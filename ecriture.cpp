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

void generateClassTuple(vector<vector <pair<string, vector<string>>>> regles, ofstream & file){
	//le nombre d'arguments de la 1er règle 
	auto nombreArg = regles.at(0).at(0).second.size();
	file << "class Tuple" << nombreArg << " {\n" ;
	file << "public:\n";
	file << "\tObject *object["<<nombreArg<<"];\n\n";
	file <<"\tTuple" << nombreArg << "(";
	for (int i = 0 ; i < nombreArg ; i++){
		string charVariable;
		charVariable = (char)97+i;
		file << "Object *"<<charVariable<<",";
	} 
	file << "\n};\n";
}



int main(int argc, char **argv) {
	vector<string> variablesRegle = {"X","Y","Z"};
	vector<string> variablesPred1 = {"X","Y"};
	vector<string> variablesPred2 = {"Y","Z"};

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
	vector < pair<string, vector<string>> > listPred;
	listPred.push_back(make_pair("grand_pere",variablesRegle));
	listPred.push_back(make_pair("pere",variablesPred1));
	listPred.push_back(make_pair("pere",variablesPred2));

	vector< vector < pair<string, vector<string>> >> regles;

	regles.push_back(listPred);
		diese = (char)35;
		
		cout << diese << '\n';
		ofstream myfile;
	myfile.open ("example.cpp");
	myfile << diese+"include <unistd.h>\n"+
		diese+"include <stdio.h>\n"+
		diese+"include <stdlib.h>\n"+
		diese+"include <iostream>\n"+"\n";

	generateClassTuple(regles,myfile);
	generateVectorPredicat(genealogie, myfile);
	
	myfile.close();
	return 0;
}
