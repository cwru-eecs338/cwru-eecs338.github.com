#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char * cat_file = "cat";
    char * const cat_args [] = {"cat", "basic_exec.c", NULL};
    
    pid_t pid;

    // spawn a process that runs 'cat basic_exec.c'

    pid = fork();

    if (fork > 0) {
        wait();
        printf("Done.\n");
    } else if (fork == 0) {
        execvp(cat_file, cat_args);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
