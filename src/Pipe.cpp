// The first integer in the array (element 0) is set up and opened for reading, while the second integer 
// (element 1) is set up and opened for writing. Visually speaking, the output of fd1 becomes the input for fd0

// If the parent wants to receive data from the child, it should close fd1, and the child should close fd0
// If the parent wants to send data to the child, it should close fd0, and the child should close fd1

// fd[0] is set up for reading, fd[1] is set up for writing

#include "Pipe.h"
#include "Connector.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

Pipe::Pipe(): Connector(leftChild, rightChild){ id = "|";}
Pipe::Pipe(Shell* leftChild, Shell* rightChild): Connector(leftChild, rightChild) { }

bool Pipe::execute() { // FIX: need dup() and pipe()
    // int fd[2], pid;
    
    // if(pipe(fd) == -1){
    //     perror("PIPE");
    //     return false;
    // }

    // int input = open()

    return true;
}

SingleInput::SingleInput(): Connector(leftChild, rightChild){ id = "<";}
SingleInput::SingleInput(char* filename, char* coms):Connector() {filename = filename; coms = coms;}
SingleInput::SingleInput(Shell* leftChild, Shell* rightChild): Connector(leftChild, rightChild){}

bool SingleInput::execute() {
    
    
    
    
    //     close(0);
    //     open(getFilename(), O_RDONLY);
    // if(fork() == 0){
    //     // execvp the left side of >
    // }
    // FIX
    
    return true;
}

SingleOutput::SingleOutput(): Connector(leftChild, rightChild){ id = ">";}
SingleOutput::SingleOutput(char* filename, char* coms):Connector() {filename = filename; coms = coms; }
SingleOutput::SingleOutput(Shell* leftChild, Shell* rightChild): Connector(leftChild, rightChild){}
bool SingleOutput::execute(){
    // int out = open(filename, O_WRONLY|O_CREAT, 0666);        // set of permission to write/make
    // similar/ opposite of input
    // execvp the left side of >
    // filename should be in char* which is the right side of >
    
    return true;
}


DoubleOutput::DoubleOutput(): Connector(leftChild, rightChild){ id = ">>";}
DoubleOutput::DoubleOutput(char* filename, char* coms):Connector() {filename = filename; coms = coms;}
DoubleOutput::DoubleOutput(Shell* leftChild, Shell* rightChild):  Connector(leftChild, rightChild){}

bool DoubleOutput::execute(){
    
    //tba
    
    return true;
}
