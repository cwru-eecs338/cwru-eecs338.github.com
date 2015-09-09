#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>

#define LOOP_ITERATIONS (1 << 30)

int main()
{
    time_t start, end;
    double time_diff;
    int i;

    // get start time
    time(&start);

    for (i = 0; i < LOOP_ITERATIONS; i++) { }

    // get end time
    time(&end);

    // calculate difference
    time_diff = difftime(end, start);

    printf("End time: %s.\n", ctime(&end));
    printf("Elapsed time: %f seconds.\n", time_diff);
}
