#include <stdio.h>
#include <pthread.h>
#include "threads.h"

#include <stdlib.h>

static int shared_counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

Thread *create_thread(int tid, int parent_pid, int work_unit) {
    Thread *thread = malloc(sizeof(Thread));

    thread->tid = tid;
    thread->parent_pid = parent_pid;
    thread->work_unit = work_unit;
    thread->result = 0;

    return thread;
}

void *thread_worker(void *arg) {
    int total = 0;
    for (int i = 0; i < ((Thread *)arg)->work_unit; ++i) {
        total += ((Thread *)arg)->tid;
    }
    ((Thread *)arg)->result = total;
    printf("[Thread %i of PID %i] done, result = %li", ((Thread *)arg)->tid, ((Thread *)arg)->parent_pid, ((Thread *)arg)->result);

    return NULL;
}

void *demo_worker(void *arg) {
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        shared_counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void run_multithreaded_processor(int num_threads) {
    pthread_t pthreads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        int ret = pthread_create(&pthreads[i], NULL, thread_worker, threads[i]);
        if (ret != 0) {
            printf("Error creating pthread %d\n", ret);
            exit(1);
        }
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(pthreads[i], NULL);
    }

    int total = 0;
    for (int i = 0; i < num_threads; i++) {
        total += threads[i]->result;
    }

    printf("Total result: %i", total);
}

void run_race_condition_demo (int num_threads) {
    pthread_t pthreads[num_threads];
    shared_counter = 0;

    for (int i = 0; i < num_threads; i++) {
        pthread_create(&pthreads[i], NULL, demo_worker, threads[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(pthreads[i], NULL);
    }

    printf("Total result: %i", shared_counter);
}