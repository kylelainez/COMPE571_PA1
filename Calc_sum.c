#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    uint64_t start = strtoull(argv[1], NULL,  10);
    uint64_t end = strtoull(argv[2], NULL, 10);
    uint64_t sum = 0;

    for (uint64_t i = start; i < end; i++) {
        sum += i;
    }

    printf("%lu\n", sum);

    return 0;
}