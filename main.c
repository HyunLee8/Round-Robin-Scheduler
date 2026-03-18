#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"
#include "scheduler.h"

int main(void) {
    PCB *pcb1 = create_process(0, 2, 10, 3, 1);
    PCB *pcb2 = create_process(1, 2, 10, 3, 1);
    PCB *pcb3 = create_process(2, 2, 10, 3, 1);
    PCB *pcb4 = create_process(3, 2, 10, 3, 1);

    Scheduler *s = createScheduler();

    enqueue(s, pcb1);
    enqueue(s, pcb2);
    enqueue(s, pcb3);
    enqueue(s, pcb4);
    dequeue(s);
    dequeue(s);
    admit_process(s->queue[s->head], 1);

    print_queue(s);
    printf("%s",state_to_string(s->queue[s->head]->state));

    return 0;
}
