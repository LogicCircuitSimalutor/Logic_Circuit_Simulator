#ifndef _NANDx_H_
#define _NANDx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class NANDx : public FunctionGate{

public:

	NANDx(string name, int NbInput, bool logicState = 0) : 
	Gate(name, NbInput, logicState),
	FunctionGate(name, NbInput, logicState){

	}

	~NANDx();

	void CalculateOutput();

	//void connectGate(Gate* g);

	void print(ostream& out) const;


};

#endif