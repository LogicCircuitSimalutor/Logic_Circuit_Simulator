#ifndef _ANDx_H_
#define _ANDx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class ANDx : public FunctionGate{

public:

	ANDx(string name, int NbInput, bool logicState = 0) : 
	Gate(name, NbInput, logicState),
	FunctionGate(name, NbInput, logicState){

	}

	~ANDx();

	void CalculateOutput();

	// void connectGate(Gate* g);

	void print(ostream& out) const;


};

#endif