#include<stdio.h>
#include<string.h>
#include "mypopen_mypclose.h"

//Global Variables used amongst multiple functions
Process process[MAX_PROCESSES];
int counter = 0;

/**
 * @brief Opens a process by creating a pipe, forking, and invoking the shell.
 *
 * @param command The command to execute.
 * @param type The type of operation, either "r" for reading or "w" for writing.
 * @return FILE* The file pointer to the pipe stream.
 */
FILE *mypopen(char *command, char *type){
    //Declare new File fp
    FILE *fp;
    //Variable for both ends of the pipe
    int p[2];

    //Creates a pipe and checks if it was sucessfull
    if(pipe(p) == -1){
        perror("Fehler beim erstellen der Pipe");
        return NULL;
    }
    
    //Variable to store the Process ID
    pid_t pid =  fork();

    //Checks if fork was sucessfull
    if (pid == -1){
        perror("Fehler beim erstellen eines child processes\n");
        close(p[0]);
        close(p[1]);
        return NULL;
    }
    
    //Child Process
    if(pid == 0){ 
        //Check if write or read access
        if (strcmp(type, "r") == 0){
            //Closes the read end of child process to avoid conflict with parent process
            close(p[0]);
            //Redirects stdout to the pipe and checks if dup2 was executed sucessfully
            if (dup2(p[1], STDOUT_FILENO) == -1) {
                perror("dup2 error");
                exit(EXIT_FAILURE);
            }
            //Closes write end after redirection
            close(p[1]);
        }else if (strcmp(type, "w") == 0){
            //Closes the write end of child process to avoid conflict with parent process
            close(p[1]);
            //Redirects stdin to the pipe and checks if dup2 was executed sucessfully
            if (dup2(p[0], STDIN_FILENO) == -1) {
                perror("dup2 error");
                exit(EXIT_FAILURE);
            }
            //Closes read end after redirection
            close(p[0]);
        }
        //
        execl("/bin/sh", "sh", "-c", command, (char *) NULL);
        perror("execl error");
        exit(EXIT_FAILURE);

    }else{ 
        //Parent Process
        if(strcmp(type, "r") == 0){
            //Close the write end
            close(p[1]);
            //Read from the pipe
            fp = fdopen(p[0], "r");
        }else if (strcmp(type, "w") == 0){
            //Close the read end
            close(p[0]);
            //Write in the pipe
            fp = fdopen(p[1], "w");
        }

        //Checks if file was opened sucessfully
        if (fp == NULL){
            perror("fdopen error");
            return NULL;
        }
    }

    //Saves Process ID and Pipe File in struct for further use
    process[counter].pid = pid;
    process[counter].fp = fp;
    //Increases counter for further use
    counter++;

    return fp;
}

/**
 * @brief Gets the process information.
 *
 * @return Process* Pointer to the array of Process structs.
 */
Process *get_process_info(){
    //Returns the values saved in struct
    return process;
}