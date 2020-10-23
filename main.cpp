#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "ecriture.cpp"
#include "readFile.cpp"
using namespace std;

int main(int argc, char **argv)
{
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

	if(read(fileName))
		Ecriture ecrire(fileName, listPredicat, listRegles);
	
	return 0;
}
