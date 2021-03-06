#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

static vector<pair<string, vector<vector<string>>>> listPredicat;
static vector<vector<pair<string, vector<string>>>> listRegles; //la première paire est le nom de la regle

//Suppression des espaces
static std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

static std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

static std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

static void analyseVariable(string s){
    size_t test = s.find("(");
    if (test != string::npos)
    {
        throw string("Error: Arguments dans la règle non correctes dans le fichier .pl");
    }
}

//Lecture des prédicats
static bool readPredicat(string ligne)
{
    bool newPredicat = true; //cas ou regle non existante
    pair<string, vector<vector<string>>> nouveauPredicat;
    size_t debutArgs = ligne.find('(');
    if (debutArgs == string::npos)
    {
        return false;
    }
    string nomPredicat = ligne.substr(0, debutArgs);
    nomPredicat = trim(nomPredicat);
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
    {
        // boucle jusqu'a  la fin de la ligne
        size_t nextArg = ligne.find(',', i);

        if (nextArg == string::npos)
        {
            // pas de vigule trouvee, on en est au dernier argument
            nextArg = ligne.find(')', i);
            string arg = ligne.substr(i, nextArg - i);
            variables.push_back(trim(arg));
            break;
        }
        string arg = ligne.substr(i, nextArg - i);
        try
        {
            analyseVariable(arg);
        }
        catch(string const & e)
        {
            cerr << e <<'\n';
            return false;
        }

        variables.push_back(trim(arg));
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
    return true;
}

static bool contains(vector<pair<string, vector<string>>> v, string regle)
{
    for (auto it : v)
    {
        if (!it.first.compare(regle))
        {
            return true;
        }
    }
    return false;
}

static void sortRegles()
{
    vector<string> regleExiste;
    for (int it1 = 0; it1<listRegles.size();it1++ )
    {
        for (int it2 = it1 +1 ; it2<listRegles.size();it2++ )
        {
                //listRegles[it2][0] 0 car il n'y a que le nom de la règle qui nous interesse
                if (contains(listRegles[it1], listRegles[it2][0].first))
                {
                    vector<pair<string, vector<string>>> tmp;
                    tmp = listRegles[it1];
                    listRegles[it1] = listRegles[it2];
                    listRegles[it2] = tmp;
                }
        }
    }
}

static bool readRegle(string ligne)
{
    bool newRegle = true; //cas ou regle non existante
    vector<pair<string, vector<string>>> nouvelleRegle;
    string variablesBrutes;
    bool erreur = false;
    int i = 0;
    while (i < ligne.length())
    {
        // boucle jusqu'Ã  la fin de la ligne
        pair<string, vector<string>> predicat;
        size_t debutArgs = ligne.find('(', i);
        string nomPredicat = ligne.substr(i, debutArgs - i);
        if (nomPredicat.find(":-") != string::npos)
        {
            nomPredicat = nomPredicat.substr(2);
            nomPredicat = trim(nomPredicat);
        }
        if (nomPredicat.find(",") != string::npos)
        {
            nomPredicat = nomPredicat.substr(1);
            nomPredicat = trim(nomPredicat);
        }
        predicat.first = nomPredicat;
        size_t nextArg;
        size_t finRegle = ligne.find(')', i);
        variablesBrutes = ligne.substr(debutArgs + 1, finRegle - debutArgs - 1);
        int cptVarBrutes = 0;
        try{
            analyseVariable(variablesBrutes);
            vector<string> variables;
            do
            {
                nextArg = variablesBrutes.find(',', cptVarBrutes);
                string arg = variablesBrutes.substr(cptVarBrutes, nextArg - cptVarBrutes);
                cptVarBrutes = nextArg + 1;
                variables.push_back(trim(arg));
                predicat.second = variables;
            } while (nextArg != string::npos);
            nouvelleRegle.push_back(predicat);
            i = finRegle + 1;
            if (ligne.find(".") == i)
            {
                break;
            }
        }
        catch (string const &s){
            cerr<< s << endl;
            return false;
        }
        // analyseVariable(variablesBrutes);
    }
    listRegles.push_back(nouvelleRegle);
    //mettre les regles dans le bon ordre pour l'execution
    sortRegles();
    return true;
}

static bool read(string fileName)
{
    ifstream fichier(fileName, ios::in);
    if (!fichier.good())
    {
        cout << "le fichier renseigné en paramètre n'existe pas" << endl;
        throw runtime_error("Could not open file");
        return false;
    }
    string ligne;
    vector<vector<string>> arguments;
    while (getline(fichier, ligne))
    {
        size_t isPredicat = ligne.find(":-");
        if (isPredicat != string::npos)
        {
            if(!readRegle(ligne))
                return false;
        }
        else
        {
            readPredicat(ligne);
        }
    }
    fichier.close();
    return true;
}
