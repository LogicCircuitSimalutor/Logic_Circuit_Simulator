/*>
*	This file gathers these follower unit tests : 
*
*	- Create ANDx Gate with 2, 4, 8 inputs
* 	- Evaluate Gates multi-inputs with new method of calcul 
*			if 1 zero in inputs ==> return 0
*			else return 1
* 	- Print True table to validate algorithm
*/
#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include "main5.h"


using namespace std;

int main(int argc, char const *argv[]){
	string dot_path = argv[1];
	string vcd_path = argv[2];
	string speriod = argv[3]; //clock period expressed in ns
	int period = atoi(argv[3]);

	/*>Declaration of map stimuli */
	map<int, vector<bool> >mapStimuli;

	Circuit * circuit = NULL; //init of circuit

	/*>Parse DOT file in order to create circuit*/
	Parseur parseur(dot_path);
	parseur.Parser();

	/*>Parse VCD file to get stimuli to apply*/
	ParseurVCD parseurVCD(vcd_path);
	parseurVCD.connectCircuit(parseur.getCircuit());
	parseurVCD.Parser(mapStimuli);

	cout << parseur << endl;
	cout << parseurVCD << endl;

	circuit = parseur.getCircuit();

	/*>Is the circuit properly wired ?*/
	if(circuit->checkGlobalConnection()){
		//fill outpust vector in circuit to get logicstate
		if(circuit->fillOutputsVector()){
					//Sorting of circuit by level
			if(circuit->sortGate()){
				if(circuit->simulate(&mapStimuli)){
					cout << "Simulation finished with success" << endl;
				}else{
					cout << "Simulation failed..." << endl;
					exit(4);
				}
			}else{
				cout << "Combinatory loop error..." << endl;
				exit(3);
			}
		}else{
			cout << "Circuit must have at least one output..." << endl;
			exit(1);
		}
	}else{
		cout << "Connection error...." << endl;
		exit(2);
	}	
}