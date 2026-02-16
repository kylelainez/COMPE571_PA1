/****************************************************************************************
 * Authors: Vincent Pierce, Kyle Lainez
 * 
 * Description: COMPE571 Programming Assignment 1 -- Comparing sequential, Multithreading,
 * and Multitasking workloads. This project implements a summation of numbers between 0 
 * and N, using three different methods. Case 1 is a baseline sequential implementation.
 * Case 2 is a Multithreaded implementation using POSIX pthreads. Case 3 uses multitasking 
 * via the fork system call to spawn new processes and pipes for inter-process communication. 
 * *************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){
    system("gcc PA1_Sequential.c -o sequential");
    system("gcc PA1_Multithreading.c -o multithreading");
    system("gcc PA1_Multitasking_Fork.c -o multitasking_fork");
    system("gcc PA1_Multitasking_Popen.c -o multitasking_popen");
    
    int NUM_MULTI[3] = {2,4,8};
    uint64_t N[3] = {100000000,1000000000,10000000000};

    char programs[4][50] = {
        "./sequential %lu",
        "./multithreading %lu %d",
        "./multitasking_fork %lu %d",
        "./multitasking_popen %lu %d"
    };  

    char methods[4][50]={
        "Sequential",
        "Multithreaded",
        "Multitasking (fork)",
        "Multitasking (popen)"
    };

    uint64_t total_sum[4][3][10];
    double seconds[4][3][10], elapsed[4][3];
   
    char command[256];
    for(int i=0; i < 4; i++){
        for (int val=0; val<3 ; val++){

            if (i == 0){
                for(int j=0; j<10; j++){                    // Loop to run the cases 10 times
                    FILE* fp;
                    sprintf(command, programs[i],N[val],NUM_MULTI[val]);
                    fp = popen(command, "r");
                    fscanf(fp, "%lu %lf", &total_sum[i][val][j], &seconds[i][val][j]);
                    elapsed[i][val] += seconds[i][val][j];
                }
                elapsed[i][val] = elapsed[i][val] / 10;
                printf("Average time taken using %s with N=%lu is: %lf\n", methods[i],N[val],(elapsed[i][val]));
            }else{
                for (int val_thread = 0; val_thread < 3; val_thread++){
                    for(int j=0; j<10; j++){                    // Loop to run the cases 10 times
                        FILE* fp;
                        sprintf(command, programs[i],N[val],NUM_MULTI[val]);
                        fp = popen(command, "r");
                        fscanf(fp, "%lu %lf", &total_sum[i][val][j], &seconds[i][val][j]);
                        elapsed[i][val] += seconds[i][val][j];
                    }
                    elapsed[i][val] = elapsed[i][val] / 10;
                    printf("Average time taken using %s with N=%lu and NUM_THREADS/TASK=%d is: %lf\n", methods[i],N[val],NUM_MULTI[val_thread],(elapsed[i][val]));
                }
                
                
            }
            
        }
    }
    

    return 0;
}