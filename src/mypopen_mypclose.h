#ifndef MYOPEN_MYCLOSE_H
#define MYOPEN_MYCLOSE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Defining MAX Amount of processes
#define MAX_PROCESSES 256

//Declaring a struct
typedef struct{
    pid_t pid;
    FILE *fp;
}Process;

//Declaring gloabal variables
extern int counter;

//Declareing functions
extern FILE *mypopen(char *command, char *type);
extern int mypclose(FILE *fp);
extern Process *get_process_info();

#endif