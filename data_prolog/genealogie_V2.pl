pere(roger,michel).
pere(michel,jean).
pere(michel,mathieu).
pere(jean,sarah).
pere(jean,xavier).
pere(xavier,thomas).
mere(marie,michel).
mere(elise,jean).
mere(elise,mathieu).
frere(roger,stephane).
frere(jean,mathieu).
soeur(sarah,xavier).
soeur(anna,roger).
grand_pere(X,Z):- pere(X,Y), pere(Y,Z).
grand_pere(X,Z):- pere(X,Y), mere(Y,Z).
oncle(Y,Z):- frere(X,Y), pere(X,Z).
oncle(Y,Z):- frere(X,Y), mere(X,Z).
tante(X,Z):- soeur(X,Y), pere(Y,Z).
tante(X,Z):- soeur(X,Y), mere(Y,Z).