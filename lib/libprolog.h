#ifndef libprolog_h
#define libprolog_h

#include <cstdarg>
#include "../readFile.cpp"
#include "../ecriture.cpp"

struct Predicate{
  Predicate(string nom, vector<string> constantes):_nom(nom), _constantes(constantes){}
  string _nom;
  vector<string> _constantes;

  string get_nom(){return _nom;}
  void set_nom(string nom){_nom = nom;}

  string& operator[](size_t i){return _constantes[i];}

  vector<string> get_constantes(){return _constantes;}
  void set_constantes(vector<string> constantes){_constantes = constantes;}

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
  :_nom(nom), _var(var), _predicatsR(predicats){}
  string _nom;
  vector<string> _var;
  vector<Predicate> _predicatsR;

  string get_nom(){return _nom;}
  void set_nom(string nom){_nom = nom;}

  vector<string> get_var(){return _var;}
  void set_var(vector<string> var){_var = var;}

  vector<Predicate> get_predicatsR(){return _predicatsR;}
  void set_predicatsR(vector<Predicate> predicats){_predicatsR = predicats;}

  friend ostream& operator<<(ostream &out,const Rule &r) {
    out << r._nom << "(";
    for(int i=0; i<r._var.size(); ++i) {
      out << r._var[i] << (i==r._var.size()-1 ? "" : ",");
    }
    out << ") :- ";
    for(int i=0; i<r._predicatsR.size(); ++i){
      out << r._predicatsR[i] << (i==r._predicatsR.size()-1 ? "" : ",");
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
  /*utility*/
  void readPl(string filename);
  void generateCPP();
  void solvePl();
  void exportPl(string filename);

  /*predicates*/
  vector<Predicate> getPredicates();
  vector<Predicate> findPredicates(string nom);
  void setPredicats(vector<Predicate> predicats);
  void addPredicate(Predicate p);
  void addPredicate(string nom, int n, ...);
  Predicate createPredicate(string nom, int n, ...);

  /*rules*/
  vector<Rule> getRules();
  void setRules(vector<Rule> rules);
  void addRule(Rule r);
  void addRule(string nom, vector<Predicate> predicats, int n, ...);
  Rule createRule(string nom, vector<Predicate> predicats, int n, ...);

private:
  void doRecursion(int baseCondition, Rule r, vector<Predicate> t,
  multimap<pair<int,int>, pair<int, int>> &conditons);

  multimap<pair<int,int>, pair<int, int>> generateConditions(multimap<string, pair<int, int>> mapVariables);
  int count = 0;
  vector<Predicate> getPredicatesInRule(Rule r);
};

#endif
