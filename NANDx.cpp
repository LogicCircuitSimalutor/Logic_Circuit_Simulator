#include <iostream>
#include <string>
#include <vector>
#include "NANDx.h"

NANDx::~NANDx(){

}

// void NANDx::CalculateOutput(){
// 	const vector <Gate * >* input = getInput();
// 	vector <Gate *>::const_iterator itr = input->begin();
// 	Gate * tmp = *itr;
// 	itr++;
// 	bool temp_output = tmp->getLogicState();

// 	while(itr != input->end()){
// 		Gate * tmp = *itr;
// 		temp_output = temp_output && tmp->getLogicState();
// 		itr++;
// 	}
// 	temp_output = !temp_output;
// 	if(temp_output != this->getLogicState()){
// 		this->setLogicState(temp_output);
// 		tmp->changeDeltaOnOutput();
// 	}
// 	setDelta(0);
// }

void NANDx::CalculateOutput(){
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
		// cout << "porte nandx value de " << tmp->getName() << " vaut  " << temp_output << endl;
		if(temp_output == 0){
 			itr = input->end();
		}else{
			itr++;
		}
	}

	if(!temp_output != this->getLogicState(temp_bit)){
		// cout << "temp_output = " << !temp_output << endl;
 		this->setLogicState(!temp_output, temp_bit);
 		this->changeDeltaOnOutput();
	}

	setDelta(0);
}

void NANDx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}