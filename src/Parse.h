#ifndef __PARSE_H__
#define __PARSE_H__

#include "Shell.h"
#include "Connector.h"

#include <iostream> 
#include <string>
#include <stack>

using namespace std;

class Fork : public Shell {
	protected:
		vector<string> cmd;
	public:
		Fork() {}
		Fork(vector<string> &);
		bool execute();
};

class Parse {
    protected:
        vector<Shell*> exec_cmds_vec; // this vector is only used for fork, tester, and tree objs
        void makeTree(stack<Connector*> &);
        void makeFork(vector<string> &,unsigned, unsigned);
        void makeTester(vector<string> &,unsigned, unsigned);
    public:
        Parse() {}
        void parse(string);
        
};

#endif 
