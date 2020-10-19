#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void generateVectorPredicat(std::vector<std::string, std::vector<std::vector<std::string>>> predicat, std::ofstream file){
	for(int i = 0; i<predicat.size(); i++){
		auto nom = predicat.at(i).at(0);
		file << "vector<tuple2> "+nom+';';
		for(auto tuples : predicat.at(i).at(1)){
			// file << nom+".pushback("+std::.get<0>(predicat.get(i).get(1))+","+std::.get<1>(predicat.get(i).get(1))+")";
			for(auto constante : tuples){
				file << nom + " pushback "+constante;
			}
		}
	}
}

int main(int argc, char **argv) {

		std::string diese;
		diese = (char)35;
		std::cout << diese << '\n';
		std::ofstream myfile;
	  myfile.open ("example.cpp");
	  myfile << diese+"include <unistd.h>\n"+
		diese+"include <stdio.h>\n"+
		diese+"include <stdlib.h>\n"+
		diese+"include <iostream>\n";"
	  myfile.close();
	return 0;
}
