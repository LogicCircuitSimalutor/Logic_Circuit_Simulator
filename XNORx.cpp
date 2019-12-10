#include <iostream>
#include <string>
#include <vector>
#include "XNORx.h"

XNORx::~XNORx(){

}

void XNORx::CalculateOutput(){
	const vector <Gate * >* input = getInput();
	vector <Gate *>::const_iterator itr = input->begin();
	Gate * tmp = *itr;
	itr++;
	bool temp_output = tmp->getLogicState();

	while(itr != input->end()){
		Gate * tmp = *itr;
		temp_output = temp_output ^ tmp->getLogicState();
		itr++;
	}
	if(!temp_output != this->getLogicState()){
		this->setLogicState(!temp_output);
		this->changeDeltaOnOutput();
	}
	setDelta(0);
}


void XNORx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}