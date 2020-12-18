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

	vector<string> v; v.push_back("oui"); v.push_back("non");
	l.addPredicate(Predicate("titi", v));
	l.addPredicate("coucou", 4, "victor", "jerome", "tomotei", "matthias");

	vector<Predicate> preds;
	preds.push_back(l.createPredicate("pred1", 4, "X", "Y", "Z", "K"));
	preds.push_back(l.createPredicate("pred2", 2, "Z", "Y"));
	l.addRule("regle", preds, 3, "X", "Y", "Z");

/*
	for(Predicate p : l.getPredicates()){
		std::cout << p << '\n';
	}

	for(Rule r : l.getRules()){
		std::cout << r << '\n';
	}
*/
	l.generateCPP();

	l.exportPl("sortie.pl");

	// l.solvePl();

	return 0;
}
