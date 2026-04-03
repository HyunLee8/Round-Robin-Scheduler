#ifndef SCHEDULER_PROCESS_THREADS_H
#define SCHEDULER_PROCESS_THREADS_H
#include "pcb.h"

//need this file to get rid of circular dependencies

void load_process_threads(PCB *pcb);
void unload_process_threads();

#endif //SCHEDULER_PROCESS_THREADS_H