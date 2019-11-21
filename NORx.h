#ifndef _NORx_H_
#define _NORx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class NORx : public FunctionGate{

public:

	NORx(string name, int NbInput, bool logicState = 0) : 
	Gate(name, NbInput, logicState),
	FunctionGate(name, NbInput, logicState){

	}

	~NORx();

	void CalculateOutput();

	//void connectGate(Gate* g);

	void print(ostream& out) const;


};

#endif