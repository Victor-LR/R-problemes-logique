#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void generateInclude(ofstream &file){
	string diese;
	diese = (char)35;
	file << diese+"include <unistd.h>\n"+
			diese+"include <stdio.h>\n"+
			diese+"include <stdlib.h>\n"+
			diese+"include <iostream>\n"+
			"using namespace std;\n\n";
}

void generateClassObject(ofstream &file){
	file << "class Object {\n";
	file << "public:\n";
	
	file << "\tstring value;\n\n";
	
	file << "\tObject() {\n";
	file << "\t}\n\n";
	
	file << "\tObject(string v): value(v) {\n";
	file << "\t}\n\n";
	
	file << "\tvirtual ~Object() {\n";
	file << "\t}\n\n";

	file << "\tvirtual int compare(const Object & obj) = 0;\n\n";
	
	file << "\tfriend bool operator==(const Object& obj1, const Object& obj2) {\n";
	file << "\t\treturn const_cast<Object &>(obj1).compare(obj2) == 0;\n";	
	file << "\t}\n\n";
	
	file << "\tfriend bool operator!=(const Object& obj1, const Object& obj2) {\n";
	file << "\t\treturn const_cast<Object &>(obj1).compare(obj2) != 0;\n";	
	file << "\t}\n\n";
	
	file << "};\n\n";
}

void generateClassVariable(ofstream &file){
	file << "class Variable : public Object {\n";
	file << "public:\n";
	
	file << "\tVariable(string name) : Object(name){ }\n\n";
	
	file << "\tint compare(const Object & obj) {\n";
	file << "\t\treturn 0;\n";
	file << "\t}\n\n";

	file << "};\n\n";
}

void generateClassValue(ofstream &file){
	file << "class Value : public Object {\n";
	file << "public:\n";
	
	file << "\tValue(string identifier) : Object(identifier){}\n\n";
	
	file << "\tint compare(const Object & obj) {\n";
	file << "\t\tValue * val = dynamic_cast<Value *>(&const_cast<Object &>(obj));\n";
	file << "\t\tif(val == nullptr) {\n";
	file << "\t\t\treturn 0;\n";
	file << "\t\t} else {\n";
	file << "\t\t\tif (value == val->value) return 0;\n";
	file << "\t\t\treturn 1;\n";
	file << "\t\t}\n";
	file << "\t\treturn 0;\n";
	file << "\t}\n\n";

	file << "};\n\n";
}

void generateVectorPredicat(vector<pair<string, vector<vector<string>>>> predicats, ofstream &file){
	//parcour de chaque paire (nom, liste(liste(string)))
	for(auto p : predicats){
		auto nom = p.first;
		auto tuple_size = p.second.at(0).size();
		file << "list<Tuple" << tuple_size << "> " + nom + ";\n";
		//parcour de la liste de n-uplets {(Michel,Jean), (Pierre, Paul), ....}
		for(auto nuplet : p.second){
			file << nom + ".push_back(Tuple" << tuple_size << "(";
			//parcour chaque string du nuplet (Jean)
			for(int i = 0; i < nuplet.size(); i++){
				file << "new Value("+nuplet.at(i)+")" << (i==nuplet.size()-1 ? "" : ",");
			}
			file << "));\n";
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

void generate_deduce(vector< vector < pair<string, vector<string>> >> regles,  ofstream & file){
	for(auto regle : regles){
		string nomRegle = regle.at(0).first;
		auto variablesRegle = regle.at(0).second;
		auto nbpredicat = regle.size();
		auto tuple_size = regle.at(0).second.size();;
		file << "void " + nomRegle + "_deduce(){\n";
		for(int i = 1; i<nbpredicat; i++){
			file << "\tfor(auto t" << i << " : " << nomRegle << "){\n\t";
		}
		file << "\tif(condition){\n";
		file << "\t" + nomRegle + ".push_back(Tuple" << tuple_size << "(";
		//A MODIFIER faire la correspondance t1[0] : X1
		file << "tA[X], tB[Y]));\n";
		file << "}";
		for(int i = 0; i<nbpredicat; i++){
			file << "}";
		}
	}
}

// 			string predicat = regle.at(i).first;
// 			file << predicat << "(";
// 			for(auto variable : regle.at(i).second){
// 				file << variable << ",";
// 			}
// 			file << "),";
//
// 		}
// 	}
// }



int main(int argc, char **argv) {
	vector<string> variablesRegle = {"X","Z"};
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

		
	vector < pair<string, vector<string>> > listPred;
	listPred.push_back(make_pair("grand_pere",variablesRegle));
	listPred.push_back(make_pair("pere",variablesPred1));
	listPred.push_back(make_pair("pere",variablesPred2));

	vector< vector < pair<string, vector<string>> >> regles;
	regles.push_back(listPred);

	regles.push_back(listPred);
		
		ofstream myfile;
	myfile.open ("example.cpp");

	generateInclude(myfile);
	generateClassObject(myfile);
	generateClassVariable(myfile);
	generateClassValue(myfile);
	generateClassTuple(regles,myfile);
	generateVectorPredicat(genealogie, myfile);
	generate_deduce(regles, myfile);

	myfile.close();
	return 0;
}
