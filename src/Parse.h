#ifndef __PARSE_H__
#define __PARSE_H__

#include "Shell.h"
#include "Connector.h"

#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Parse {
    protected:
    	void createFork(vector<string> &,unsigned, unsigned);
        vector<Shell*> exec_cmds_vector;
    public:
        Parse() {}
        void par(string);
        
};

#endif 

