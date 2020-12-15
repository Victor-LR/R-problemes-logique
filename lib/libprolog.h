#ifndef libprolog_h
#define libprolog_h

#include "../readFile.cpp"
#include "../ecriture.cpp"

class libprolog {
private:
  string _filename;
  vector<pair<string, vector<vector<string>>>> _listPredicat;
  vector<vector<pair<string, vector<string>>>> _listRegles;

public:

  void readPl(string filename);
  // vector<..> gettuples()

  void generateCPP();

};
#endif
