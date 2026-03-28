# ProcessThreadSim

This is a simple high level simulation of a round robin scheduler used in all OS's in order to handle several requests at the same time taking care of PCBs, interruptions, and thread workers.

## Scheduler

The scheduler struct consists of a custon queue data structure of type PCB, a running PCB, head and tail pointers for the queue, size, capacity, current tick, and cpu tick. The diference of the cpu and global tick is that the cpu is tracking how many ticks the current PCB has been running for and will be overriden by the quantum tick which says "Hey all you can take up is x ticks for this cycle; go in the back of the queue". 

The following helper functions:
- admit_process(): NEW -> READY
- dispatch(): READY -> RUNNING
= preempy(): RUNNING -> READY
- block_on_io(): RUNNING -> WAITING
- io_complete(): WAITING -> READY
- terminate_process(): STATE -> TERMINATED


## Run Scheduler

Once all processes are allocated into an array which each one having a specific set of allocated amount of threads with its own characteristics it can initiate the process by performing run_scheudler() with arguments Scheduler* s, PCB **pcb, const int size,  const int quantum. Quantum is the max amount of ticks a process can hog the running cycle like stated earlier if a process has a cpu_tick of 5 but the quantum is 4 then once 4 ticks are run it does a state transition to preempt and sends it to enqueue. At the begininng of the loop, it always checks interruptions as they are the highest priority of any process in the entire program. Instead of passing it in the run scheudler it acccesses the global array via check_Interruptions. Next priority would be the wait list; this should only be run after the first tick since no processes can be allowed in the waitlist off the first run. Only once those conditions are checked can the scheduler now start pushing threads to compute via pthreads library. 

## Notes

There is a outlier file called process_threads.c/h which litteraly only has one function. While I was making the program there was a bit of a circular dependecy issue where i had threads.h include pcb and pcb.h include threads but because threads are inside of processes it should've only been pcb.h including threads.h. I had to fix this by making a intermediate between the two and added pcb.h inorder for processes to load the threads in the thread.c file

