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

void OutputGate::connectGate(Gate* g){
	 //this->addOutput(g);

	 g->addInput(this);

}

void OutputGate::CalculateOutput(){
	const vector <Gate *>* input = getInput();
	vector <Gate *>::const_iterator itr = input->begin();
	Gate * tmp = *itr;
	bool temp_output = tmp->getLogicState();

	if(temp_output != this->getLogicState()){
 		this->setLogicState(temp_output);
	}

	setDelta(0);
}
