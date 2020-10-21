pere(roger,michel).
pere(michel,jean).
pere(michel,mathieu).
pere(jean,sarah).
grand_pere(X,Z):- pere(X,Y), pere(Y,Z).
