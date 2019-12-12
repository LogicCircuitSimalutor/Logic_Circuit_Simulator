#ifndef _FA_H_
#define _FA_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class FA : public FunctionGate{

public:

	bool m_logicState[2];

	FA(string name, bool logicState = 0) : 
	Gate(name, 3, logicState),
	FunctionGate(name, 3, logicState){
		m_logicState[0] = logicState;
		m_logicState[1] = logicState;
	}

	~FA();

	void CalculateOutput();

	//void connectGate(Gate* g);

	void setLogicState(const bool logic, int pos = 0){
		m_logicState[pos] = logic;
	}

	bool getLogicState(int pos = 0) const{
		return m_logicState[pos];
	}

	void print(ostream& out) const;


};

#endif