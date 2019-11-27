#include "Parseur.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[]) {
  string dot_path = argv[1];
  Parseur parseur(dot_path);
  parseur.Parser();
  cout << parseur;
  return 0;
}
