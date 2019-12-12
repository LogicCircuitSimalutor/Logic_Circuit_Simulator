#ifndef _InputGate_H_
#define _InputGate_H_

#include <iostream>
#include <string.h>
#include "Gate.h"

using namespace std;

class InputGate : public Gate {

public:

	//Constructeur
	InputGate(string name, bool logicState = 0) : 
	Gate(name, 0, logicState)
	{
		setLevel(0);
		setDelta(0);
	}

	~InputGate();

	void connectGate(Gate* g, int pos);

	void print(ostream& out) const;


};

#endif