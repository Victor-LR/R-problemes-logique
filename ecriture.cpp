#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>

using namespace std;

class Ecriture {

public:

		Ecriture(string filename, vector<pair<string, vector<vector<string>>>> listPredicat, vector<vector<pair<string, vector<string>>>> listRegles){

		ofstream myfile;
		filename = filename.substr(0, filename.length()-2);
		auto found = filename.find_last_of("/\\");
 		if (found!=string::npos){
			filename = filename.substr(found+1);
		}
		myfile.open (filename+"cpp");

		generateInclude(myfile);
		generatePrint(myfile);
		generateClassObject(myfile);
		generateClassTuple(listRegles,listPredicat,myfile);
		generateVectorPredicat(listPredicat, myfile);
		generateVectorRegle(listRegles, myfile);
		generate_deduce(listRegles, myfile);
		generateDeduction(listRegles,listPredicat,myfile);
		generateMain(myfile);
		cout<<"Le fichier a été généré"<<endl;
		myfile.close();
	}

	static void generateInclude(ofstream &file){
		string diese;
		diese = (char)35;
		file << diese+"include <unistd.h>\n"+
				diese+"include <stdio.h>\n"+
				diese+"include <stdlib.h>\n"+
				diese+"include <iostream>\n"+
				diese+"include <list>\n"+
				"using namespace std;\n\n";
	}

	static void generatePrint(ofstream &file){
		file << "template<class Tuple>\n";
		file << "ostream& operator <<(ostream &out,list<Tuple> &c) {\n";
		file << "\tfor(auto e : c) {\n";
		file << "\t\tout << \"\\t\" << e << endl;\n";
		file << "\t}\n";
		file << "\tout << endl;\n";
		file << "\treturn out;\n";
		file << "}\n\n";
	}

	static void generateClassObject(ofstream &file){
		file << "class Object {\n";
		file << "public:\n";

		file << "\tstring value;\n\n";

		file << "\tObject() {\n";
		file << "\t}\n\n";

		file << "\tObject(string v): value(v) {\n";
		file << "\t}\n\n";

		file << "\tvirtual ~Object() {\n";
		file << "\t}\n\n";

		file << "\tint compare(const Object & obj) {\n";
		file << "\t\tObject * o = dynamic_cast<Object *>(&const_cast<Object &>(obj));\n";
		file << "\t\tif(o == nullptr) {\n";
		file << "\t\t\treturn 0;\n";
		file << "\t\t} else {\n";
		file << "\t\t\tif (value == o->value) return 0;\n";
		file << "\t\t\treturn 1;\n";
		file << "\t\t}\n";
		file << "\t\treturn 0;\n";
		file << "\t}\n\n";

		file << "\tfriend bool operator==(const Object& obj1, const Object& obj2) {\n";
		file << "\t\treturn const_cast<Object &>(obj1).compare(obj2) == 0;\n";
		file << "\t}\n\n";

		file << "\tfriend bool operator!=(const Object& obj1, const Object& obj2) {\n";
		file << "\t\treturn const_cast<Object &>(obj1).compare(obj2) != 0;\n";
		file << "\t}\n\n";

		file << "};\n\n";
	}

	//declaration des listes de tuples
	static void generateVectorPredicat(vector<pair<string, vector<vector<string>>>> predicats, ofstream &file){
		//parcour de chaque paire (nom, liste(liste(string)))
		for(auto p : predicats){
			auto nom = p.first;
			auto tuple_size = p.second.at(0).size();
			file << "list<Tuple" << tuple_size << "> " + nom + ";\n";
		}
		file << "\n";
	}

	static void generateVectorRegle(vector<vector<pair<string, vector<string>>>> regles, ofstream &file){
		std::list<std::string> nomPredicatListe;
		for(auto r : regles){
			auto nom = r.at(0).first;
			auto tuple_size = r.at(0).second.size();
			auto it = std::find(nomPredicatListe.begin(),nomPredicatListe.end(),nom);
			if(it != nomPredicatListe.end()){
				std::cout << "contains " << nom << std::endl;
			}else{
				file << "list<Tuple" << tuple_size << "> " + nom + ";\n";
				nomPredicatListe.push_back(nom);
			}

		}
		file << "\n";
	}

