#ifndef _XNORx_H_
#define _XNORx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class XNORx : public FunctionGate{

public:

	XNORx(string name, int NbInput, bool logicState = 0) : 
	Gate(name, NbInput, logicState),
	FunctionGate(name, NbInput, logicState){

	}

	~XNORx();

	void CalculateOutput();

	//void connectGate(Gate* g);

	void print(ostream& out) const;


};

#endif