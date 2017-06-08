// The first integer in the array (element 0) is set up and opened for reading, while the second integer 
// (element 1) is set up and opened for writing. Visually speaking, the output of fd1 becomes the input for fd0

// If the parent wants to receive data from the child, it should close fd1, and the child should close fd0
// If the parent wants to send data to the child, it should close fd0, and the child should close fd1

// fd[0] is set up for reading, fd[1] is set up for writing

#include "Pipe.h"
#include "Connector.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

Pipe::Pipe(Shell* leftChild, Shell* rightChild): Connector(leftChild, rightChild) { }
Pipe::Pipe(): Connector() { }

bool execute() {
    int fd[2];
    pid_t childpid;

    pipe(fd);
        
    if((childpid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if(childpid == 0) {
        /* Child process closes up input side of pipe */
        close(fd[0]);

        /* Send "string" through the output side of pipe */
        write(fd[1], string, (strlen(string)+1));
        exit(0);
    }
    else {
        /* Parent process closes up output side of pipe */
        close(fd[1]);
    }
        
    return(0);
}

