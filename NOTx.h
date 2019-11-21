#ifndef _NOTx_H_
#define _NOTx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class NOTx : public FunctionGate{

public:

	NOTx(string name, bool logicState = 0) : 
	Gate(name, 1, logicState),
	FunctionGate(name, 1, logicState){

	}

	~NOTx();

	void CalculateOutput();

	// void connectGate(Gate* g);

	void print(ostream& out) const;


};

#endif