#include "libprolog.h"

vector<Predicate> libprolog::getPredicates(){
  return _predicats;
}

vector<Rule> libprolog::getRules(){
  return _rules;
}

void libprolog::setPredicats(vector<Predicate> predicats){
  _predicats = predicats;
}

void libprolog::setRules(vector<Rule> rules){
  _rules = rules;
}

void libprolog::readPl(string filename){
  if(read(filename)){
    std::cout << "fichier lu" << '\n';
    _filename = filename;

    //remplir liste des _predicats
    for(pair<string, vector<vector<string>>> pair : listPredicat){
      string nomPred = pair.first;
      for(vector<string> v : pair.second ){
        vector<string> listeConstantes;
        for(int i = 0; i<v.size(); i++){
          listeConstantes.push_back(v[i]);
        }
        _predicats.push_back(Predicate(nomPred, listeConstantes));
      }
    }
    //remplir liste des _rules
    for(vector<pair<string, vector<string>>> v : listRegles){
      string nomRegle = v[0].first;
      vector<string> variables = v[0].second;
      vector<Predicate> predicats;
      for(int i=1; i<v.size(); ++i){
        string nomPred = v[i].first;
        vector<string> varPred = v[i].second;
        predicats.push_back(Predicate(nomPred,varPred));
      }
      _rules.push_back(Rule(nomRegle, variables, predicats));
    }
  }
}

void libprolog::addPredicate(Predicate p){
  _predicats.push_back(p);
}

/*filename : nom du fichier avec extension .pl*/
void libprolog::exportPl(string filename){
  ofstream myfile;
  myfile.open(filename);
  //ecriture des preficats au format pl
  for(Predicate p : _predicats){
    myfile << p._nom << "(";
    for(int i=0; i<p._constantes.size(); ++i){
      myfile << p._constantes[i] << (i==p._constantes.size() -1 ? "" : ",");
    }
    myfile << ")." << endl;
  }
  //ecriture des regles au format pl
  for(Rule r : _rules){
    myfile << r._nom << "(";
    for(int i=0; i<r._var.size(); ++i){
      myfile << r._var[i] << (i==r._var.size() -1 ? "" : ",");
    }
    myfile << "):-";
    for(int j=0; j<r._predicatsR.size(); ++j){
      myfile << r._predicatsR[j]._nom << "(";
      for(int k=0; k<r._predicatsR[j]._constantes.size(); ++k){
        myfile << r._predicatsR[j]._constantes[k]
        << (k==r._predicatsR[j]._constantes.size() -1 ? "" : ",");
      }
      myfile << ")" << (j==r._predicatsR.size() -1 ? "." : ",");
    }
    myfile << endl;
  }
  std::cout << "Fichier Prolog créé : " << filename << '\n';
  myfile.close();
}
/*
nom : string le nomPred
n : nombre de constantes
... : une liste de string, les constantes du predicat
*/
void libprolog::addPredicate(string nom, int n, ...){
  vector<string> v_constantes;
  va_list constantes;
  va_start(constantes, n); //la liste des constantes commence apres n
  for(int i=0; i<n; ++i){
    string c = va_arg(constantes, const char *);
    v_constantes.push_back(c);
  }
  va_end(constantes);
  _predicats.push_back(Predicate(nom, v_constantes));
}

void libprolog::addRule(Rule r){
  _rules.push_back(r);
}

/*
nom : string le nomRule
predicats : vector de predicats, corps de la regle
n : nombre de var de la tete de regle
... : une liste de string, les var de la tete de regle
*/
void libprolog::addRule(string nom, vector<Predicate> predicats, int n, ...){
  vector<string> v_var;
  va_list vars;
  va_start(vars, n);
  for(int i=0; i<n; ++i){
    string v = va_arg(vars, const char *);
    v_var.push_back(v);
  }
  va_end(vars);
  _rules.push_back(Rule(nom, v_var, predicats));
}

Predicate libprolog::createPredicate(string nom, int n, ...){
  vector<string> v_constantes;
  va_list constantes;
  va_start(constantes, n); //la liste des constantes commence apres n
  for(int i=0; i<n; ++i){
    string c = va_arg(constantes, const char *);
    v_constantes.push_back(c);
  }
  va_end(constantes);
  return Predicate(nom, v_constantes);
}

Predicate libprolog::createPredicate(string nom, vector<string> constantes){
  return Predicate(nom, constantes);
}

Rule libprolog::createRule(string nom, vector<Predicate> predicats, int n, ...){
  vector<string> v_var;
  va_list vars;
  va_start(vars, n);
  for(int i=0; i<n; ++i){
    string v = va_arg(vars, const char *);
    v_var.push_back(v);
  }
  va_end(vars);
  return Rule(nom, v_var, predicats);
}

Rule libprolog::createRule(string nom, vector<string> var, vector<Predicate> predicats){
  return Rule(nom, var, predicats);
}


