voisins(rouge,vert).
voisins(rouge,bleu).
voisins(vert,rouge).
voisins(vert,bleu).
voisins(bleu,rouge).
voisins(bleu,vert).
coloriage(X1,X2,X3,X4):- voisins(X1,X2), voisins(X1,X4), voisins(X2,X3), voisins(X2,X4), voisins(X3,X4).
