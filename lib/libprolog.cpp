#include "libprolog.h"

void libprolog::readPl(string filename){
  if(read(filename)){
    std::cout << "fichier lu" << '\n';
    _filename = filename;
  } else {
    std::cout << "erreur de Lecture" << '\n';
  }
  //_predicats et _rules a remplir
}

void libprolog::generateCPP(){
    Ecriture ecrire(_filename, listPredicat, listRegles);
}

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
  //TODO
  // for(vector<vector<pair<string, vector<string>>>>)
}

/*
checkpredicat()

coloriage(X1,X2,X3,X4):- voisins(X1,X2, X3), voisins(X1,X4), voisins(X2,X3), voisins(X2,X4), voisins(X3,X4).

listRegles.add(nom, list<string>, list<predicat(X,Y)>)



Predicat(voisins, <bleu,rouge>);
list<Predicat>

add(nom, list){
  listPredicat.add(new Predicat(nom, liste<rouge, bleu, vert>));
}
*/
