#include "libprolog.h"

void libprolog::readPl(string filename){
  if(read(filename)){
    std::cout << "fichier lu" << '\n';
  } else {
    std::cout << "erreur de Lecture" << '\n';
  }
}
