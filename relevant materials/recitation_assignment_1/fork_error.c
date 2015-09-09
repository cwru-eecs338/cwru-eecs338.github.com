#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("I am the child process (%d).\n", getpid());
        printf("My parent has the pid %d.\n", getppid());
    } else if (pid > 0) {
        printf("I am the parent process (%d).\n", getpid());
        printf("My child has the pid %d.\n", pid);

        // what should we do here?
    } else {
        perror("fork() failed");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
