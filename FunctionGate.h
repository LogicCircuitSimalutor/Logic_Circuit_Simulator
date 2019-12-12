#ifndef _FunctionGate_H_
#define _FunctionGate_H_

#include <iostream>
#include <string.h>
#include "Gate.h"

using namespace std;

class FunctionGate : public virtual Gate {


public:

	//Constructeur
	FunctionGate(string name, int NbInput, bool logicState = 0) : 
	Gate(name, NbInput, logicState){

	}

	virtual ~FunctionGate();

	virtual void CalculateOutput() = 0;

	void connectGate(Gate* g, int pos);

	virtual void print(ostream& out) const;


};

#endif