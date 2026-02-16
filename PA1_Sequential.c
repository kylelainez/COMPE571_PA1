/****************************************************************************************
 * Authors: Vincent Pierce, Kyle Lainez
 * 
 * Description: COMPE571 Programming Assignment 1 -- Comparing sequential, Multithreading,
 * and Multitasking workloads. This project implements a summation of numbers between 0 
 * and N, using three different methods. Case 1 is a baseline sequential implementation.
 * Case 2 is a Multithreaded implementation using POSIX pthreads. Case 3 uses multitasking 
 * via the fork system call to spawn new processes and pipes for inter-process communication. 
 * 
 * Sequential Implementation below
 * *************************************************************************************/

/* FILE INCLUSIONS *********************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Source Code *************************************************************************/
int main(int argc, char* argv[])
{
    uint64_t N = strtoull(argv[1],NULL, 10);
    uint64_t sum = 0;
    //Clock
    struct timespec start, end;
    double elapsed;
    
    clock_gettime(CLOCK_MONOTONIC, &start);          // Start Clock

    for(uint64_t i=0;i<N;++i)
    {
        sum+=i;
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);              // End clock

    // Calculate time betwen start and end clock
    elapsed = end.tv_sec - start.tv_sec;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("%lu %f",sum, elapsed);
    return 0;
}