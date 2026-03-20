#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "scheduler.h"

int main(void) {
    PCB *pcb1 = create_process(0, 0,  10, 3, 1);
    PCB *pcb2 = create_process(1, 2,  6,  0, 2);
    PCB *pcb3 = create_process(2, 4,  8,  5, 3);
    PCB *pcb4 = create_process(3, 2, 10, 3, 1);

    PCB **processes = (PCB **)malloc(4*sizeof(PCB *));
    processes[0] = pcb1;
    processes[1] = pcb2;
    processes[2] = pcb3;
    processes[3] = pcb4;

    Scheduler *s = createScheduler();
    run_scheduler(s, processes, 4, 4);
    printf("Finished");


    return 0;
}
