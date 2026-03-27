#ifndef SCHEDULER_PCB_H
#define SCHEDULER_PCB_H
#include "threads.h"
#define MAX_THREADS 256

typedef enum { NEW, READY, RUNNING, WAITING, TERMINATED } ProcessState;

typedef struct {
    int pid;
    ProcessState state;

    Thread threads[MAX_THREADS];
    int threads_size;

    int program_counter;
    int cpu_time_used;
    int cpu_burst;
    int remaining_burst;
    int io_burst_length;
    int io_time_remaining;
    int priority;
    int arrival_time;
    int finish_time;
} PCB;

static inline char *state_to_string(const ProcessState state) {
    switch (state) {
        case NEW:
            return "NEW";
        case READY:
            return "READY";
        case RUNNING:
            return "RUNNING";
        case WAITING:
            return "WAITING";
        case TERMINATED:
            return "TERMINATED";
        default:
            return "UNKNOWN";
    }
}

PCB *create_process(int pid, int arrival_time, int cpu_burst, int io_burst, int priority);
void print_pcb(PCB *p);
void destroy_process(PCB *p);
void add_thread(PCB *pcb, Thread *thread);
void remove_thread(PCB *pcb);
#endif //SCHEDULER_PCB_H