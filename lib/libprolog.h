#ifndef libprolog_h
#define libprolog_h

#include "../readFile.cpp"
#include "../ecriture.cpp"

struct Predicate{
  string nom;
  list<string> cosntantes;
};

struct Rule{
  string nom;
  list<string> var;
  list<Predicate> predicats;
};

class libprolog {
private:
  string _filename;
  list<Predicate> _predicats;
  list<Rule> _rules;

public:
  void readPl(string filename);
  void printPredicates();
  void printRules();
  void generateCPP();

};
#endif
