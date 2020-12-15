#ifndef libprolog_h
#define libprolog_h

#include "../readFile.cpp"
#include "../ecriture.cpp"

struct Predicate{
  Predicate(string nom, vector<string> constantes):_nom(nom), _constantes(constantes){}
  string _nom;
  vector<string> _constantes;

  friend ostream& operator<<(ostream &out,const Predicate &p) {
    out << p._nom << "(";
    for(int i=0; i<p._constantes.size(); ++i) {
      out << p._constantes[i] << (i==p._constantes.size()-1 ? "" : ",");
    }
    out << ")";
    return out;
  }
};

struct Rule{
  Rule(string nom, vector<string> var, vector<Predicate> predicats)
  :_nom(nom), _var(var), _predicats(predicats){}
  string _nom;
  vector<string> _var;
  vector<Predicate> _predicats;

  friend ostream& operator<<(ostream &out,const Rule &r) {
    out << r._nom << "(";
    for(int i=0; i<r._var.size(); ++i) {
      out << r._var[i] << (i==r._var.size()-1 ? "" : ",");
    }
    out << ") :- ";
    for(int i=0; i<r._predicats.size(); ++i){
      out << r._predicats[i] << (i==r._predicats.size()-1 ? "" : ",");
    }
    return out;
  }
};

class libprolog {
private:
  string _filename;
  vector<Predicate> _predicats;
  vector<Rule> _rules;

public:
  void readPl(string filename);
  void generateCPP();
  vector<Predicate> getPredicates();
  vector<Rule> getRules();
  //addPredicate
  //addRule
  //solve


  // void printPredicates();
  // void printRules();
};

#endif
