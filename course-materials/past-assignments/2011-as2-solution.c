/* 
 * File:   as2.c
 * Author: 
 * Description:
 *      EECS 338
 *      Assignment #2
 *
 *      Procedure:
 *       1 - parent opens four unnamed pipes
 *       2 - parent forks two children
 *       3 - children send PIDS to parent
 *       4 - parent conducts at least 10 iterations of prisoner's dilemma game
 *       5 - parent signals children to exit
 *       6 - parent prints score and exits
 *
 *      Pipe communication protocol
 *       - parent sends one byte commands followed by terminator character
 *       - child responses have one or more bytes followed by terminator character
 *       - valid messages are #defined as PARENT_ and CHILD_ macros below
 * 
 */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PARENT_REQUEST_PID    1     // request for child's PID
#define PARENT_REQUEST_CHOICE 2     // request for child to respond to prisoner's dilemma
#define PARENT_REQUEST_EXIT   3     // request for child to exit
#define CHILD_RESPONSE_COOPERATE 0  // prisoner response to interrogation: take the fifth
#define CHILD_RESPONSE_DEFECT    1  // prisoner response to interrogation: confess
#define TERMINATOR '\0'             // character indicating end of protocol communication over pipe
const int PIPE_READ_END = 0;        // read end of pipe
const int PIPE_WRITE_END = 1;       // write end of pipe
const int PIPE_BUFFER_SIZE = 32;    // arbitrary size for pipe buffers
const int NUMBER_OF_GAMES = 10;     // number of times to iterate the prisoner's dilemma game
/*
 * returns random choice to defect or cooperate
 * 0 = cooperate
 * 1 = defect
 */
int rand_choice(void){
    return rand() % 2;  // pseudo-randomly return 0 or 1
}
/*
 * print the human-readable meaning of a prisoner's option
 * 0    = cooperate
 * else = defect
 */
void print_choice(int c){
    if(c) printf("Defect");
    else  printf("Cooperate");
}
/*
 * main
 */
