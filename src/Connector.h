#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "Shell.h"
#include <stdlib.h>


class Connector : public Shell {
	protected:
	    Shell* leftChild;
	    Shell* rightChild;

	public:
		// sets id to conn for program to know when to check for operators
		Connector() : leftChild(NULL), rightChild(NULL) { id = "connector"; } 
		// error checking function for children
		void errorCheck();
		// setter functions
		void setLeftChild(Shell* left);
		void setRightChild(Shell* right);
		virtual bool execute() = 0;
};

class And : public Connector {
    public:
        And() {}
        bool execute();
};

class Or : public Connector {
    public:
        Or() {}
        bool execute();
};

class SemiColon : public Connector {
    public:
        SemiColon() {}
        bool execute();
};

class Parentheses : public Connector {
    public:
      // only marks for left parentheses
      Parentheses() { id = "("; }
      bool execute();
};

#endif
