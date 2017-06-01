#ifndef __SHELL_H__
#define __SHELL_H__
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class Shell {
	protected:
		string id;
	public:
		Shell() {}
		virtual bool execute() = 0;
		string getID() { return id; };

};

#endif