	static void generateClassTuple(vector<vector <pair<string, vector<string>>>> regles, vector<pair<string, vector<vector<string>>>> predicat, ofstream & file){

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
	static void generateDeduction(vector<vector <pair<string, vector<string>>>> regles, vector<pair<string, vector<vector<string>>>> predicats, ofstream & file){
		file << "void deduction(){\n";
		for(auto p : predicats){
			auto nom = p.first;
			auto tuple_size = p.second.at(0).size();
			//parcour de la liste de n-uplets {(Michel,Jean), (Pierre, Paul), ....}
			for(auto nuplet : p.second){
				file << "\t" << nom + ".push_back(Tuple" << tuple_size << "(";
				//parcour chaque string du nuplet (Jean)
				for(int i = 0; i < nuplet.size(); i++){
					file << "new Object(\""+nuplet.at(i)+"\")" << (i==nuplet.size()-1 ? "" : ",");
				}
				file << "));\n";
			}
		}
		//Affichage
		file << "\tcout << \"Listes des prédicats : \"<< endl;\n";
		for(auto p : predicats){
			auto nom = p.first;
			file << "\tcout <<\""<< nom <<" =\\n\" << " << nom << " << endl;\n";
		}
		file << "\n\tcout << \"Déductions pour toutes les règles :\"<< endl;\n";
		std::map<std::string, int> nomRegleMap;
		for(auto r1 : regles){
			auto nom = r1.at(0).first;
			if(nomRegleMap.find(nom)!= nomRegleMap.end()){
				nomRegleMap[nom]++;
			}
			else
			{
				nomRegleMap[nom]=1;
			}
			file << "\t"<< nom << "_deduce";
			file << nomRegleMap[nom];
			file << "();\n";
		}
		for(std::map<std::string,int>::iterator iter=nomRegleMap.begin();iter!=nomRegleMap.end();++iter){
			file << "\tcout <<\""<< iter->first <<" =\\n\" << " << iter->first << " << endl;\n";
		}
		file << "}\n\n";
	}

	static void generateMain(ofstream &file){
		file << "int main(int argc, char **argv){\n";
		file << "\tdeduction();\n";
		file << "};\n\n";
	}


	static void generate_deduce(vector< vector < pair<string, vector<string>> >> regles,  ofstream & file){
		std::map<std::string, int> nomRegleMap;
		for(auto regle : regles){
			multimap<string, pair<string, int>> mapVariables;

			string nomRegle = regle.at(0).first;
			//Gestion des doublons de prédicat supplémentaire
			if(nomRegleMap.find(nomRegle)!= nomRegleMap.end()){
				nomRegleMap[nomRegle]++;
			}
			else
			{
				nomRegleMap[nomRegle]=1;
			}
			auto variablesRegle = regle.at(0).second;
			auto nbpredicat = regle.size();
			auto tuple_size = regle.at(0).second.size();
			file << "void " + nomRegle + "_deduce";
			file << nomRegleMap[nomRegle];
			file << "(){\n";
			string tab = "\t";

			//création du futur parcours de toutes les combinaisons des prédicats
			for(int t = 1; t<regle.size(); t++){
				auto predicat = regle.at(t);
				string nomPredicat = predicat.first;
				file << tab <<"for(auto t" << t << " : " << nomPredicat << "){\n";
				tab += "\t";
				int i = 0;
				for(auto variable : predicat.second){ //pour chaque variable du predicat {X, Y, ...}
						string tString = "t"+to_string(t);
						//variable : nom de la variable, tString : t1/t2/T3..., i :x1/x2
						mapVariables.insert(make_pair(variable, make_pair(tString, i)));
					i++;
				}
			}
			tab += "\t";

			//création des conditions parcourues
			for(auto v1 : mapVariables){
				for(auto v2 : mapVariables){
					//si deux variable du prédicat sont égales donc qu'il faut les comparer :
					// exemple (grand_pere(X,Z):- pere(X,Y), pere(Y,Z).) Y==Y test
					// et si il ne sagit pas du même t donc du même prédicat
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

			//Création du code pour insérer une solution dans la liste finale
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
			file <<"\n";
		}
	}

};
