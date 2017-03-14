#ifndef TESTS_UNITAIRES_H
#define TESTS_UNITAIRES_H

#include "heuristic.h"
#include "graphe.h"
#include "listeSimple.h"
#include "liste.h"
#include "viderLeCache.h"

/* Notes :
	Certaines fonctions sont compliquées à tester.
	Comment savoir qu'on a bien effacer les cases
	en mémoire allouer à une liste ? (par exemple)
	Aussi, ne pouvant tester les heuristiques à
	l'aide de fonctions... (qui faudrait elle même
	tester... vous voyez le cercle vicieux ?) j'ai
	déroulé à la main les différentes heuristiques
	sur un cas à 8 sommets et j'ai comparé avec ce
	que mes fonctions renvoyaient.
	Aussi via l'interface graphique on peut observer
	l'exactitude des heuristiques...
	
	Les testsUnitaires ont été effectués sur les 
	fonctions écrites pour le mode console. Depuis
	quelques changements ont dû être fait pour rendre
	compatibles les fonctions avec l'interface graphique.
	Cela explique la différence de prototypes utilisés
	pour certaines fonctions pour les testUnitaires.
*/

int testsMenu (void);
int afficheTests (void);
int testsListeSimple (void);
int testsListeDouble (void);
int testsGraphe (void);


#endif
