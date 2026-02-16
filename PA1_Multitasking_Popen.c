#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    uint64_t N = strtoull(argv[1],NULL, 10);
    uint64_t NUM_TASKS = strtol(argv[2],NULL,10);

    FILE* fps[NUM_TASKS];
    uint64_t total_sum = 0;
    
    //Clock
    struct timespec start, end;
    double elapsed;
    
    clock_gettime(CLOCK_MONOTONIC, &start);          // Start Clock

    for (int i = 0; i < NUM_TASKS ; i++){
        char command[256];
        uint64_t start = i * (N / NUM_TASKS);
        uint64_t end = (i + 1) == NUM_TASKS ? N : (i + 1) * (N / NUM_TASKS);
        sprintf(command, "./calc_sum %lu %lu", start, end);
        fps[i] = popen(command, "r");
    }
    for (int i=0; i<NUM_TASKS; i++) {
        uint64_t partial_sum;
        fscanf(fps[i], "%lu", &partial_sum);
        total_sum += partial_sum;
        pclose(fps[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);              // End clock

    // Calculate time betwen start and end clock
    elapsed = end.tv_sec - start.tv_sec;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("%lu %f",total_sum, elapsed);

}