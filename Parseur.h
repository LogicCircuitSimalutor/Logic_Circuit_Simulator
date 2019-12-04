#include <iostream>
#include <string>

#include <fstream>

#include "Gate.h"
#include "InputGate.h"
#include "ANDx.h"
#include "ORx.h"
#include "NOTx.h"
#include "NANDx.h"
#include "NORx.h"
#include "XORx.h"
// #include "MUXx.h"
#include "Circuit.h"
#include <set>
#include <vector>

using namespace std;

class Parseur {
private:
bool CircuitCreated = 0;
string m_dot_path = "";
std::set<string> noms;
Circuit * m_circuit;
public:

  	Parseur(string dot_path);
    void Parser();
    void CreateCircuit();
    void CreateConnections();
    void CreateGates();
    string CleanLine(string line);
    bool UselessLine(string line);
    string getPath();
    void setPath(string dot_path);
    Circuit * getCircuit()
    {
      return m_circuit;
    }
    friend ostream& operator <<(ostream& out, const  Parseur &f);

};
