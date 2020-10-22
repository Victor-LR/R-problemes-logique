animal(X):- homme(X).
mortel(X):- animal(X).
empoisonne(X):- boit(X,Y), poison(Y).
meurt(X):- mortel(X), empoisonne(X).
homme(socrate).
homme(platon).
ami(socrate,platon).
ami(platon,socrate).
boit(socrate,cigue).
poison(cigue).
