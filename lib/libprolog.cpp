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