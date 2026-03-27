#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"
#include "threads.h"

PCB *create_process(int pid, int arrival_time, int cpu_burst, int io_burst, int priority) {
    PCB *pcb = malloc(sizeof(PCB));
    pcb->threads_size = 0;

    pcb->pid = pid;
    pcb->state = NEW;
    pcb->program_counter = 0;
    pcb->cpu_time_used = 0;
    pcb->cpu_burst = cpu_burst;
    pcb->remaining_burst = cpu_burst;
    pcb->io_burst_length = io_burst;
    pcb->io_time_remaining = io_burst;
    pcb->priority = priority;
    pcb->arrival_time = arrival_time;
    pcb->finish_time = -1;

    return pcb;
}

void destroy_process(PCB *pcb) {
    free(pcb);
}

void print_pcb(PCB *pcb) {
    printf("pid: %i\n", pcb->pid);
    printf("state %s\n", state_to_string(pcb->state));
    printf("program_counter: %i\n", pcb->program_counter);
    printf("cpu_time_used: %i\n", pcb->cpu_time_used);
    printf("cpu_burst: %i\n", pcb->cpu_burst);
    printf("remaining_burst: %i\n", pcb->remaining_burst);
    printf("io_burst_length: %i\n", pcb->io_burst_length);
    printf("io_time_remaining: %i\n", pcb->io_time_remaining);
    printf("priority: %i\n", pcb->priority);
    printf("arrival_time: %i\n", pcb->arrival_time);
    printf("finish_time: %i\n", pcb->finish_time);
}

void add_thread(PCB *pcb, Thread *thread) {
    if (pcb->threads_size < MAX_THREADS) {
        threads[pcb->threads_size] = thread;
        pcb->threads_size++;
    } else {
        printf("Too many threads\n");
    }
}

void remove_thread(PCB *pcb) {
    if (pcb->threads_size > 0) {
        pcb->threads_size--;
    } else {
        printf("No more threads\n");
    }
}

/*
void destroy_thread(Thread *thread) {

}
*/