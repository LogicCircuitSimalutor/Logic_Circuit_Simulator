#ifndef _OutputGate_H_
#define _OutputGate_H_

#include <iostream>
#include <string.h>
#include "Gate.h"

using namespace std;

class OutputGate : public Gate {

public:

	//Constructeur
	OutputGate(string name, bool logicState = 0) : 
	Gate(name, 0, logicState)
	{
		setLevel(0);
	}

	~OutputGate();

	void connectGate(Gate* g);

	void print(ostream& out) const;

	void CalculateOutput();


};

#endif