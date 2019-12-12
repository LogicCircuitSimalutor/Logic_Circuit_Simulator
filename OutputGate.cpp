#include <iostream>
#include <vector>
#include "OutputGate.h"

void OutputGate::print(ostream& out) const{
	out << "\t\t ===== OUTPUT ===== " << endl;
	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	Gate::print(out);
}

OutputGate::~OutputGate(){

}

void OutputGate::connectGate(Gate* g, int pos){
	 //this->addOutput(g);

	 g->addInput(this);

}

void OutputGate::CalculateOutput(){
	const vector <Gate *>* input = getInput();
	vector <Gate *>::const_iterator itr = input->begin();
	Gate * tmp = *itr;
	const vector <int>* bitSelection = getSelectBit();
	vector <int>::const_iterator itr_select = bitSelection->begin();
	bool temp_output = tmp->getLogicState(*itr_select);

	if(temp_output != this->getLogicState()){
 		this->setLogicState(temp_output);
	}

	setDelta(0);
}
