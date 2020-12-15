#include "libprolog.h"

// ostream& operator<<(ostream &out,const Predicate &p) {
//   out << p._nom << "(";
//   for(int i=0; i<p._constantes.size(); ++i) {
//     out << p._constantes[i] << (i==p._constantes.size()-1 ? "" : ",");
//   }
//   out << ")" << endl;
//   return out;
// }

vector<Predicate> libprolog::getPredicates(){
  return _predicats;
}

vector<Rule> libprolog::getRules(){
  return _rules;
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

void libprolog::generateCPP(){
  Ecriture ecrire(_filename, listPredicat, listRegles);
}

/*
void libprolog::printPredicates(){ //affiche la liste des predicats
for(pair<string, vector<vector<string>>> pair : listPredicat){
std::cout << pair.first << " = " << '\n'; //nom du predicat
for(vector<string> v : pair.second ){
std::cout << "(";
for(int i = 0; i<v.size(); i++){
std::cout << v[i] << (i==v.size()-1 ? "" : ",");
}
std::cout << ")";
std::cout << '\n';
}
}
}

void libprolog::printRules(){
// for(vector<vector<pair<string, vector<string>>>>)
}

*/
