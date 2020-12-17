#include "libprolog.h"

vector<Predicate> libprolog::getPredicates(){
  return _predicats;
}

vector<Rule> libprolog::getRules(){
  return _rules;
}

void libprolog::setPredicats(vector<Predicate> predicats){
  _predicats = predicats;
}

void libprolog::setRules(vector<Rule> rules){
  _rules = rules;
}

void libprolog::readPl(string filename){
  if(read(filename)){
    std::cout << "fichier lu" << '\n';
    _filename = filename;

    //remplir liste des _predicats
    for(pair<string, vector<vector<string>>> pair : listPredicat){
      string nomPred = pair.first;
      for(vector<string> v : pair.second ){
        vector<string> listeConstantes;
        for(int i = 0; i<v.size(); i++){
          listeConstantes.push_back(v[i]);
        }
        _predicats.push_back(Predicate(nomPred, listeConstantes));
      }
    }
    //remplir liste des _rules
    for(vector<pair<string, vector<string>>> v : listRegles){
      string nomRegle = v[0].first;
      vector<string> variables = v[0].second;
      vector<Predicate> predicats;
      for(int i=1; i<v.size(); ++i){
        string nomPred = v[i].first;
        vector<string> varPred = v[i].second;
        predicats.push_back(Predicate(nomPred,varPred));
      }
      _rules.push_back(Rule(nomRegle, variables, predicats));
    }
  } else {
    std::cout << "erreur de Lecture" << '\n';
  }
}

void libprolog::addPredicate(Predicate p){
  _predicats.push_back(p);
}

/*filename : nom du fichier avec extension .pl*/
void libprolog::exportPl(string filename){
  ofstream myfile;
  myfile.open(filename);
  //ecriture des preficats au format pl
  for(Predicate p : _predicats){
    myfile << p._nom << "(";
    for(int i=0; i<p._constantes.size(); ++i){
      myfile << p._constantes[i] << (i==p._constantes.size() -1 ? "" : ",");
    }
    myfile << ")." << endl;
  }
  //ecriture des regles au format pl
  for(Rule r : _rules){
    myfile << r._nom << "(";
    for(int i=0; i<r._var.size(); ++i){
      myfile << r._var[i] << (i==r._var.size() -1 ? "" : ",");
    }
    myfile << "):-";
    for(int j=0; j<r._predicatsR.size(); ++j){
      myfile << r._predicatsR[j]._nom << "(";
      for(int k=0; k<r._predicatsR[j]._constantes.size(); ++k){
        myfile << r._predicatsR[j]._constantes[k]
        << (k==r._predicatsR[j]._constantes.size() -1 ? "" : ",");
      }
      myfile << ")" << (j==r._predicatsR.size() -1 ? "." : ",");
    }
    myfile << endl;
  }
  myfile.close();
}
/*
nom : string le nomPred
n : nombre de constantes
... : une liste de string, les constantes du predicat
*/
void libprolog::addPredicate(string nom, int n, ...){
  vector<string> v_constantes;
  va_list constantes;
  va_start(constantes, n); //la liste des constantes commence apres n
  for(int i=0; i<n; ++i){
    string c = va_arg(constantes, const char *);
    v_constantes.push_back(c);
  }
  va_end(constantes);
  _predicats.push_back(Predicate(nom, v_constantes));
}

void libprolog::addRule(Rule r){
  _rules.push_back(r);
}

/*
nom : string le nomRule
predicats : vector de predicats, corps de la regle
n : nombre de var de la tete de regle
... : une liste de string, les var de la tete de regle
*/
void libprolog::addRule(string nom, vector<Predicate> predicats, int n, ...){
  vector<string> v_var;
  va_list vars;
  va_start(vars, n);
  for(int i=0; i<n; ++i){
    string v = va_arg(vars, const char *);
    v_var.push_back(v);
  }
  va_end(vars);
  _rules.push_back(Rule(nom, v_var, predicats));
}

Predicate libprolog::createPredicate(string nom, int n, ...){
  vector<string> v_constantes;
  va_list constantes;
  va_start(constantes, n); //la liste des constantes commence apres n
  for(int i=0; i<n; ++i){
    string c = va_arg(constantes, const char *);
    v_constantes.push_back(c);
  }
  va_end(constantes);
  return Predicate(nom, v_constantes);
}

Rule libprolog::createRule(string nom, vector<Predicate> predicats, int n, ...){
  vector<string> v_var;
  va_list vars;
  va_start(vars, n);
  for(int i=0; i<n; ++i){
    string v = va_arg(vars, const char *);
    v_var.push_back(v);
  }
  va_end(vars);
  return Rule(nom, v_var, predicats);
}

void libprolog::generateCPP(){
  Ecriture ecrire(_filename, listPredicat, listRegles);
}

vector<Predicate> libprolog::findPredicates(string nom){
  vector<Predicate> v;
  for(Predicate p : getPredicates()){
    if(p.get_nom() == nom ){
      v.push_back(p);
    }
  }
  return v;
}

vector<Predicate> libprolog::getPredicatesInRule(Rule r){
  vector<Predicate> v;
  vector<Predicate> vr = r.get_predicatsR();
  for(Predicate p : vr){
    vector<Predicate> x = findPredicates(p.get_nom());
    v.insert(v.end(), x.begin(), x.end());
  }
  return v;
}


// recur(){
//   ifconditions
//     if(sf = gd)
//   recur
// }

void libprolog::doRecursion(int baseCondition, Rule r, vector<Predicate> t){
 vector<Predicate> preds = r.get_predicatsR();
 if(baseCondition==0){
   for( Predicate p : t){
     std::cout << p << ", ";
     // recur(sf,gd)
     // // multimap m;
     // // for()
     // p[0] p[1]
   }
   std::cout<<"taille " << t.size() << endl;
   count++;
 } else {
   preds.erase(preds.begin());
   baseCondition--;
   for(Predicate p : getPredicatesInRule(r)){
     t.push_back(p);
     doRecursion(baseCondition, r, t);
     t.pop_back();
   }
 }
}

void libprolog::solvePl(){
  for(Rule r : _rules){
    vector<Predicate> t;
    int taillecorpsregle = r.get_predicatsR().size();
    doRecursion(taillecorpsregle, r, t);
  }
  std::cout << "it : " << count << '\n';
}
