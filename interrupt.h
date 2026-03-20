#ifndef SCHEDULER_INTERRUPT_H
#define SCHEDULER_INTERRUPT_H

#define MAX_INTERRUPTS 64

typedef enum {
    INT_TIMER,
    INT_IO_COMPLETE,
    INT_KILL
} InterruptType;

typedef struct {
    InterruptType type;
    int fire_at_tick;
    int target_pid;
    int handled;
} Interrupt;

Interrupt *create_interrupt(InterruptType type, int fire_at_tick, int target_pid);


void register_interrupt(Interrupt *interrupt);
Interrupt *check_interrupts(int tick);

#endif //SCHEDULER_INTERRUPT_H