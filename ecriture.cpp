#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void generateVectorPredicat(vector<pair<string, vector<vector<string>>>> predicat, ofstream &file){
	//parcour de chaque paire (nom, liste(liste(string)))
	for(auto p : predicat){
		auto nom = p.first;
		file << "vector<tuple2> "+nom+";\n";
		//parcour de la liste de n-uplets {(Michel,Jean), (Pierre, Paul), ....}
		for(auto nuplet : p.second){
			file << "(";
			//parcour chaque string du nuplet (Jean)
			for(int i = 0; i < nuplet.size(); i++){
				file << nuplet.at(i) << ",";
			}
			file << ")\n";
		}
	}
}

int main(int argc, char **argv) {

		vector<pair<string, vector<vector<string>>>> genealogie;
		vector<string> michjean;
		michjean.push_back("Michel");
		michjean.push_back("Jean");
		vector<string> pierrepaul;
		pierrepaul.push_back("Pierre");
		pierrepaul.push_back("Paul");
		vector<vector<string>> couplesperes;
		couplesperes.push_back(michjean);
		couplesperes.push_back(pierrepaul);
		genealogie.push_back(make_pair("pere", couplesperes));

		vector<string> mariejean;
		mariejean.push_back("Marie");
		mariejean.push_back("Jean");
		vector<vector<string>> couplesmeres;
		couplesmeres.push_back(mariejean);
		genealogie.push_back(make_pair("mere", couplesmeres));

		string diese;
		diese = (char)35;
		cout << diese << '\n';
		ofstream myfile;
	  myfile.open ("example.cpp");
	  // myfile << diese+"include <unistd.h>\n"+
		// diese+"include <stdio.h>\n"+
		// diese+"include <stdlib.h>\n"+
		// diese+"include <iostream>\n";
		generateVectorPredicat(genealogie, myfile);
	  myfile.close();
	return 0;
}
