#include <stdio.h>
#include "interrupt.h"

#include <stdlib.h>

static Interrupt *pending[MAX_INTERRUPTS];
static int pending_count = 0;

Interrupt *create_interrupt(InterruptType type, int fire_at_tick, int target_pid) {
    Interrupt *interrupt = malloc(sizeof(Interrupt));

    interrupt->type = type;
    interrupt->fire_at_tick = fire_at_tick;
    interrupt->target_pid = target_pid;
    interrupt->handled = 0;

    return interrupt;
}

void register_interrupt(Interrupt *interrupt) {
    pending[pending_count] = interrupt;
    pending_count++;
}

Interrupt *check_interrupt(int tick) {
    for (int i = 0; i < MAX_INTERRUPTS; i++) {
        if (pending[i]->fire_at_tick == tick) {
            pending[i]->handled = 1;
            return pending[i];
        }
    }
    return NULL;
}
