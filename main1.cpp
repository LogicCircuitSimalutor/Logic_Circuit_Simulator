/*>
*	This file gathers these follower unit tests : 
*
*	- Create some Gates
*	- Try to connect Inputs & Gates
*	- Print Gates & Inputs structure
* 	- Evaluate Gates multi-inputs and update delta
*/
#include <iostream>
#include <string.h>
#include "main1.h"


using namespace std;

int main(int argc, char const *argv[]){

	//Inputs & Gates initialization

	Gate* IN1 = new InputGate("IN1", 1);
	Gate* IN2 = new InputGate("IN2", 1);
	Gate* IN3 = new InputGate("IN3", 0);
	Gate* IN4 = new InputGate("IN4", 1);

	Gate* AND2 = new ANDx("AND2", 2, 0);
	Gate* OR2 = new ORx("OR2", 2, 0);
	Gate* NAND2 = new NANDx("NAND2", 2, 0);
	Gate* XOR2 = new XORx("XOR2", 2, 0);
	Gate* NOR2 = new NORx("NOR2", 2, 0);
	Gate* NOTIN = new NOTx("NOT", 0);

	Gate* AND4 = new ANDx("AND4", 4, 1);
	Gate* OR4 = new ORx("OR4", 4, 1);
	Gate* NAND4 = new NANDx("NAND4", 4, 0);
	Gate* XOR4 = new XORx("XOR4", 4, 0);
	Gate* NOR4 = new NORx("NOR4", 4, 0);

	Gate* Connection = new ANDx("Connection_test_gate", 11, 1);


	/*> IN1 testing */
	cout << "======================================" << endl;
	cout << "START OF IN1 TESTING..." << endl;
	IN1->connectGate(AND2);
	IN1->connectGate(OR2);
	IN1->connectGate(NAND2);
	IN1->connectGate(XOR2);
	IN1->connectGate(NOR2);
	IN1->connectGate(NOTIN);

	cout << *IN1 << endl;
	cout << "END OF IN1 TESTING..." << endl;
	cout << "======================================" << endl;


	/*> IN2 testing */
	cout << "======================================" << endl;
	cout << " START OF IN2 TESTING..." << endl;
	IN2->connectGate(AND2);
	IN2->connectGate(OR2);
	IN2->connectGate(NAND2);
	IN2->connectGate(XOR2);
	IN2->connectGate(NOR2);

	cout << *IN2 << endl;
	cout << "END OF IN2 TESTING..." << endl;
	cout << "======================================" << endl;

	/*> AND2 testing */
	cout << "======================================" << endl;
	cout << "START OF AND2 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	AND2->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *AND2 << endl;
	cout << "Calculation of output...." << endl;
	AND2->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *AND2 << endl;
	cout << "END OF AND2 TESTING..." << endl;
	cout << "======================================" << endl;

	/*> OR2 testing */
	cout << "======================================" << endl;
	cout << "START OF OR2 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	OR2->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *OR2 << endl;
	cout << "Calculation of output...." << endl;
	OR2->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *OR2 << endl;
	cout << "END OF OR2 TESTING..." << endl;
	cout << "======================================" << endl;

		/*> NAND2 testing */
	cout << "======================================" << endl;
	cout << "START OF NAND2 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	NAND2->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *NAND2 << endl;
	cout << "Calculation of output...." << endl;
	NAND2->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *NAND2 << endl;
	cout << "END OF NAND2 TESTING..." << endl;
	cout << "======================================" << endl;

		/*> NOR2 testing */
	cout << "======================================" << endl;
	cout << "START OF NOR2 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	NOR2->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *NOR2 << endl;
	cout << "Calculation of output...." << endl;
	NOR2->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *NOR2 << endl;
	cout << "END OF NOR2 TESTING..." << endl;
	cout << "======================================" << endl;

		/*> XOR2 testing */
	cout << "======================================" << endl;
	cout << "START OF XOR2 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	XOR2->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *XOR2 << endl;
	cout << "Calculation of output...." << endl;
	XOR2->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *XOR2 << endl;
	cout << "END OF XOR2 TESTING..." << endl;
	cout << "======================================" << endl;

		/*> NOT testing */
	cout << "======================================" << endl;
	cout << "START OF NOT TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	NOTIN->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *NOTIN << endl;
	cout << "Calculation of output...." << endl;
	NOTIN->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *NOTIN << endl;
	cout << "END OF NOT TESTING..." << endl;
	cout << "======================================" << endl;

	IN1->connectGate(AND4);
	IN1->connectGate(OR4);
	IN1->connectGate(NAND4);
	IN1->connectGate(XOR4);
	IN1->connectGate(NOR4);

	IN2->connectGate(AND4);
	IN2->connectGate(OR4);
	IN2->connectGate(NAND4);
	IN2->connectGate(XOR4);
	IN2->connectGate(NOR4);

	IN3->connectGate(AND4);
	IN3->connectGate(OR4);
	IN3->connectGate(NAND4);
	IN3->connectGate(XOR4);
	IN3->connectGate(NOR4);

	IN4->connectGate(AND4);
	IN4->connectGate(OR4);
	IN4->connectGate(NAND4);
	IN4->connectGate(XOR4);
	IN4->connectGate(NOR4);

	/*> AND4 testing */
	cout << "======================================" << endl;
	cout << "START OF AND4 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	AND4->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *AND4 << endl;
	cout << "Calculation of output...." << endl;
	AND4->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *AND4 << endl;
	cout << "END OF AND4 TESTING..." << endl;
	cout << "======================================" << endl;

	/*> OR4 testing */
	cout << "======================================" << endl;
	cout << "START OF OR4 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	OR4->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *OR4 << endl;
	cout << "Calculation of output...." << endl;
	OR4->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *OR4 << endl;
	cout << "END OF OR4 TESTING..." << endl;
	cout << "======================================" << endl;

		/*> NAND4 testing */
	cout << "======================================" << endl;
	cout << "START OF NAND4 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	NAND4->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *NAND4 << endl;
	cout << "Calculation of output...." << endl;
	NAND4->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *NAND4 << endl;
	cout << "END OF NAND4 TESTING..." << endl;
	cout << "======================================" << endl;

		/*> NOR4 testing */
	cout << "======================================" << endl;
	cout << "START OF NOR4 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	NOR4->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *NOR4 << endl;
	cout << "Calculation of output...." << endl;
	NOR4->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *NOR4 << endl;
	cout << "END OF NOR4 TESTING..." << endl;
	cout << "======================================" << endl;

		/*> XOR4 testing */
	cout << "======================================" << endl;
	cout << "START OF XOR4 TESTING..." << endl;
	cout << "Connect to connection_test_gate" << endl;
	XOR4->connectGate(Connection);
	cout << "Initial structure : " << endl;
	cout << *XOR4 << endl;
	cout << "Calculation of output...." << endl;
	XOR4->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *XOR4 << endl;
	cout << "END OF XOR4 TESTING..." << endl;
	cout << "======================================" << endl;

			/*> Connection Gate checking */
	cout << "======================================" << endl;
	cout << "START OF CHECK TESTING..." << endl;
	cout << "Initial structure : " << endl;
	cout << *Connection << endl;
	cout << "Calculation of output...." << endl;
	Connection->CalculateOutput();
	cout << "Structure updated : " << endl;
	cout << *Connection << endl;
	cout << "END OF CHECK TESTING..." << endl;
	cout << "======================================" << endl;



	//How instanciate a object into a map ?
	//NOT ==> modifier la classe adéquatement

	//Check shared_ptr

	//Create vector
	//Pour le tri par étage faire un tableau par référencement

}