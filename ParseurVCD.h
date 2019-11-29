#include <iostream>
#include <string>

#include <fstream>
#include "build/VCDFileParser.hpp"

#include "Gate.h"
#include "InputGate.h"
#include "ANDx.h"
#include "ORx.h"
#include "NOTx.h"
#include "NANDx.h"
#include "NORx.h"
#include "XORx.h"
#include "Circuit.h"
#include <set>
#include <vector>
#include <map>

using namespace std;

class ParseurVCD {
private:
string m_vcd_path = "";
VCDFileParser m_parser;
VCDFile * m_trace;
Circuit * m_circuit = NULL;
map<VCDTime, vector<VCDBit> > mapStimulis;
vector<VCDBit> vectorStimulis;

public:

  	ParseurVCD(string vcd_path);
    void Parser();
    string getPath();
    void connectCircuit(Circuit * circuit);
    void setPath(string vcd_path);
    friend ostream& operator <<(ostream& out, const  ParseurVCD &f);

    vector<VCDBit> * getStimulisVector()
    {
      return & vectorStimulis;
    }
    map<VCDTime, vector<VCDBit> > * getStimulisMap()
    {
      return & mapStimulis;
    }

};
