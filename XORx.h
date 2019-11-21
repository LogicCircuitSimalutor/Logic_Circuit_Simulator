#ifndef _XORx_H_
#define _XORx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class XORx : public FunctionGate{

public:

	XORx(string name, int NbInput, bool logicState = 0) : 
	Gate(name, NbInput, logicState),
	FunctionGate(name, NbInput, logicState){

	}

	~XORx();

	void CalculateOutput();

	//void connectGate(Gate* g);

	void print(ostream& out) const;


};

#endif