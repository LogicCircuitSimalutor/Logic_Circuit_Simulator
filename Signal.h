#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <iostream>
#include <string.h>
#include "Gate.h"

using namespace std;

class Signal {

public:
	int m_x;
	int m_y;
	Gate * m_gate;
	int m_prevLogicState;
	// int m_selectBit;

	//Constructor
	Signal(int x, int y, Gate* gate) : 
	m_x(x),
	m_y(y),
	m_gate(gate),
	m_prevLogicState(0)
	{

	} 

	//Destructor
	~Signal();

	void setX(const int x){
		m_x = x;
	}

	void setY(const int y){
		m_y = y;
	}

	int getX() const{
		return m_x;
	}

	int getY() const{
		return m_y;
	}

	// int getBit() const{
	// 	return m_selectBit;
	// }

	Gate* getAddrGate() const{
		return m_gate;
	}

	int getPrevLogicState() const{
		return m_prevLogicState;
	}

	void setPrevLogicState(int val){
		m_prevLogicState = val;
	}

};

#endif