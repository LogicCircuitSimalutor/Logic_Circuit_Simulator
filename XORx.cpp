#include <iostream>
#include <string>
#include <vector>
#include "XORx.h"

XORx::~XORx(){

}

void XORx::CalculateOutput(){
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
		Gate * tmp = *itr;
		temp_bit = *itr_select;
		temp_output = temp_output ^ tmp->getLogicState(temp_bit);
		itr++;
		itr_select++;
	}
	if(temp_output != this->getLogicState(temp_bit)){
		this->setLogicState(temp_output);
		this->changeDeltaOnOutput();
	}
	setDelta(0);
}


void XORx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}