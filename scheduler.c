#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "pcb.h"


/*=== Initialize scheduler ===*/

Scheduler *createScheduler() {
    Scheduler *s = malloc(sizeof(Scheduler));
    s->running = NULL;

    s->head = 0;
    s->tail = 0;
    s->size = 0;
    s->capacity = MAX_PCBs;
    s->tick = 0;
    s->ticks_on_cpu = 0;
    s->quantum = 0;

    return s;
}

/*=== Queue Functions ===*/

void enqueue(Scheduler *s, PCB *pcb) {
    if (s->size == s->capacity) {
        fprintf(stderr, "Error: Queue is full");
    } else {
        s->queue[s->tail] = pcb;
        s->tail = (s->tail + 1) % s->capacity;
        s->size++;
    }
}

PCB *dequeue(Scheduler *s) {
    if (s->size == 0) {
        return NULL;
    } else {
        PCB *pcb = s->queue[s->head];
        s->head = (s->head + 1) % s->capacity;
        s->size--;
        return pcb;
    }
}

/*=== Utilities ===*/

int is_empty(Scheduler *s) {
    return s->size == 0;
}

void print_queue(Scheduler *s) {
    int itr = s->head;
    PCB *temp = s->queue[itr];

    while (itr != s->tail) {
        temp = s->queue[itr];
        printf("PID: %i\n", temp->pid);

        itr = (itr + 1) % s->capacity;
    }
}


/*=== State Transitions ===*/

static void state_transition (PCB *pcb, ProcessState prevState, ProcessState nextState, int tick) {
    if (pcb->state == prevState) {
        pcb->state = nextState;
        printf("[TICK %i] PID %i: %s\n", tick, pcb->pid, state_to_string(pcb->state));
    } else {
        printf("Error: Not the correct state");
    }
}

void admit_process(PCB *pcb, int tick) { state_transition(pcb, NEW, READY, tick); }
void dispatch(PCB *pcb, int tick) { state_transition(pcb, READY, RUNNING, tick); }
void preempt(PCB *pcb, int tick) { state_transition(pcb, RUNNING, READY, tick); }
void block_on_io(PCB *pcb, int tick) { state_transition(pcb, RUNNING, WAITING, tick); }
void io_complete(PCB *pcb, int tick) { state_transition(pcb, WAITING, READY, tick); }
void terminate_process(PCB *pcb, int tick) { state_transition(pcb, RUNNING, TERMINATED, tick); }

/*=== Run Scheduler ===*/

void run_scheduler(Scheduler *s, PCB **processes, int size, int quantum) {
    s->quantum = quantum;
    int running_scheduler = 1;

    while (running_scheduler) {
         for (int i = 0; i < size; i++) {
            if (processes[i]->state == WAITING) {
                processes[i]->io_time_remaining--;
                if (processes[i]->io_time_remaining == 0) {
                    io_complete(processes[i], s->tick);
                    enqueue(s, processes[i]);
                }
            } else if (processes[i]->arrival_time == s->tick && processes[i]->state == NEW) {
                admit_process(processes[i], s->tick);
                enqueue(s, processes[i]);
            }
        }

        if (s->running != NULL) {
            s->running->remaining_burst--;
            s->running->program_counter++;
            s->running->cpu_time_used++;
            s->ticks_on_cpu++;
            if (s->running->remaining_burst <= 0) {
                if (s->running->io_burst_length > 0) {
                    s->running->io_time_remaining = s->running->io_burst_length;
                    s->running->io_burst_length = 0;
                    block_on_io(s->running, s->tick);
                    s->running = NULL;
                    s->ticks_on_cpu = 0;
                } else {
                    terminate_process(s->running, s->tick);
                    s->running->finish_time = s->tick;
                    s->running = NULL;
                    s->ticks_on_cpu = 0;
                }
            } else if (s->ticks_on_cpu >= s->quantum){
                preempt(s->running, s->tick);
                enqueue(s, s->running);
                s->running = NULL;
                s->ticks_on_cpu = 0;
            }

        } else if (s->running == NULL && is_empty(s) == 0) {
            s->running = dequeue(s);
            dispatch(s->running, s->tick);

        } else if (s->running == NULL && is_empty(s) == 1) {
            int complete_flag = 1;
            for (int i = 0; i < size; i++) {
                if (processes[i]->state != TERMINATED) {
                    complete_flag = 0;
                    break;
                }
            }
            if (complete_flag) running_scheduler = 0;
        }

        s->tick++;
    }
}
