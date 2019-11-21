#include <iostream>
#include "FunctionGate.h"

FunctionGate::~FunctionGate(){

}

void FunctionGate::connectGate(Gate* g){
	 this->addOutput(g);

	 g->addInput(this);

}

void FunctionGate::print(ostream& out) const{
	
}

// void FunctionGate::changeDeltaOnOutput(){
// 	const vector <Gate * >* output = getOutput();
// 	vector <Gate * >::const_iterator itr = output->begin();
// 	while(itr != output->end()){
// 		Gate * tmp = *itr;
// 		tmp->setDelta(1);
// 		itr++;
// 	}
//}