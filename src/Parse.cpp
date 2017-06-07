#include "Parse.h"
#include "Tester.h"
#include "Shell.h"

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

Fork::Fork(vector<string> &cmdLine) {
    cmd = cmdLine;
}

// executes commands using execvp
bool Fork::execute() {
    if (cmd.size() == 1 && cmd.at(0) == "exit") {
        exit(0);
    }
    
	//Changes cmdLine into a cstring array.
	vector<char*> argv;
	argv.resize(cmd.size() + 1);
	for (size_t i = 0; i != cmd.size(); ++i) {
		argv[i] = &cmd[i][0];
	}

	//Fork() and uses execvp(). The parent waits for the child to finish doing work.
    pid_t pid = fork();
    if (pid == -1) {
        //fork failed to execute
        perror("Could not fork: ");
        exit(1);
    }
    if (pid == 0) {
        // child process
        if (execvp(argv[0], argv.data()) == -1) {
            //failed to execute
            perror("Command not found: ");
            exit(1);
        }
    }
    if (pid > 0) {
        // parent process
        int status;
        waitpid(pid, &status, 0);

        if (WEXITSTATUS(status) == 0) {
            return true;
        } else if (WEXITSTATUS(status) == 1) {
            return false;
        }
    }
    
    return true;
}


// creates new Tester and pushes it into a temp vector to execute
void Parse::makeTester(vector<string> &cmds_vector, unsigned i, unsigned j) {
    // holds the rest of the commands (excluding Fork and Tester objects)
    vector<string> cmd;
    string filename;
    for (unsigned k = i; k < j; ++k) {
        // checks if it's a special character
        if (cmds_vector.at(k) != "\"") {
            cmd.push_back(cmds_vector.at(k));
        }
    }
    // temp vector only holds Tester and Fork objects
    exec_cmds_vec.push_back(new Tester(cmd, filename));
}

// creates new Fork and pushes it into a temp vector to execute
void Parse::makeFork(vector<string> &cmds_vector, unsigned i, unsigned j) {
    vector<string> cmd;
    // assigns k each element i in the vector to avoid being overwritten 
    for (unsigned k = i; k < j; ++k) {
        if (cmds_vector.at(k) != "\"") {
            cmd.push_back(cmds_vector.at(k));
        }
    }
    exec_cmds_vec.push_back(new Fork(cmd));
}

void Parse::makeTree(stack<Connector*> &cmd_stack) {
    // since stack is LIFO, set right child first
    if (!cmd_stack.empty()) {
        // to set right the child
        cmd_stack.top()->setRightChild(exec_cmds_vec.back());
        exec_cmds_vec.pop_back();
        // to set left the child
        cmd_stack.top()->setLeftChild(exec_cmds_vec.back());
        exec_cmds_vec.pop_back();
        // pushes onto exec_cmds_vec with fork and tester obj
        exec_cmds_vec.push_back(cmd_stack.top());
        cmd_stack.pop();
    }
}

    // CONNECTOR CASE: if first command returns true and if 
    // operator && is found, execute after operator as well
    // if first command is false and operator && is found, break 
    // the operator ; should work the same way 
    
    // if first command return false and && is found, then done
    // if first command returns true and || is found, then done
    // if first command returns false and || is found, then execute after operator

