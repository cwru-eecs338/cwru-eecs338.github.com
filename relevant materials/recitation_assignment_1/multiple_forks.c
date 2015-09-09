#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_FORKS 4

int main()
{
    pid_t pid;
    int status;
    int fork_count;

    for(fork_count = 0; fork_count < NUM_FORKS; fork_count++) {
        pid = fork();

        if (pid > 0) {
            // parent
        } else if (pid == 0) {
            // child
            // look at fork_count
            break;

            // better way!!!!
            // do_child_stuff();
            // return 0; -or- exit(0);
        } else {
            perror("fork() failed\n");
            exit(EXIT_FAILURE);
        }
    }

    if (pid == 0) {
        printf("I am child #%d and my pid is %d.\n", fork_count, getpid());
    } else {
        printf("I am the parent and I will wait on my children!\n");
        for (fork_count = 0; fork_count < NUM_FORKS; fork_count++) {
            pid = wait(&status);
            printf("process %d exited with status %d\n", pid, WEXITSTATUS(status));
        }
    }
}
