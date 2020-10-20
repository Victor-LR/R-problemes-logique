voisins(rouge,vert).
voisins(rouge,bleu).
voisins(vert,rouge).
voisins(vert,bleu).
voisins(bleu,rouge).
voisins(bleu,vert).
coloriage(X1,X2,X3,X4) :- voisin(X1,X2), voisin(X1,X4), voisin(X2,X3), voisin(X2,X4), voisin(X3,X4).

