#include "threads.h"
#include "pcb.h"

void load_process_threads(PCB *pcb) {
    for (int i = 0; i < pcb->threads_size; i++) {
        threads[threads_size] = &pcb->threads[i];
        threads_size++;
    }
}