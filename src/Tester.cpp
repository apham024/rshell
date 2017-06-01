#include "Tester.h"
#include "Shell.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>

using namespace std;

// $ test -e test/file/path
// $ [ -e test/file/path ]

Tester::Tester(vector<string> &v, string file) : Fork(v) { fileName = file; }

bool Tester::execute() {
    // the results are stored in exists and the return value of stat 
    // is an error code indicating if the stat operation succeeded or failed
    
    char f[1024];
    fileName = cmd.at(1);
    struct stat exists; 
    
    // since stat() has a pointer for first param, we need to strcpy to copy the data that is pointed to
    strcpy(f, fileName.c_str());

    // if user does not specify which flag, automatically sets flag to "-e"
    // FIX: does not execute "-e" if no flag given -- out of range error elsewhere
    
    if(cmd.size() == 1 || cmd.at(0).at(0) != '-') { 
        // cmd.insert(cmd.at(1), "-e"); 
        cmd.insert(cmd.begin(), "-e ");
    }
    
    if(cmd.at(0) == "-e") {
    // stat() stats the file pointed to by path and fills in exists
        if(stat(f, &exists) == 0) {
            cout << "(True)\n";
            return true;
        }
        else {
            cout << "(False)\n";
        }
    }
    else if(cmd.at(0) == "-f") {
        if(stat(f, &exists) == 0 && S_ISREG(exists.st_mode)) {
            cout << "(True)\n";
            return true;
        }
        else {
            cout << "(False)\n";
        }
    
    }
    else if(cmd.at(0) == "-d") {
        if(stat(f, &exists) == 0 && S_ISDIR(exists.st_mode)) {
            cout << "(True)\n";
            return true;
        }
        else {
            cout << "(False)\n";
        }

    }
    
    else {
        cout << "Error: Invalid flag.\n";
    }
    return false;
    
}