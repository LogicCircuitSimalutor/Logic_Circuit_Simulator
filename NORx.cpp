#include <iostream>
#include <string>
#include <vector>
#include "NORx.h"

NORx::~NORx(){

}

// void NORx::CalculateOutput(){
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
// 	temp_output = !temp_output;
// 	if(temp_output != this->getLogicState()){
// 		this->setLogicState(temp_output);
// 		tmp->changeDeltaOnOutput();
// 	}
// 	setDelta(0);
// }

void NORx::CalculateOutput(){
	const vector <Gate *>* input = getInput();
	vector <Gate *>::const_iterator itr = input->begin();
	bool temp_output;

	while(itr != input->end()){
		Gate * tmp = *itr;
		temp_output = tmp->getLogicState();

		if(temp_output == 1){
 			itr = input->end();
		}else{
			itr++;
		}
	}

	if(!temp_output != this->getLogicState()){
 		this->setLogicState(!temp_output);
 		this->changeDeltaOnOutput();
	}

	setDelta(0);
}



void NORx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
}