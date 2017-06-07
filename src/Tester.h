#ifndef TESTER_H
#define TESTER_H

#include "Parse.h"

class Tester : public Fork {
    protected:
		string fileName;
	public:
	    Tester() {}
		Tester(vector<string> &v, string file);
//      bool e(); 
// 		bool f();
// 		bool d();
		bool execute();
};

#endif
