#include "Shell.h"
#include "Forker.h"
#include "Parse.h"

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <cstring> 
#include <sstream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> 

using namespace std;

int main() {
	string userInput;	
	string arg = "";
	while(1) {
		Parse* p = new Parse();

		cout << "$ "; 
		// gets a command
		getline(cin, userInput);  
		// parses and runs program
		p->par(userInput);
		// to prevent memory leak
		delete p;
	}

	return 0;
}

