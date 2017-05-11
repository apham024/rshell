#include "Parse.h"
#include "Forker.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <cstdio>

using namespace std;

void Parse::createFork(vector<string> &cmds_vector, unsigned i, unsigned j) {
    vector<string> cmd;
    for (unsigned k = i; k < j; ++k) {
        if (cmds_vector.at(k) != "\"") {
            cmd.push_back(cmds_vector.at(k));
        }
    }
    exec_cmds_vector.push_back(new Forker(cmd));
}


void Parse::par(string in) {
    const string a = "&&";
    const string o = "||";
    const string s = ";";
    
    // parse command line and store in cmds_vector 
    char cmds[1024];
    char *ptr;
    
    vector<string> cmds_vector;
    strcpy(cmds, in.c_str());
    // parse white space
    ptr = strtok(cmds, " "); 
    while (ptr != NULL) {
        // store parsed commands into cmds_vector
        cmds_vector.push_back(ptr);
        ptr = strtok(NULL, " ");
    }
    
    // push elements from cmds_vector to exec_cmds_vector until a connector
    // execute everything before connector then clear
    // check if the last command pass or fail

    stack<Connector*> cmd_stack; 
    
    // comment case
    for (unsigned j = 0; j < cmds_vector.size(); ++j) {
        if ((cmds_vector.at(j))[0] == '#') {
            cmds_vector.resize(j);
            break;
        }
    }
    
    unsigned i;
    for (i = 0; i < cmds_vector.size();++i) {
        // transfers commands
        string indexString = cmds_vector.at(i);
        
        if (cmds_vector.at(i) == a) {
            // checks to see if connector is &&
            // pushes new operator onto stack
            cmd_stack.push(new And());
        }
        else if (cmds_vector.at(i) == o) {
            // checks to see if conn is ||
            // pushes new operator onto stack
            cmd_stack.push(new Or());
        }
        else if (cmds_vector.at(i) == s) {
            // checks to see if conn is ;
            // pushes new operator onto stack
            cmd_stack.push(new SemiColon());
        }

        else { // iterates until find a conn
            unsigned j = 0;
            for (j = i; j < cmds_vector.size(); ++j) {
                // if connector is found .....
                if (cmds_vector.at(j) == a || 
                    cmds_vector.at(j) == o ||
                    cmds_vector.at(j) == s) {
                        // stores strings into new fork
                        createFork(cmds_vector, i, j);
                        i = j - 1; // needed to add the conn
                        break;
                }
            }
            // if conn not found, it's at the end of the cmds_vector
            if (j >=  cmds_vector.size()) {
                // creates new fork
                createFork(cmds_vector, i, j);
                break;
            }
        }
    }
    
    if (!exec_cmds_vector.empty() && exec_cmds_vector.at(0)->execute()) {
        exec_cmds_vector.clear();
    }
}

