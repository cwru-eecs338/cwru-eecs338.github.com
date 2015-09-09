#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>

#define LOOP_ITERATIONS (0x7fffffff) // biggest positive 32 bit integer

int main()
{
    struct tms process_times;
    clock_t result;
    double utime_seconds; // user time in seconds
    double stime_seconds; // system time in seconds
    int i;

    for (i = 0; i < LOOP_ITERATIONS; i++) { }

    result = times(&process_times);
    if (result == (clock_t) -1) {
        perror("times() failed\n");
        exit(EXIT_FAILURE);
    }
    
    utime_seconds =
        (double) process_times.tms_utime / CLOCKS_PER_SEC;
    stime_seconds =
        (double) process_times.tms_stime / CLOCKS_PER_SEC;

    printf("User time: %f\n", utime_seconds);
    printf("System time: %f\n", stime_seconds);
}

