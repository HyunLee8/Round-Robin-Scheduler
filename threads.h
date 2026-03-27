#ifndef SCHEDULER_THREADS_H
#define SCHEDULER_THREADS_H
#define NUM_THREADS 4
#define INCREMENTS 100000

typedef struct {
   int tid;
   int parent_pid;
   int work_unit;
   long result;
} Thread;

Thread *threads[NUM_THREADS];
static int threads_size = 0;

Thread *create_thread(int tid, int parent_pid, int work_unit);
void *thread_worker (void *arg);
void run_multithreaded_processor(int num_threads);
void run_race_condition_demo(int num_threads);

#endif //SCHEDULER_THREADS_H