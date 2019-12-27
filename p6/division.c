//////////////////////////////////
// Main File:        division.c
// This File:        division.c
// Other Files:      intdate.c sendsig.c
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
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int count = 0;
/* This is the SIGINT handler
 * Prints number of operations completed and terminates
 */
void handler_SIGINT(){
    printf("\nTotal number of operations successfully completed:"
    " %d\nThe program will be terminated.\n", count);
    exit(0);
}

/* This is the SIGFPE handler
 * Show divisioin error, prints number of operations completed 
 * and terminates
 */
void handler_SIGFPE(){
    printf("Error: a division by 0 operation was attempted.\n"
    "Total number of operations completed successfully:"
    " %d\nThe program will be terminated.\n", count);
    exit(0);
}


/* This program takes 2 numbers as inputs
 * prints the quotion and remainder, 
 * and counts number of opertions completed before terminates
 */

int main(){
    struct sigaction div0;
    memset (&div0, 0, sizeof(div0));
    div0.sa_handler = handler_SIGFPE;
    div0.sa_flags = 0;
    if (sigaction(SIGFPE, &div0, NULL) != 0){
        printf("ERROR binding SIGFPE handler.\n");
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
    
    int a, b;
    char num[100];
    while (1){
        printf("Enter first integer: ");
        if (fgets(num, 100, stdin) == NULL){
            printf("Fail to read user input\n");
            exit(1);
        }
        a = atoi(num);
        printf("Enter second integer: ");
        if (fgets(num, 100, stdin) == NULL){
            printf("Fail to read user input\n");
            exit(1);
        }
        b = atoi(num);
        printf("%d / %d is %d with a remainder of %d\n", a, b, a/b, a%b);
        count++;
    }
}
