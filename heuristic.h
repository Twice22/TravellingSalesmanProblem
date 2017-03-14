#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "graphe.h"
#include "liste.h"

Liste* plusProcheVoisin(Graphe* graphe);
Liste* plusProcheAddition (Graphe* graphe);
Liste* insertionMoindreCout (Graphe* graphe);
Liste* insertionPlusLointaine(Graphe* graphe);
void deuxOpt(Graphe* graphe, Liste* listeSommets);


#endif
