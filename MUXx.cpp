#include <iostream>
#include <string>
#include <vector>
#include "MUXx.h"
#include <math.h>       /* pow */
#include <algorithm>    // std::reverse

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

	if(getSizeInput() != pow(2,getSizeSel()))
	{
		cout << "ERROR :: Number of selectors dont match nbinput = " << getSizeInput() << " sizeSel = " << getSizeSel() << " pow =" << pow(2,getSizeSel())  << endl;
	 exit(1);
	}
	cout << "Number of selectors  match nbinput = " << getSizeInput() << " sizeSel = " << getSizeSel() << " pow =" << pow(2,getSizeSel())  << endl;

	std::reverse(m_vectorSel.begin(),m_vectorSel.end());//reverse LSB and MSB

	int value_sel=0;
	int itr =0;
	for(std::vector<Gate*>::iterator itrv=m_vectorSel.begin();itrv!=m_vectorSel.end();itrv++)
	{
		Gate * tmp = *itrv;
	// cout << "itrv = " << itrv << endl;
	// cout << endl<<  double(m_vectorSel.size()-itrv) << "^" << double(m_vectorSel[itrv]) <<endl;
		value_sel += (pow(2,itr) * tmp->getLogicState()) ;
		itr++;
	}
	cout << "value sel = " << value_sel << endl;
	bool temp_output =0;


	const vector <Gate *>* input = getInput();

	int tmp =0;

	for(vector <Gate *>::const_iterator itrv = input->begin();itrv!=input->end();itrv++)
	{
		Gate * gtmp = *itrv;
		if(tmp == value_sel)
		{
			temp_output=gtmp->getLogicState();
			itrv=input->end();
		}
		tmp++;
	}

	if(temp_output != this->getLogicState()){
 		this->setLogicState(temp_output);
 		this->changeDeltaOnOutput();
	}

	setDelta(0);
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
