# COMPE571 – Embedded Operating Systems – Programming Assignment 1
**Authors**: Vincent Pierce, Kyle Lainez
-----------------------------------------------------------------------------------------
This project accomplishes a simple workload, calculating the summation of 0 through N, via sequential, multitasking, and multithreading implementations. The multithreaded and multitasked implementations also accept a parameter for the number of threads, or processes to spawn when performing workloads. Measurements for each implementation's speed are compared and justified, as both the number of tasks/threads and the workload size N is varied.  

## Usage

Compile and run **PA1_Master.c** to execute all test cases 10 times and display the average time taken.  
>`gcc PA1_Master.c -o master`  
`./master`

To execute the test cases individually, compile and run each program using **N** as the first argument and **NUM_THREADS / NUM_TASKS** as the second.
  
### Sequential
```shell
gcc PA1_Sequential -o sequential` 
./sequential 1000000
```  
### Multithreading
```shell
gcc PA1_Multithreading -o multithreading
./multithreading 10000000 8
                    #N    #NUM_THREADS
```
### Multitasking using fork
```shell
gcc PA1_Multitasking_Fork -o multitasking_fork
./multitasking_fork 10000000 8
```
### Multitasking using popen
```shell
gcc PA1_Multitasking_Popen -o multitasking_popen
./multitasking_popen 10000000 8
```