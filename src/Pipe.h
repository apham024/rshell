#ifndef __PIPE_H__
#define __PIPE_H__

#include "Connector.h"
#include "Connector.cpp"

class Pipe : public Connector { // |
    public:
        Pipe();
        Pipe(Shell* leftChild, Shell* rightChild);
        bool execute();

};

class SingleInput : public Connector { // <
    public:
        SingleInput();
        SingleInput(Shell* leftChild, Shell* rightChild);
        bool execute();
};

class SingleOutput : public Connector { // > overwrites the entire file
    public:
        SingleOutput();
        SingleOutput(Shell* leftChild, Shell* rightChild);
        bool execute();
};

class DoubleOutput : public Connector { // >> adds onto the file 
    public:
        DoubleOutput();
        DoubleOutput(Shell* leftChild, Shell* rightChild);
        bool execute();
};


#endif