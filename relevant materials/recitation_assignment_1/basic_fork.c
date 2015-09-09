#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main()
{
    const int max_number = 10;
    const unsigned sleep_interval = 4; // seconds
    int current_number;
    int process_no;
    pid_t fork_result;

    fork_result = fork();

    if (fork_result == 0) {
        // child process 
        process_no = 2;
        current_number = 1;
        sleep(sleep_interval / 2);
    } else if (fork_result > 0) {
        // parent process
        process_no = 1;
        current_number = 0;
    } else {
        fprintf(stderr, "errno %d: %s\n", errno, strerror(errno));
        // if you really want that extra info ^
        perror("fork() failed\n");
        exit(EXIT_FAILURE);
    }

    while (current_number < max_number) {
        printf("Process #%d (%d): %d\n", process_no, getpid(), current_number);
        current_number += 2;
        sleep(sleep_interval);
    }

    return EXIT_SUCCESS;
}
