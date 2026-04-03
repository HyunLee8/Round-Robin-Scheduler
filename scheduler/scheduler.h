#ifndef SCHEDULER_SCHEDULER_H
#define SCHEDULER_SCHEDULER_H
#include "../process/pcb.h"
#define MAX_PCBs 256

typedef struct {
    PCB *queue[MAX_PCBs];
    PCB *running;
    int head;
    int tail;
    int size;
    int capacity;
    int tick;
    int ticks_on_cpu;
    int quantum;
} Scheduler;

Scheduler *createScheduler();

void enqueue(Scheduler *s, PCB *pcb);
PCB *dequeue(Scheduler *s);

int is_empty(Scheduler *s);
void print_queue(Scheduler *s);

//state transition funcs

void admit_process(PCB *pcb, int tick);
void dispatch(PCB *pcb, int tick);
void preempt(PCB *pcb, int tick);
void block_on_io(PCB *pcb, int tick);
void io_complete(PCB *pcb, int tick);
void terminate_process(PCB *pcb, int tick);

void run_scheduler(Scheduler *s, PCB **processes, int size, int quantum);

#endif //SCHEDULER_SCHEDULER_H