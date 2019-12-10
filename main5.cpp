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
#include <fstream>
#include <vector>
#include "main5.h"

#define NBL 1000
#define NBC 1000
#define X 10
#define Y 20
using namespace std;

int main(int argc, char const *argv[]){
	string dot_path = argv[1];
	string vcd_path = argv[2];
	string result_file = argv[3];
	string speriod = argv[4]; //clock period expressed in ns
	int period = atoi(argv[4]);

	/*>Declaration of map stimuli */
	map<int, vector<bool> >mapStimuli;

	Circuit * circuit = NULL; //init of circuit
	Chronogramme chrono(NBL, NBC, 255);

	const string output_file("result.txt");
	ofstream myFlux(output_file.c_str());

	/*>Parse DOT file in order to create circuit*/
	Parseur parseur(dot_path);
	parseur.Parser();

	cout << parseur << endl;
	cout << circuit << endl;

	/*>Parse VCD file to get stimuli to apply*/
	ParseurVCD parseurVCD(vcd_path);
	parseurVCD.connectCircuit(parseur.getCircuit());
	parseurVCD.Parser(mapStimuli);

	//chrono.TraceClock(int(mapStimuli.size()), X+40, Y);

	//cout << parseurVCD << endl;

	circuit = parseur.getCircuit();

	/*>Is the circuit properly wired ?*/
	if(circuit->checkGlobalConnection()){
		//fill outpust vector in circuit to get logicstate
		if(circuit->fillOutputsVector(chrono.getSignalVector(), X, Y)){
			chrono.TraceNewSignalLine(X, Y);
					//Sorting of circuit by level
			if(circuit->sortGate()){
				if(circuit->simulate(&mapStimuli, chrono, period, myFlux)){
					cout << "Simulation finished with success" << endl;
					cout << chrono << endl;
					chrono.sauver("chronogramme.bmp");
					system("eog chronogramme.bmp&");
					system("gedit result.txt&");
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
