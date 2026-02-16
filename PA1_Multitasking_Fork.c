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

/* Source Code *************************************************************************/
int main(int argc, char* argv[]){
    uint64_t N = strtoull(argv[1],NULL, 10);
    uint64_t NUM_TASKS = strtol(argv[2],NULL,10);

    int pipes[NUM_TASKS][2];
    pid_t pids[NUM_TASKS];

    //Clock
    struct timespec start, end;
    double elapsed;
    
    clock_gettime(CLOCK_MONOTONIC, &start);          // Start Clock

   for (int i=0; i< NUM_TASKS; i++){
        pipe(pipes[i]);
        pids[i] = fork();

        uint64_t start = i * (N / NUM_TASKS);
        uint64_t end = (i + 1) == NUM_TASKS ? N : (i + 1) * (N / NUM_TASKS);
        uint64_t local_sum = 0;

        if (pids[i] == 0){                                        // Child Process
            close(pipes[i][0]);

            for(uint64_t j = start; j < end; j++){
                local_sum += j;
            }
            write(pipes[i][1], &local_sum, sizeof(local_sum));
            exit(0);

        }else if (pids[i] > 0){                                   // Parent Process
            close(pipes[i][1]);
        }
   }
   uint64_t total_sum = 0;
   for (int i=0; i<NUM_TASKS; i++){
        uint64_t local_sum = 0;
        read(pipes[i][0], &local_sum, sizeof(local_sum));
        total_sum += local_sum;
   }


    clock_gettime(CLOCK_MONOTONIC, &end);              // End clock

    // Calculate time betwen start and end clock
    elapsed = end.tv_sec - start.tv_sec;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("%lu %f",total_sum, elapsed);
    return 0;
}