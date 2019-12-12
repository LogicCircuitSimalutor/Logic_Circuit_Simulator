#include <iostream>
#include <string>
#include <vector>
#include "XNORx.h"

XNORx::~XNORx(){

}

void XNORx::CalculateOutput(){
	const vector <Gate * >* input = getInput();
	const vector <int>* bitSelection = getSelectBit();
	vector <Gate *>::const_iterator itr = input->begin();
	vector <int>::const_iterator itr_select = bitSelection->begin();
	Gate * tmp = *itr;
	int temp_bit = *itr_select;
	bool temp_output = tmp->getLogicState(temp_bit);
	itr++;
	itr_select++;

	while(itr != input->end()){
		temp_bit = *itr_select;
		Gate * tmp = *itr;
		temp_output = temp_output ^ tmp->getLogicState(temp_bit);
		itr++;
		itr_select++;
	}
	if(!temp_output != this->getLogicState(temp_bit)){
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