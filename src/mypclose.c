#include <stdio.h>
#include "mypopen_mypclose.h"
#include <sys/wait.h>

/**
 * @brief Closes the pipe stream and waits for the associated process to terminate.
 *
 * @param fp The file pointer to the pipe stream.
 * @return int The exit status of the child process.
 */
int mypclose(FILE *fp){
    int status;
    pid_t pid;
    //Declaring new process and initializing it with values from mypopen
    Process *process = get_process_info();

    //For loop running through all porcesses
    for(int i = 0; i < counter; i++){
        //Check if the file pointer matches the current process's file pointer
        if (process[i].fp == fp){
            pid = process[i].pid;
            //closes the file pointer of the moved process entry
            fclose(process[i].fp);
            //Removes the entry from the array and replacing it with the last entry
            process[i] = process[counter - 1];
            //Decrements the process counter
            counter --;
            break;
        }
    }

    //Waits for the child process to change state and checks if it was sucessfull
    if(waitpid(pid, &status, 0) == -1){
        printf("Waitpid error\n");
        return -1;
    }

    //Checks if child process terminated normally
    if(WIFEXITED(status)){
        //Gets the exit status of the 
        status = WEXITSTATUS(status);
    } else {
        return -1;
    }

    return status;
}