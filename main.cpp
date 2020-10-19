
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <tuple>

using namespace std;

vector<pair<string, vector<vector<string>>>> regles;

int main(int argc, char **argv)
{
	ifstream fichier("prolog.pl", ios::in);
	string ligne;
	vector<vector<string>> arguments;
	while (getline(fichier, ligne))
	{
		bool newRegle = true;
		pair<string, vector<vector<string>>> nouvelleRegle;
		size_t debutArgs = ligne.find('(');
		string regle = ligne.substr(0, debutArgs - 1);
			for (pair<string, vector<vector<string>>> p : regles)
			{
				if(!p.first.compare(regle)){
					nouvelleRegle = p;
					newRegle = false;
					break;
				}
			}
		nouvelleRegle.first = regle;
		int i = debutArgs + 1;
		vector<string> variables;
		while (i < ligne.length())
		{ // boucle jusqu'Ã  la fin de la ligne
			size_t nextArg = ligne.find(',', i);
			if( nextArg == string::npos)
                { // pas de vigule trouvee, on en est au dernier argument
					nextArg = ligne.find('.', i);
					string arg = ligne.substr(i, nextArg-i-1);
					variables.push_back(arg);
                    break;
                }

			string arg = ligne.substr(i, nextArg-i);
			variables.push_back(arg);
			i = nextArg+1;
			
		}
		nouvelleRegle.second.push_back(variables);
					if(newRegle){
						regles.push_back(nouvelleRegle);
					}
		}
	for(pair<string, vector<vector<string>>> p :regles){
		//cout<<p.first<<endl;
			for(vector<string> p2 :p.second){
				for(string p3 :p2){
					cout<<' '<< p.first <<" :"<<p3 << ' ' <<endl;
				}
		}
	}
	fichier.close();
	return 0;
	}