void Parse::parse(string input) {
    const string leftParen = "("; // FIX
    const string rightParen = ")"; // FIX
    const string a = "&&"; // WORKS
    const string o = "||"; // WORKS
    const string s = ";"; // WORKS
    
    for(unsigned i = 0; i < input.size(); i++) {

        if(input.at(i) == ';') {
            // inserts a space before the semicolon to distinguish it as its own cmd
            input.insert(i, " ");
            i++;
        }
        else if(input.at(i) == '(') {
            // inserts a space after the paren to distinguish it as its own cmd
            input.insert(i + 1, " ");
        }
        else if(input.at(i) == ')') {
            // inserts a space before the paren to distinguish it as its own cmd
            input.insert(i, " ");
            i++;
        }
        
    }

    // parse command line and store in cmds_vector 
    char cmds[1024];
    char *ptr;

    vector<string> cmds_vector;
    strcpy(cmds, input.c_str());
    // parse white space
    ptr = strtok(cmds, " "); 
    while(ptr != NULL) {
        // store parsed commands into cmds_vector
        cmds_vector.push_back(ptr);
        ptr = strtok(NULL, " ");
    }
    
    // push elements from cmds_vector to exec_cmds_vec until a connector
    // execute everything before connector then clear
    // check if the last command pass or fail

    stack<Connector*> cmd_stack; 
    
    // comment case
    for(unsigned j = 0; j < cmds_vector.size(); ++j) {
        if((cmds_vector.at(j))[0] == '#') {
            cmds_vector.resize(j);
            break;
        }
    }
    
    //unsigned i;
    // stack<char> p;
    for(unsigned i = 0; i < cmds_vector.size(); i++) {
        unsigned size = cmds_vector.size();
        
        // transfers commands
        string indexString = cmds_vector.at(i);
        
        // if(cmds_vector.at(i) == leftParen){
        //     p.push(cmds_vector.at(i));
        // } else if(cmds_vector.at(i)){
            
        // } else
        if(cmds_vector.at(i) == a) {

            // checks to see if connector is &&
            // pushes new operator onto stack
            makeTree(cmd_stack);
            cmd_stack.push(new And());
        }
        else if(cmds_vector.at(i) == o) {

            // checks to see if conn is ||
            // pushes new operator onto stack
            makeTree(cmd_stack);
            cmd_stack.push(new Or());
        }
        else if(cmds_vector.at(i) == s) {

            // checks to see if conn is ;
            // pushes new operator onto stack
            makeTree(cmd_stack);
            cmd_stack.push(new SemiColon());
        }
        
        else if(cmds_vector.at(i) == leftParen) {
            
            cmd_stack.push(new Parentheses());
        }
        
        else if(cmds_vector.at(i) == rightParen) {
            // while it's not "(", continue making the tree
            while(!cmd_stack.empty() && cmd_stack.top()->getID() != leftParen) {
                makeTree(cmd_stack);
            }
            // while(!cmd_stack.empty()){
                cmd_stack.pop();
            //}
        }
        
        // if user enters test -e or [ -e ...]
        else if (cmds_vector.at(i) == "test" || (cmds_vector.at(i) == "[" && cmds_vector.at(size - 1) == "]")) {
            if ((i + 1) == cmds_vector.size()) {
                break;
            }
            
            if (cmds_vector.at(i) == "test") {
                unsigned size = cmds_vector.size();
                
                // checks test pathname 
                // if that's not the case, checks test -e pathname 
                if ((i + 2) == size || (i + 3) == size) {
                    // calls makeTester and uses i + 1 to skip "test"
                    if ((i + 2) == size) {
                        vector<string>::iterator it = cmds_vector.begin() + i;
                        cmds_vector.insert( it + 1, "-e");
                    }
                    makeTester(cmds_vector, i + 1, i + 3);
                    i += 2;
                }
                
                // checks test pathname
                else if (cmds_vector.at(i + 2) == a || cmds_vector.at(i + 2) == o || cmds_vector.at(i + 2) == s ) {
                    //create Tester() with default flag
                    vector<string>::iterator it = cmds_vector.begin() + i;
                    cmds_vector.insert( it + 1 , "-e");
                    makeTester(cmds_vector, i + 1, i + 3);
                    i += 2; // to push connector
                }
                
                // checks test -e pathname
                else if (cmds_vector.at(i + 3) == a || cmds_vector.at(i + 3) == o || cmds_vector.at(i + 3) == s ) {
                    //create Tester with flag
                    makeTester(cmds_vector, i + 1, i + 3);
                    i += 2; // to push connector
                 
                }
            }
                    
            else if (cmds_vector.at(i) == "[") {
                if (cmds_vector.at(i + 2) == "]") {
                    //create Tester with default flag
                    vector<string>::iterator it = cmds_vector.begin() + i;
                    cmds_vector.insert( it + 1 , "-e");
                    makeTester(cmds_vector, i + 1, i + 3);
                    i += 3; // skip  "]"
                }
                        
                else if (cmds_vector.at(i + 3) == "]") {
                    //create Tester with flag
                    makeTester(cmds_vector, i + 1, i + 3);
                    i += 3; // skip "]"
                }
                        
                else {
                    cout << "Error: Invalid # of commands\n";
                }
            }

        }
        
        
        else { // iterates until find a connector
            unsigned j = 0;
            for (j = i; j < cmds_vector.size(); ++j) {
                // if connector is found .....
                if (cmds_vector.at(j) == a || cmds_vector.at(j) == o || cmds_vector.at(j) == s || cmds_vector.at(j) == rightParen) {
                    // stores strings into new fork
                    makeFork(cmds_vector, i, j);
                    i = j - 1; // needed to add the connector
                    break;
                }
            }
            // if conn not found, it's at the end of the cmds_vector
            if (j >=  cmds_vector.size()) {
                // creates new fork
                makeFork(cmds_vector, i, j);
                break;
            }
        }
    }
        
    // actually calls the function makeTree 
    while(!cmd_stack.empty()) {
        makeTree(cmd_stack);
    }
    
    // actually executes whatever is in the vector (fork, tester)
    if(!exec_cmds_vec.empty()) {
        exec_cmds_vec.at(0)->execute();
        exec_cmds_vec.clear();
    }
}

