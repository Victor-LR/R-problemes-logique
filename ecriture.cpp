#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Ecriture {

public:

		Ecriture(vector<pair<string, vector<vector<string>>>> listPredicat, vector<vector<pair<string, vector<string>>>> listRegles){

		// // TEST
		// vector<pair<string, vector<vector<string>>>> genealogie;
		// vector<string> michjean;
		// michjean.push_back("Michel");
		// michjean.push_back("Jean");
		// vector<string> pierrepaul;
		// pierrepaul.push_back("Pierre");
		// pierrepaul.push_back("Paul");

		// vector<vector<string>> couplesperes;
		// couplesperes.push_back(michjean);
		// couplesperes.push_back(pierrepaul);
		// genealogie.push_back(make_pair("pere", couplesperes));

		// vector<string> mariejean;
		// mariejean.push_back("Marie");
		// mariejean.push_back("Jean");
		// vector<vector<string>> couplesmeres;
		// couplesmeres.push_back(mariejean);
		// genealogie.push_back(make_pair("mere", couplesmeres));

		// vector<string> variablesRegle = {"X","Z"};
		// vector<string> variablesPred1 = {"X","Y"};
		// vector<string> variablesPred2 = {"Y","Z"};

		// vector < pair<string, vector<string>> > listPred;
		// listPred.push_back(make_pair("grand_pere",variablesRegle));
		// listPred.push_back(make_pair("pere",variablesPred1));
		// listPred.push_back(make_pair("pere",variablesPred2));

		// vector< vector < pair<string, vector<string>> >> regles;
		// regles.push_back(listPred);
		// //FIN TEST

		ofstream myfile;
		myfile.open ("example.cpp");

		generateInclude(myfile);
		generatePrint(myfile);
		generateClassObject(myfile);
		generateClassVariable(myfile);
		generateClassValue(myfile);
		generateClassTuple(listRegles,listPredicat,myfile);
		generateVectorPredicat(listPredicat, myfile);
		generateVectorRegle(listRegles, myfile);
		generate_deduce(listRegles, myfile);
		generateSolution(listRegles,listPredicat,myfile);
		generateMain(myfile);
		cout<<"Le fichier a été généré"<<endl;
		myfile.close();
	}

	void generateInclude(ofstream &file){
		string diese;
		diese = (char)35;
		file << diese+"include <unistd.h>\n"+
				diese+"include <stdio.h>\n"+
				diese+"include <stdlib.h>\n"+
				diese+"include <iostream>\n"+
				diese+"include <list>\n"+
				"using namespace std;\n\n";
	}

	void generatePrint(ofstream &file){
		file << "template<class Container>\n";
		file << "void print(Container &c) {\n";
		file << "\tfor(auto e : c) {\n";
		file << "\t\tcout << \"\\t\" << e << endl;\n";
		file << "\t}\n";
		file << "\tcout << endl;\n";
		file << "}\n\n";
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

	//declaration des listes de tuples
	void generateVectorPredicat(vector<pair<string, vector<vector<string>>>> predicats, ofstream &file){
		//parcour de chaque paire (nom, liste(liste(string)))
		for(auto p : predicats){
			auto nom = p.first;
			auto tuple_size = p.second.at(0).size();
			file << "list<Tuple" << tuple_size << "> " + nom + ";\n";
			//parcour de la liste de n-uplets {(Michel,Jean), (Pierre, Paul), ....}
			/* for(auto nuplet : p.second){
				file << nom + ".push_back(Tuple" << tuple_size << "(";
				//parcour chaque string du nuplet (Jean)
				for(int i = 0; i < nuplet.size(); i++){
					file << "new Value(\""+nuplet.at(i)+"\")" << (i==nuplet.size()-1 ? "" : ",");
				}
				file << "));\n";
			}*/
		}
		file << "\n";
	}

	void generateVectorRegle(vector<vector<pair<string, vector<string>>>> regles, ofstream &file){
		for(auto r : regles){
			auto nom = r.at(0).first;
			auto tuple_size = r.at(0).second.size();
			file << "list<Tuple" << tuple_size << "> " + nom + ";\n";
		}
		file << "\n";
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


	void generateClassTuple(vector<vector <pair<string, vector<string>>>> regles, vector<pair<string, vector<vector<string>>>> predicat, ofstream & file){

		vector <int> typesTuples;

		for (auto r : regles){
			auto it = find (typesTuples.begin(), typesTuples.end(), r.at(0).second.size());
			if (it == typesTuples.end())
					typesTuples.push_back(r.at(0).second.size());
		}

		for (auto p : predicat){
			for(auto nuplet : p.second){
				auto it = find (typesTuples.begin(), typesTuples.end(), nuplet.size());
				if (it == typesTuples.end())
					typesTuples.push_back(nuplet.size());
			}
		}


		for (int nbt : typesTuples){


			//le nombre d'arguments de la 1er règle
			int nombreArg = nbt;
			string charVariable;

			file << "class Tuple" << nombreArg << " {\n" ;
			file << "public:\n";
			file << "\tObject *object["<<nombreArg<<"];\n\n";
			file <<"\tTuple" << nombreArg << "(";

			//Le nombre de paramètre du constructeur
			for (int i = 0 ; i < nombreArg ; i++){
				charVariable = (char)97+i;
				if (i == nombreArg-1)
					file << "Object *"<<charVariable<<") {\n";
				else
					file << "Object *"<<charVariable<<", ";

			}

			//intitialiser les paramètres
			for (int i = 0 ; i < nombreArg ; i++){
				charVariable = (char)97+i;
				file << "\t\t object[" << i << "] = " + charVariable + ";\n";
			}
			file << "\t}\n\n";

			for (int i = 0 ; i < nombreArg ; i++){
				file << "\tObject& x" << i+1 << "() {\n";
				file << "\t\treturn *object[" << i << "];\n\t}\n";

			}

			file << "\tObject *operator[](int n) {\n"
				<< " \t\treturn object[n];\n\t}\n";

			//Operator <<
			file << "\tfriend ostream& operator <<(ostream &out, Tuple" << nombreArg << " &obj) {\n"
			<< " \t\tout << \"(\" << ";
			for(int i = 0; i < nombreArg - 1 ; i++){
				file << "obj[" << i << "] -> value << \",\" <<";
			}
			file << "obj[" << nombreArg - 1 << "] -> value << ";
			file << "\")\";";
			file <<"\n\t\treturn out;";
			file << "}\n";


			file << "\n};\n\n";

		}

	}

	//remplissage des listes de tuples crees par generateVectorPredicat
	void generateSolution(vector<vector <pair<string, vector<string>>>> regles, vector<pair<string, vector<vector<string>>>> predicats, ofstream & file){
		file << "void solution(){\n";
		for(auto p : predicats){
			auto nom = p.first;
			auto tuple_size = p.second.at(0).size();
			//parcour de la liste de n-uplets {(Michel,Jean), (Pierre, Paul), ....}
			for(auto nuplet : p.second){
				file << "\t" << nom + ".push_back(Tuple" << tuple_size << "(";
				//parcour chaque string du nuplet (Jean)
				for(int i = 0; i < nuplet.size(); i++){
					file << "new Value(\""+nuplet.at(i)+"\")" << (i==nuplet.size()-1 ? "" : ",");
				}
				file << "));\n";
			}
		}
		//Affichage
		file << "\tcout << \"Listes des prédicats : \"<< endl;\n";
		for(auto p : predicats){
			auto nom = p.first;
			file << "\tcout <<\""<< nom <<" =\\n\"; print("<< nom <<");cout << endl;\n";
		}
		file << "\n\tcout << \"Solutions pour toutes les règles :\"<< endl;\n";
		for(auto r1 : regles){
			auto nom = r1.at(0).first;
			file << "\t"<< nom <<"_deduce();\n";
			file << "\tcout <<\""<< nom << " =\\n\";print("<< nom <<");cout << endl;\n";
		}
		file << "}\n\n";
	}

	void generateMain(ofstream &file){
		file << "int main(int argc, char **argv){\n";
		file << "\tsolution();\n";
		file << "};\n\n";
	}


	void generate_deduce(vector< vector < pair<string, vector<string>> >> regles,  ofstream & file){


	for(auto regle : regles){
		multimap<string, pair<string, int>> mapVariables;

		string nomRegle = regle.at(0).first;
		auto variablesRegle = regle.at(0).second;
		auto nbpredicat = regle.size();
		auto tuple_size = regle.at(0).second.size();;
		file << "void " + nomRegle + "_deduce(){\n";
		string tab = "\t";
		for(int t = 1; t<regle.size(); t++){
			auto predicat = regle.at(t);
			string nomPredicat = predicat.first;
			file << tab <<"for(auto t" << t << " : " << nomPredicat << "){\n";
			tab += "\t";
			int i = 0;
			for(auto variable : predicat.second){ //pour chaque variable du predicat {X, Y, ...}
					string tString = "t"+to_string(t);
					mapVariables.insert(make_pair(variable, make_pair(tString, i)));
				i++;
			}
		}
		tab += "\t";
		for(auto v1 : mapVariables){
			for(auto v2 : mapVariables){
				if((v1.first == v2.first) && (v1.second.first != v2.second.first)){
					int v1nombre = stoi((v1.second.first).substr(1,1));
					int v2nombre = stoi((v2.second.first).substr(1,1));
					//Suppression des doublons dans les conditions
					if (v1nombre < v2nombre){
						file << tab;
						file << "if(" << v1.second.first << ".x" << v1.second.second + 1 << "()";
						file << " != " << v2.second.first << ".x" << v2.second.second +1 << "()";
						file << ") continue;\n";
					}
				}
			}
		}
		file << tab << "\t" + nomRegle + ".push_back(Tuple" << tuple_size << "(";

		for(int i = 0; i<variablesRegle.size(); i++){
			auto it = mapVariables.find(variablesRegle.at(i));
			if(it != mapVariables.end()){
				file << it->second.first << "[" << it->second.second << "]" << (i==variablesRegle.size() - 1 ? "" : ",");
			}
		}
		file << "));\n";
		for(int i = 0; i<nbpredicat; i++){
			string tab = "";
			for (int t = i+1; t<nbpredicat; t++)
				tab += "\t";
			file << tab <<"}\n";
		}
		//afichage map
		// for(auto it = mapVariables.begin(); it != mapVariables.end(); it++){
		// 	string t =it->second.first;
		// 	std::cout << it->first << "->" << t << "[" << it->second.second << "]" <<  '\n';
		// 	}
	}


}



};