void libprolog::generateCPP(){
  //conversion predicats
  vector<pair<string, vector<vector<string>>>> vector_predicats;
  string nompred = _predicats[0].get_nom();
  vector<vector<string>> v_all_constantes;
  for(int i=0; i<_predicats.size(); ++i){
    Predicate p = _predicats[i];
    string newpred = p.get_nom();
    if(nompred == newpred){
      v_all_constantes.push_back(p.get_constantes());
    } else {
      if(i==_predicats.size()-1){
        vector_predicats.push_back(make_pair(nompred, v_all_constantes));
        vector<vector<string>> v_last;
        v_last.push_back(p.get_constantes());
        vector_predicats.push_back(make_pair(newpred, v_last));
      }
      else{
        vector_predicats.push_back(make_pair(nompred, v_all_constantes));
        v_all_constantes.clear();
        v_all_constantes.push_back(p.get_constantes());
        nompred = p.get_nom();
      }
    }
  }
  //conversion regles
  vector<vector<pair<string, vector<string>>>> vector_regles;
  for(int i=0; i<_rules.size(); ++i){
    Rule r = _rules[i];
    vector<pair<string, vector<string>>> v_regle;
    //tete de regle
    v_regle.push_back(make_pair(r.get_nom(), r.get_var()));
    for(int j=0; j<r.get_predicatsR().size(); ++j){
      Predicate pr = r.get_predicatsR()[j];
      v_regle.push_back(make_pair(pr.get_nom(), pr.get_constantes()));
    }
    vector_regles.push_back(v_regle);
  }
  Ecriture ecrire(_filename, vector_predicats, vector_regles);
}

vector<Predicate> libprolog::findPredicates(string nom){
  vector<Predicate> v;
  for(Predicate p : getPredicates()){
    if(p.get_nom() == nom ){
      v.push_back(p);
    }
  }
  return v;
}

void libprolog::doRecursion(int baseCondition, Rule r, vector<Predicate> possiblePredicats,
  multimap<string, pair<int,int>> &mapVariables,
  multimap<pair<int,int>, pair<int, int>> &conditions){
    vector<Predicate> preds = r.get_predicatsR();
    //une fois qu'on a remplit possiblePredicats avec tout les predicats possibles on peu chercher une solution
    if(baseCondition==0){
      reverse(possiblePredicats.begin(), possiblePredicats.end());
      bool continuer = true;
      vector<string> v_sol;
      //on verifie si les conditions sont correctes dans les predicats possibles, c'est donc l'équivalent d'une regle en prolog
      for(auto p: conditions){
        if(continuer && possiblePredicats.at(p.first.first-1)[p.first.second-1] ==
        possiblePredicats.at(p.second.first-1)[p.second.second-1]){
          continuer = true;
        }else{
          continuer = false;
          break;
        }
      }
      string value;
      //si les conditions sont remplies on en deduit les solutions
      if(continuer){
        for(auto var : r.get_var()){
          auto it = mapVariables.find(var);
          if(it != mapVariables.end()){
            value = possiblePredicats.at(it->second.first-1)[it->second.second-1];
            v_sol.push_back(value);
          }
        }
        Predicate deduction(r.get_nom(), v_sol);
        std::cout << "DEDUCTION : " << deduction << '\n';
        _predicats.push_back(deduction);
      }
    } else {
      baseCondition--;
      for(Predicate p : findPredicates(preds[baseCondition].get_nom())){ //liste des instances de preds du corps de r
        possiblePredicats.push_back(p);
        doRecursion(baseCondition, r, possiblePredicats, mapVariables, conditions);
        possiblePredicats.pop_back();
      }
    }
  }

  void libprolog::solvePl(){
    for(Rule r : _rules){
      //multimap variables/position dans r
      multimap<string, pair<int, int>> mapVariables;
      auto corps_regle = r.get_predicatsR();

      //on remplit mapVariables
      for(int i=1; i<=corps_regle.size(); ++i){
        Predicate p = corps_regle[i-1];
        auto var_pred = p.get_constantes();
        for(int j=1; j<=var_pred.size(); ++j){
          mapVariables.insert(make_pair(var_pred[j-1], make_pair(i,j)));
        }
      }
      vector<Predicate> possiblePredicats;
      //nombre de prédicats permettant de déterminer une partie de la recursion
      int taillecorpsregle = r.get_predicatsR().size();
      multimap<pair<int,int>, pair<int, int>> conditions
      = generateConditions(mapVariables);
      //on parcours toutes les combinaisons de variables possibles
      doRecursion(taillecorpsregle, r, possiblePredicats, mapVariables, conditions);
    }
  }

  multimap<pair<int,int>, pair<int, int>> libprolog::generateConditions
  (multimap<string, pair<int, int>> mapVariables){
    //création des conditions parcourues
    multimap<pair<int,int>, pair<int, int>> conditions;
    for(auto v1 : mapVariables){
      for(auto v2 : mapVariables){
        //si deux variable du prédicat sont égales donc qu'il faut les comparer :
        // exemple (grand_pere(X,Z):- pere(X,Y), pere(Y,Z).) Y==Y test
        // et si il ne sagit pas du même t donc du même prédicat
        if((v1.first == v2.first) && (v1.second.first != v2.second.first)){
          //Suppression des doublons dans les conditions
          if (v1.second.first < v2.second.first){
            conditions.insert(make_pair(make_pair(v1.second.first,v1.second.second)
            ,make_pair(v2.second.first,v2.second.second)));
          }
        }
      }
    }
    return conditions;
  }
