
%------EXERCICE 1------


%dicoliste(DL),bondico(X,DL,D).
bondico(X,[dic(X,B,DL)|_],dic(X,B,DL)).
bondico(X,[_|DL],D):-bondico(X,DL,D).

liste(LC):-string_chars("*a", LC).

%liste(LC),cherche(LC,dic('*', false, [dic('a', true, [])])).
%liste(LC),cherche(LC,dic('a', true, [])).
cherche([X],dic(X,true,_)).
cherche([X,Y|L],dic(X,false,[dic(Y,B,D)|DL])):-
cherche([Y|L],dic(Y,B,D)).
cherche([X,Y|L],dic(X,_,[dic(_,_,_)|DL])):-
cherche([Y|L],D_),bondico(Y,DL,D_). 
%X et Z différents donc exploration du reste de la liste

%------EXERCICE 2------

%touslesmots
touslesmots([X],D):-cherche(string_chars(X,L),D).
touslesmots([X|L],D):-
cherche(string_chars(X,L),D).
touslesmots([X|L],D):-
touslesmots(L,D).
%cas ou X est dans la branche, cas ou X est dans une autre branchee

%------EXERCICE 3------
%inserer
ajout(X,dic(X,false,DL),dic(X,true,DL)).
ajout([X,Y|L],dic(X,B,[]),dic(X,B,[dic(Y,false,[])])).
ajout([X,Y|L],dic(X,false,[dic(Z,B,DL_)|DL]),DF):-
ajout([X,Y|L],dic(X,false,[DL]),DF).


inserer([X],D,D_):-ajout(X,D,D_).
inserer([X|L],D,DF):-ajout(X,D,D_),inserer(L,D_,DF).


