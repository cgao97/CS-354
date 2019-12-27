//////////////////////////////////
// Main File:        intdate.c
// This File:        intdate.c
// Other Files:      sendsig.c division.c
// Semester:         CS 354 Fall 2018
//
// Author:           Chenxi Gao
// Email:            cgao63@wisc.edu
// CS Login:         cgao
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
int seconds = 3;
int count = 0;

/* This is the SIGALRM handler
 * Prints pid and current time every time an alarm is received
 */

void handler_SIGALRM(){
    time_t currtime;
    time(&currtime);
    if (ctime(&currtime) == NULL){
        printf("Error printing current time\n");
        exit(1);
    }
    printf("PID: %d | Current Time: %s", getpid(), ctime(&currtime));
    alarm(seconds);
}
/* This is the SIGUSR1 handler
 * Prints signal recieves and increase count
 */

void handler_SIGUSR1(){
    printf("SIGUSR1 caught!\n");
    count++;
}

/* This is the SIGINT handler
 * Prints number of operations completed and terminates
 */
void handler_SIGINT(){
    printf("\nSIGINT received.\nSIGUSR1 was received %d times."
    " Exiting now.\n", count);
    exit(0);
}

/* This program prints the pid and current time every 3 seconds
 * counts number of SIGUSR1 received before terminates
 *
 * argc: CLA count
 * argv: CLA value
 */
int main(){
    struct sigaction act;
    memset (&act, 0, sizeof(act));
    act.sa_handler = handler_SIGALRM;
    act.sa_flags = 0;
    if (sigaction(SIGALRM, &act, NULL) != 0){
        printf("ERROR binding SIGALRM handler.\n");
        exit(1);
    }
    alarm(seconds);

    struct sigaction user;
    memset (&user, 0, sizeof(user));
    user.sa_handler = handler_SIGUSR1;
    user.sa_flags = 0;
    if (sigaction(SIGUSR1, &user, NULL) != 0){
        printf("ERROR binding SIGUSR1 handler.\n");
        exit(1);
    }

    struct sigaction cntr_c;
    memset (&cntr_c, 0, sizeof(cntr_c));
    cntr_c.sa_handler = handler_SIGINT;
    cntr_c.sa_flags = 0;
    if (sigaction(SIGINT, &cntr_c, NULL) != 0){
        printf("ERROR binding SIGINT handler.\n");
        exit(1);
    }
    while (1){
    }
}

