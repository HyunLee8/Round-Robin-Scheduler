#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "scheduler.h"
#include "interrupt.h"
#include "threads.h"

int main(void) {
    /*
    PCB *pcb1 = create_process(0, 0,  10, 3, 1);
    PCB *pcb2 = create_process(1, 1,  6,  0, 2);
    PCB *pcb3 = create_process(2, 2,  8,  5, 3);
    PCB *pcb4 = create_process(3, 4, 10, 3, 1);

    PCB **processes = (PCB **)malloc(4*sizeof(PCB *));
    const int processes_size = 4;
    processes[0] = pcb1;
    processes[1] = pcb2;
    processes[2] = pcb3;
    processes[3] = pcb4;

    Interrupt *intr1 = create_interrupt(INT_KILL, 0, 0);
    Interrupt *intr3 = create_interrupt(INT_KILL, 2, 2);

    register_interrupt(intr1);
    register_interrupt(intr3);

    Scheduler *s = createScheduler();
    run_scheduler(s, processes, 4, 4);

    for (int i = 0; i < processes_size; i++) {
        destroy_process((processes[i]));
    }

    free(processes);
    free(intr1);
    free(intr3);

    printf("Finished");

    */
    Thread *thread0 = create_thread(0, 0, 3);
    Thread *thread1 = create_thread(1, 0, 3);
    Thread *thread2 = create_thread(2, 0, 3);

    threads[0] = thread0;
    threads[1] = thread1;
    threads[2] = thread2;

    run_race_condition_demo(3);

    return 0;
}
