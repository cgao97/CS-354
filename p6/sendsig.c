//////////////////////////////////
// Main File:        sendsig.c
// This File:        sendsig.c
// Other Files:      intdate.c division.c
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
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
char* sig_type;
int pid;
int sig;

/* This program sends a signal to another process
 * -i:SIGUSR1
 * -u:SIGINT
 *
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Usage: <signal type> <pid>\n");
        exit(1);
    }
    
    pid = atoi(argv[2]);

    if (!strcmp(argv[1], "-i")){
        sig = SIGINT;   
    }
    if (!strcmp(argv[1], "-u")){
        sig = SIGUSR1;
    }

    if (kill(pid, sig) != 0){
        printf("Fail to send signal.\n");
        exit(1);
    }
}
