pere(roger,michel).
pere(michel,jean).
pere(michel,mathieu).
pere(jean,sarah).
pere(jean,xavier).
mere(marie,michel).
mere(elise,jean).
mere(elise,mathieu).
frere(roger,stephane).
frere(jean,mathieu).
soeur(sarah,xavier).
grand_pere(X,Z):- pere(X,Y), pere(Y,Z).
oncle(X,Z):- frere(X,Y), pere(Y,Z).
oncle(X,Z):- frere(X,Y), mere(Y,Z).
tante(X,Z):- soeur(X,Y), pere(Y,Z).
tante(X,Z):- soeur(X,Y), mere(Y,Z).