int main(void) {
    // step 1: set up four unnamed pipes
    int pipe_to_c1   [2],
        pipe_to_c2   [2],
        pipe_from_c1 [2],
        pipe_from_c2 [2];
    if (pipe(pipe_to_c1)   |
        pipe(pipe_to_c2)   |
        pipe(pipe_from_c1) |
        pipe(pipe_from_c2)
       ){
        perror("Error.  Failed when trying to create pipes.");
        exit(EXIT_FAILURE);
    }
    // step 2: fork two children
    // ... first, set up some variables useful to all processes
    char ibuf[PIPE_BUFFER_SIZE]; // inpput pipe buffer
    char obuf[PIPE_BUFFER_SIZE]; // output pipe buffer
    int ibptr = 0; // input buffer position pointer
    int obptr = 0; // output buffer position pointer
    int wlen = 0;  // write length
    int rlen = 0;  // read length
    pid_t c1_again = 0; // stores pid in child or parent for passing by pipe
    pid_t c2_again = 0; // stores pid in child or parent for passing by pipe
    // ... now, fork the children
    pid_t c1 = fork(); // fork child 1
    if (c1 < 0) {
        perror("Error.  Failed to fork child 1.");
        exit(EXIT_FAILURE);
    }
    if(c1 == 0){ // this is child 1
        srand (getpid()); // seed the random number generator
        close(pipe_to_c1[PIPE_WRITE_END]);  // close write end of inbound pipe
        close(pipe_from_c1[PIPE_READ_END]); // close read end of outbound pipe
        while(1){//loop until parent requests exit
            rlen = read(pipe_to_c1[PIPE_READ_END], ibuf, 2); // get the request from the parent
            switch(ibuf[0]){ // read the command byte of the request from the parent
                case PARENT_REQUEST_PID: // prisoner has requested PID
                    c1_again = getpid();
                    if(c1_again == 0){
                        perror("Error.  Failed to get PID.");
                        _exit(EXIT_FAILURE);
                    }
                    obptr = sprintf(obuf, "%d", c1_again);
                    if(obptr == 0){
                        perror("Error.  Failed to parse PID.");
                        _exit(EXIT_FAILURE);
                    }
                    obptr++; //increment pointer to terminator location
                    obuf[obptr] = TERMINATOR;
                    wlen = write(pipe_from_c1[PIPE_WRITE_END], obuf, obptr);
                    break;
                case PARENT_REQUEST_CHOICE: // parent has requested response to prisoner's dilemma
                    wlen = sprintf(obuf, "%d", rand_choice());
                    obuf[1] = TERMINATOR;
                    wlen = write(pipe_from_c1[PIPE_WRITE_END], obuf, 2);
                    break;
                case PARENT_REQUEST_EXIT: // parent has requested that this process exit
                    close(pipe_to_c1[PIPE_READ_END]);    // close read end of inbound pipe
                    close(pipe_from_c1[PIPE_WRITE_END]); // close write end of outbound pipe
                    _exit(EXIT_SUCCESS);
                    break;
                default:
                    perror("Error.  Invalid request from parent.");
                    _exit(EXIT_FAILURE);
                    break;
            }
        }
    } // end child 1 section
    pid_t c2 = fork(); // fork child 2
    if (c2 < 0) {
        perror("Error.  Failed to fork child 2.");
        exit(EXIT_FAILURE);
    }
    if(c2 == 0){// this is child 2
        srand (getpid()); // seed the random number generator
        close(pipe_to_c2[PIPE_WRITE_END]);  // close write end of inbound pipe
        close(pipe_from_c2[PIPE_READ_END]); // close read end of outbound pipe
        while(1){//loop until parent requests exit
            rlen = read(pipe_to_c2[PIPE_READ_END], ibuf, 2); // get the request from the parent
            switch(ibuf[0]){ // read command byte of request from parent
                case PARENT_REQUEST_PID: // parent has requested PID
                    c2_again = getpid();
                    if(c2_again == 0){
                        perror("Error.  Failed to get PID.");
                        _exit(EXIT_FAILURE);
                    }
                    obptr = sprintf(obuf, "%d", c2_again);
                    if(obptr == 0){
                        perror("Error.  Failed to parse PID.");
                        _exit(EXIT_FAILURE);
                    }
                    obptr++; //increment pointer to terminator location
                    obuf[obptr] = TERMINATOR;
                    wlen = write(pipe_from_c2[PIPE_WRITE_END], obuf, obptr);
                    break;
                case PARENT_REQUEST_CHOICE: // parent has requested response to prisoner's dilemma
                    wlen = sprintf(obuf, "%d", rand_choice());
                    obuf[1] = TERMINATOR;
                    wlen = write(pipe_from_c2[PIPE_WRITE_END], obuf, 2);
                    break;
                case PARENT_REQUEST_EXIT: // parent has requested that this process exit
                    close(pipe_to_c2[PIPE_READ_END]);    // close read end of inbound pipe
                    close(pipe_from_c2[PIPE_WRITE_END]); // close write end of outbound pipe
                    _exit(EXIT_SUCCESS);
                    break;
                default:
                    perror("Error.  Invalid request from parent.");
                    _exit(EXIT_FAILURE);
                    break;
            }
        }
    } // end child 2 section
    // step 3: request PIDs from children (even though the parent already has them, we follow the assignment)
    //...close the ends of the pipes we won't be using
    close(pipe_to_c1[PIPE_READ_END]); // close read end of pipe to child 1
    close(pipe_to_c2[PIPE_READ_END]); // close read end of pipe to child 2
    close(pipe_from_c1[PIPE_WRITE_END]); // close write end of pipe from child 1
    close(pipe_from_c2[PIPE_WRITE_END]); // close write end of pipe from child 2
    //...prepare the output buffer
    obuf[0] = PARENT_REQUEST_PID;
    obuf[1] = TERMINATOR;
    obptr = 2;
    wlen = write(pipe_to_c1[PIPE_WRITE_END], obuf, obptr); // send request to child 1
    wlen = write(pipe_to_c2[PIPE_WRITE_END], obuf, obptr); // send request to child 2
    //...read from child 1
    ibptr = 0;
    ibuf[0] = '*'; // initialize to non-terminator character
    while((read(pipe_from_c1[PIPE_READ_END], &ibuf[ibptr], 1)) &&
          (ibptr < PIPE_BUFFER_SIZE) &&
          (ibuf[ibptr] != TERMINATOR)
         ){
        ibptr ++;
    }
    if(!sscanf(ibuf, "%d", &c1_again)){
        perror("Error.  Failed to parse PID from C1.");
        exit(EXIT_FAILURE);
    }
    //...read from child 2
    ibptr = 0;
    ibuf[0] = '*'; // initialize to non-terminator character
    while((read(pipe_from_c2[PIPE_READ_END], &ibuf[ibptr], 1)) &&
          (ibptr < PIPE_BUFFER_SIZE) &&
          (ibuf[ibptr] != TERMINATOR)
         ){
        ibptr ++;
    }
    if(!sscanf(ibuf, "%d", &c2_again)){
        perror("Error.  Failed to parse PID from C2.");
        exit(EXIT_FAILURE);
    }
    // step 4: conduct 10 iterations of prisoner's dilemma game
    int i,                // iterator
        c1resp = 0,       // child 1 response
        c2resp = 0;       // child 2 response
    double c1score = 0.0, // child 1 score
           c2score = 0.0; // child 2 score
    // execute games
    // ... set up request buffer
    obuf[0] = PARENT_REQUEST_CHOICE;
    obuf[1] = TERMINATOR;
    obptr = 2;
    //... game loop
    for(i = 1; i <= NUMBER_OF_GAMES; i++){ // start iterator from 1 for ease of displaying the count
        printf("Game %d:\n", i);
        //...write to child 1
        wlen = write(pipe_to_c1[PIPE_WRITE_END], obuf, 2);
        //...write to child 2
        wlen = write(pipe_to_c2[PIPE_WRITE_END], obuf, 2);
        //...read from child 1
        rlen = read(pipe_from_c1[PIPE_READ_END], ibuf, 2);
        if(!sscanf(ibuf, "%d", &c1resp)){
            perror("Error.  Failed to parse response from C1.");
            exit(EXIT_FAILURE);
        }
        printf("%d: ", c1_again); print_choice(c1resp); printf("\n");
        //...read from child 2
        rlen = read(pipe_from_c2[PIPE_READ_END], ibuf, 2);
        if(!sscanf(ibuf, "%d", &c2resp)){
            perror("Error.  Failed to parse response from C2.");
            exit(EXIT_FAILURE);
        }
        printf("%d: ", c2_again); print_choice(c2resp); printf("\n");
        //process the results
        if((c1resp == CHILD_RESPONSE_COOPERATE) && (c2resp == CHILD_RESPONSE_COOPERATE)){c1score +=  0.5; c2score +=  0.5;}
        else
        if((c1resp == CHILD_RESPONSE_COOPERATE) && (c2resp == CHILD_RESPONSE_DEFECT   )){c1score += 10.0; c2score +=  0.0;}
        else
        if((c1resp == CHILD_RESPONSE_DEFECT   ) && (c2resp == CHILD_RESPONSE_COOPERATE)){c1score +=  0.0; c2score += 10.0;}
        else
        if((c1resp == CHILD_RESPONSE_DEFECT   ) && (c2resp == CHILD_RESPONSE_DEFECT   )){c1score +=  6.0; c2score +=  6.0;}
    }
    // step 5: signal children to exit
    obuf[0] = PARENT_REQUEST_EXIT;
    obuf[1] = TERMINATOR;
    obptr = 2;
    wlen = write(pipe_to_c1[PIPE_WRITE_END], obuf, obptr);
    wlen = write(pipe_to_c2[PIPE_WRITE_END], obuf, obptr);
    //...close the pipes
    close(pipe_to_c1[PIPE_WRITE_END]); // close pipe to c1
    close(pipe_to_c2[PIPE_WRITE_END]); // close pipe to c2
    close(pipe_from_c1[PIPE_READ_END]); // close pipe from c1
    close(pipe_from_c2[PIPE_READ_END]); // close pipe from c2
    // step 6: print final score and exit
    wait(NULL); // wait for children
    printf("------------------------\nScore:\n");
    printf("%d: %.1f years\n", c1, c1score);
    printf("%d: %.1f years\n", c2, c2score);
    return (EXIT_SUCCESS);
}


