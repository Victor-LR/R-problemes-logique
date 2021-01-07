#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include "../lib/libprolog.h"
using namespace std;

int main(int argc, char **argv)
{
	libprolog l;
	string fileName;
	if (argv[1] == nullptr)
	{
		cout << "paramètre non renseigné" << endl;
		return 0;
	}
	else
	{
		fileName = argv[1];
	}

	l.readPl(fileName);

	std::cout << "Liste des Faits : " << '\n';
	for(Predicate p : l.getPredicates()){
		std::cout << p << '\n';
	}

	std::cout << "=====================" << '\n';

	std::cout << "Liste des Regles : " << '\n';
	for(Rule r : l.getRules()){
		std::cout << r << '\n';
	}

	l.generateCPP();

	l.solvePl();

	std::cout << "=====================" << '\n';
	std::cout << "Liste des Faits après déductions : " << '\n';
	for(Predicate p : l.getPredicates()){
		std::cout << p << '\n';
	}

	l.addPredicate("boit", 2, "platon", "soda");

	vector<Predicate> preds;
	preds.push_back(l.createPredicate("homme", 1, "X"));
	l.addRule("philosophe", preds, 1, "X");

	l.exportPl("sortie.pl");


	return 0;
}
