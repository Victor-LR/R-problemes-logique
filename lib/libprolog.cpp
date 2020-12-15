#include "libprolog.h"

void libprolog::readPl(string filename){
  if(read(filename)){
    std::cout << "fichier lu" << '\n';
    _filename = filename;
    _listPredicat = getlistPredicat();
    _listRegles = getlistRegles();
  } else {
    std::cout << "erreur de Lecture" << '\n';
  }
}


void libprolog::generateCPP(){
    Ecriture ecrire(_filename, _listPredicat, _listRegles);
}

void libprolog::printPredicates(){
  for(pair<string, vector<vector<string>>> pair :listPredicat){
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
