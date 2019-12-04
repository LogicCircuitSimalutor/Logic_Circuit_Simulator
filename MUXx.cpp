#include <iostream>
#include <string>
#include <vector>
#include "MUXx.h"
#include <math.h>       /* pow */

MUXx::~MUXx(){

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
void MUXx::connectSel(Gate* Sel)
{
	m_vectorSel.push_back(Sel);
}

void MUXx::CalculateOutput(){
int value_sel=0;
	for(int itrv = 0;itrv!=m_vectorSel.size();itrv++)
	{
    // cout << endl<<  double(m_vectorSel.size()-itrv) << "^" << double(m_vectorSel[itrv]) <<endl;
    value_sel += (pow(2,itrv) * m_vectorSel[itrv]->getLogicState()) ;
	}
	//
	// const vector <Gate *>* input = getInput();
	// if(value_sel <= input->size())
	// {
	// 	vector <Gate * >::const_iterator itr;
	// 	int itrr=0;
	// 	for(itr = input->begin(); itrr!=value_sel;itrr++ )
	// 	{
	// 		itr++;
	// 	}
	//
	//
	// 	Gate * tmp = *itr;
	// 	//tmp = input[value_sel];
	// 	bool temp_output;
	// 	temp_output = tmp->getLogicState();
	// 	if(temp_output != this->getLogicState()){
	//  		this->setLogicState(temp_output);
	//  		tmp->changeDeltaOnOutput();
	// 	}
	//
	// }
	// else
	// {
	// 	cout << "			ERROR : Number of selectors too high for the MUX "  << this->getName() << endl;
	// }

}


void MUXx::print(ostream& out) const{

	out << "Address : " << this << endl;
	out << "Name : " << this->getName() << endl;
	out << "Logic value : " << this->getLogicState() << endl;
	out << "Delta value : " << this->getDelta() << endl;
	out << "Level : " << this->getLevel() << endl;
	Gate::print(out);
	out << "VECTOR SEL" << endl;
	for(unsigned int itr= 0; itr!=m_vectorSel.size();itr++)
	{
			out << m_vectorSel[itr]->getName() << endl; //faut que ca sorte correctement le vector de sel
	}
}
