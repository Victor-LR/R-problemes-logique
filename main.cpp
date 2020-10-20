#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

vector<pair<string, vector<vector<string>>>> listPredicat;
vector<vector<pair<string, vector<string>>>> listRegles; //la première paire est le nom de la regle

void readPredicat(string ligne)
{
	bool newPredicat = true; //cas ou regle non existante
	pair<string, vector<vector<string>>> nouveauPredicat;
	size_t debutArgs = ligne.find('(');

	string nomPredicat = ligne.substr(0, debutArgs);
	for (pair<string, vector<vector<string>>> p : listPredicat)
	{
		if (!p.first.compare(nomPredicat))
		{
			nouveauPredicat = p;
			newPredicat = false;
			break;
		}
	}
	nouveauPredicat.first = nomPredicat;
	int i = debutArgs + 1;
	vector<string> variables;
	while (i < ligne.length())
	{ // boucle jusqu'Ã  la fin de la ligne
		size_t nextArg = ligne.find(',', i);

		if (nextArg == string::npos)
		{ // pas de vigule trouvee, on en est au dernier argument
			nextArg = ligne.find(')', i);
			string arg = ligne.substr(i, nextArg - i);
			variables.push_back(arg);
			break;
		}
		string arg = ligne.substr(i, nextArg - i);
		variables.push_back(arg);
		i = nextArg + 1;
	}
	nouveauPredicat.second.push_back(variables);
	if (newPredicat)
	{
		listPredicat.push_back(nouveauPredicat);
	}
	else
	{
		for (auto &p : listPredicat)
		{
			if ((p.first.compare(nouveauPredicat.first)) == 0)
			{
				p.second.push_back(variables);
				break;
			}
		}
	}
}

void readRegle(string ligne)
{
	bool newRegle = true; //cas ou regle non existante
	vector<pair<string, vector<string>>> nouvelleRegle;

	int i = 0;
	while (i < ligne.length())
	{ // boucle jusqu'Ã  la fin de la ligne
		pair<string, vector<string>> predicat;
		size_t debutArgs = ligne.find('(', i);
		string nomPredicat = ligne.substr(i, debutArgs - i);
		if (nomPredicat.find(":-") != string::npos)
		{
			nomPredicat = nomPredicat.substr(2);
		}
		if (nomPredicat.find(",") != string::npos)
		{
			nomPredicat = nomPredicat.substr(1);
		}
		predicat.first = nomPredicat;
		size_t nextArg;
		size_t finRegle = ligne.find(')', i);
		string variablesBrutes = ligne.substr(debutArgs + 1, finRegle - debutArgs - 1);
		int cptVarBrutes = 0;
		vector<string> variables;
		do
		{
			nextArg = variablesBrutes.find(',', cptVarBrutes);
			string arg = variablesBrutes.substr(cptVarBrutes, nextArg - cptVarBrutes);
			cptVarBrutes = nextArg + 1;
			variables.push_back(arg);
			predicat.second = variables;
		} while (nextArg != string::npos);
		nouvelleRegle.push_back(predicat);
		i = finRegle + 1;
		if (ligne.find(".") == i)
		{
			break;
		}
	}
	listRegles.push_back(nouvelleRegle);
}

int main(int argc, char **argv)
{
	string fileName;
	if(argv[1] == nullptr){
		cout<<"paramètre non renseigné"<<endl;
		return 0;
	}else{
		fileName = argv[1];
	}
	ifstream fichier(fileName, ios::in);
	if(!fichier.good()){
		cout<<"le fichier renseigné en paramètre n'existe pas"<<endl;
		return 0;
	}
	string ligne;
	vector<vector<string>> arguments;
	while (getline(fichier, ligne))
	{
		size_t isPredicat = ligne.find(":-");
		if (isPredicat != string::npos)
		{
			readRegle(ligne);
		}
		else
		{
			readPredicat(ligne);
		}
	}
	for (pair<string, vector<vector<string>>> p : listPredicat)
	{
		for (vector<string> p2 : p.second)
		{
			for (string p3 : p2)
			{
				cout << ' ' << p.first << " :" << p3 << ' ' << endl;
			}
		}
	}
	for (auto p : listRegles)
	{
		//cout<<p.first<<endl;
		for (auto p2 : p)
		{
			cout << p2.first;
			for (string p3 : p2.second)
			{
				cout << " " << p3;
			}
			cout << endl;
		}
	}

	fichier.close();
	return 0;
}
