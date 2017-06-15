#ifndef __PIPE_H__
#define __PIPE_H__

#include "Connector.h"
// #include "Connector.cpp"

class Pipe : public Connector { // |, needs dup()
    public:
        Pipe();
        Pipe(Shell* leftChild, Shell* rightChild);
        bool execute();

};

class SingleInput : public Connector { // <
    private: 
        char filename[1024], coms[1024];
    public:
        SingleInput();
        SingleInput(char filename[1024], char coms[1024]);
        SingleInput(Shell* leftChild, Shell* rightChild);
        bool execute();
};

class SingleOutput : public Connector { // > overwrites the entire file
    private:
        char filename[1024], coms[1024];
    public:
        SingleOutput();
        SingleOutput(char filename[1024], char coms[1024]);
        SingleOutput(Shell* leftChild, Shell* rightChild);
        bool execute();
};

class DoubleOutput : public Connector { // >> adds onto the file, needs dup()
    private:
        char filename[1024], coms[1024];
    public:
        DoubleOutput();
        DoubleOutput(char filename[1024], char coms[1024]);
        DoubleOutput(Shell* leftChild, Shell* rightChild);
        bool execute();
};


#endif