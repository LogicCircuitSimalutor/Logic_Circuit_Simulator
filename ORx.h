#ifndef _ORx_H_
#define _ORx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class ORx : public FunctionGate{

public:

	ORx(string name, int NbInput, bool logicState = 0) : 
	Gate(name, NbInput, logicState),
	FunctionGate(name, NbInput, logicState){

	}

	~ORx();

	void CalculateOutput();

	// void connectGate(Gate* g);

	void print(ostream& out) const;


};

#endif