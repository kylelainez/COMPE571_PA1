/****************************************************************************************
 * Authors: Vincent Pierce, Kyle Lainez
 * 
 * Description: COMPE571 Programming Assignment 1 -- Comparing sequential, Multithreading,
 * and Multitasking workloads. This project implements a summation of numbers between 0 
 * and N, using three different methods. Case 1 is a baseline sequential implementation.
 * Case 2 is a Multithreaded implementation using POSIX pthreads. Case 3 uses multitasking 
 * via the fork system call to spawn new processes and pipes for inter-process communication. 
 * 
 * Multitasking using fork Implementation below
 * *************************************************************************************/

/* FILE INCLUSIONS *********************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/* Source Code *************************************************************************/

void doWork(uint64_t lower, uint64_t upper, int pipe);
void Multiprocessing(uint64_t N, uint8_t NUM_THREADS);

int main(int argc, char* argv[]){
    uint64_t N = strtoull(argv[1],NULL, 10);
    uint64_t NUM_TASKS = strtol(argv[2],NULL,10);
    Multiprocessing(N,NUM_TASKS);
    return 0;
}

void Multiprocessing(uint64_t N, uint8_t NUM_PROCESSES)
{
    struct timespec start, end;
    pid_t pid;
    pid_t* processes = malloc(sizeof(pid_t)*NUM_PROCESSES); // array of process ids 
    uint64_t sum = 0, accumulator = 0;
    uint64_t workLoad = N / NUM_PROCESSES;
    int fd[2]; // 0 read 1 write 
    pipe(fd);

    clock_gettime(CLOCK_MONOTONIC, &start); // start work

    for(int i = 0; i<NUM_PROCESSES; i++) // spawn the processes
    {
        pid = fork();

        if(pid == 0)
        { // -------------- Child --------------
            close(fd[0]); // child only writes 
            uint64_t lower = workLoad*i;
            uint64_t upper = (i == NUM_PROCESSES - 1) ? N : workLoad * (i + 1);
            doWork(lower, upper, fd[1]); // child does work
            close(fd[1]);
            return; 
        } // -------------- Child --------------
        else
        {
            // close(fd[1]); // parent only reads
            processes[i] = pid; // parent registers child
        }
    }
    
    for(int i = 0; i<NUM_PROCESSES; i++)
    {
        wait(processes+sizeof(pid_t)*i); // any child termination will unblock
        size_t a = read(fd[0], &accumulator, sizeof(uint64_t));
        sum += accumulator;
    }
    close(fd[0]);

    clock_gettime(CLOCK_MONOTONIC, &end); // end clock

    // Calculate time betwen start and end clock
    double time_taken = end.tv_sec - start.tv_sec; 
    time_taken += (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("%lu %f",sum, time_taken);
    free(processes);
}
void doWork(uint64_t lower, uint64_t upper, int pipe)
{
    uint64_t sum = 0;
    int writePipe = dup(pipe);

    for(uint64_t i = lower; i < upper; i++)
    {
        sum +=i;
    }
    write(writePipe, &sum, sizeof(sum)); 
}