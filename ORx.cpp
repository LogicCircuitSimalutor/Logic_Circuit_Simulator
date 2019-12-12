#include <iostream>
#include <string>
#include <vector>
#include "ORx.h"

ORx::~ORx(){

}

// void ORx::CalculateOutput(){
// 	const vector <Gate * >* input = getInput();
// 	vector <Gate *>::const_iterator itr = input->begin();
// 	Gate * tmp = *itr;
// 	itr++;
// 	bool temp_output = tmp->getLogicState();

// 	while(itr != input->end()){
// 		Gate * tmp = *itr;
// 		temp_output = temp_output || tmp->getLogicState();
// 		itr++;
// 	}
// 	if(temp_output != this->getLogicState()){
// 		this->setLogicState(temp_output);
// 		tmp->changeDeltaOnOutput();
// 	}
// 	setDelta(0);
// }

void ORx::CalculateOutput(){
	const vector <Gate *>* input = getInput();
	const vector <int>* bitSelection = getSelectBit();
	vector <Gate *>::const_iterator itr = input->begin();
	vector <int>::const_iterator itr_select = bitSelection->begin();
	bool temp_output;
	int temp_bit;

	while(itr != input->end()){
		Gate * tmp = *itr;
		temp_bit = *itr_select;
		temp_output = tmp->getLogicState(temp_bit);

		if(temp_output == 1){
 			itr = input->end();
		}else{
			itr++;
		}
	}

	if(temp_output != this->getLogicState(temp_bit)){
 		this->setLogicState(temp_output, temp_bit);
 		this->changeDeltaOnOutput();
	}

	setDelta(0);
}


void ORx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}