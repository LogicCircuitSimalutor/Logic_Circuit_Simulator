#ifndef _MUXx_H_
#define _MUXx_H_

#include <iostream>
#include <string>
#include "Gate.h"
#include "FunctionGate.h"

using namespace std;

class MUXx : public FunctionGate{
vector <Gate *> m_vectorSel;
vector<int> m_selectBit;
public:

	MUXx(string name, int NbInput, bool logicState = 0) :
	Gate(name, NbInput, logicState),
	FunctionGate(name, NbInput, logicState)
	{
	}

	~MUXx();

	void CalculateOutput();

	void connectSel(Gate* Sel, int pos);
	// void connectGate(Gate* g);

	void print(ostream& out) const;

	vector<Gate *> *getVectorSel()
	{
		return &m_vectorSel;
	}

	int getSizeSel(){
		return m_vectorSel.size();
	}

	vector<int> *getVectorBit()
	{
		return &m_selectBit;
	}

	void addBitSelection(int bit);

	bool checkNumberSelector();


};

#endif
