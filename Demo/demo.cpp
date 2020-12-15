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

	return 0;
}
