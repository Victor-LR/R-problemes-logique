#ifndef libprolog_h
#define libprolog_h

#include <cstdarg>
#include "../readFile.cpp"
#include "../ecriture.cpp"

struct Predicate{
  /*
    _nom : nom du prédicat (correspond à un fait)
    _constantes : liste contenant les constantes du prédicat
  */
  Predicate(string nom, vector<string> constantes):_nom(nom), _constantes(constantes){}
  string _nom;
  vector<string> _constantes;

  //Getteurs et Setteurs
  string get_nom(){return _nom;}
  void set_nom(string nom){_nom = nom;}

  vector<string> get_constantes(){return _constantes;}
  void set_constantes(vector<string> constantes){_constantes = constantes;}

  string& operator[](size_t i){return _constantes[i];}

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
  /*
    _nom : nom de la règle
    _var : liste contenant les variables de la règle
    _predicatsR : liste des prédicats formant la règle
  */
  Rule(string nom, vector<string> var, vector<Predicate> predicats)
  :_nom(nom), _var(var), _predicatsR(predicats){}
  string _nom;
  vector<string> _var;
  vector<Predicate> _predicatsR;

  //Getteurs et Setteurs

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
  //Nom du fichier prolog lu
  string _filename;
  //Liste des prédicats/faits
  vector<Predicate> _predicats;
  //Liste des règles
  vector<Rule> _rules;

public:
  /*utility*/
  //Permet de lire un fichier .pl et de remplir les listes prédicat et règle
  void readPl(string filename);
  //Génère un fichier .cpp qui résout spécifiquement le problème du fichier prolog
  //A CHANGER
  void generateCPP();
  //Lance la résolution du problème et affiche pour chaque règles les résultats
  //déduits en fonction des prédicats (faits)
  void solvePl();
  //Génère un fichier .pl à partir des listes _predicates et _rules
  void exportPl(string filename);

  /*predicates*/
  //Retourne la liste des prédicats _predicates
  vector<Predicate> getPredicates();
  //A partir d'un string donné en argument, récupère tous les prédicats du même nom
  vector<Predicate> findPredicates(string nom);
  //Setteur de la liste des prédicats
  void setPredicats(vector<Predicate> predicats);
  //Ajoute un prédicat à la liste _predicates
  void addPredicate(Predicate p);
  /*Ajoute un prédicat avec comme arguments :
    nom : son nom,
    n : le nombre de constantes du prédicats à ajouter,
    ... : une suite de n string séparées par des virgules correspondant
          aux constantes du predicats
  */
  void addPredicate(string nom, int n, ...);
  Predicate createPredicate(string nom, int n, ...);
  Predicate createPredicate(string nom, vector<string> constantes);

  /*rules*/
  //Retourne la liste des règles
  vector<Rule> getRules();
  //Setteur de la liste des prédicats
  void setRules(vector<Rule> rules);
  //Ajoute une règle à la liste
  void addRule(Rule r);
  /*Ajoute une règle avec comme arguments :
    nom : son nom,
     predicats : un vecteur contenant la liste des prédicats définissant la règle
    n : le nombre de variables de la règle,
    ... : une suite de n string séparées par des virgules correspondant aux variables
          de la règle
  */
  void addRule(string nom, vector<Predicate> predicats, int n, ...);
  Rule createRule(string nom, vector<Predicate> predicats, int n, ...);
  Rule createRule(string nom, vector<string> var, vector<Predicate> predicats);

private:
  void doRecursion(int baseCondition, Rule r, vector<Predicate> t,
  multimap<string, pair<int,int>> &mapVariables,
  multimap<pair<int,int>, pair<int, int>> &conditons);

  multimap<pair<int,int>, pair<int, int>> generateConditions
  (multimap<string, pair<int, int>> mapVariables);
};

#endif
