#ifndef TESTS_UNITAIRES_H
#define TESTS_UNITAIRES_H

#include "heuristic.h"
#include "graphe.h"
#include "listeSimple.h"
#include "liste.h"
#include "viderLeCache.h"

/* Notes :
	Certaines fonctions sont compliqu�es � tester.
	Comment savoir qu'on a bien effacer les cases
	en m�moire allouer � une liste ? (par exemple)
	Aussi, ne pouvant tester les heuristiques �
	l'aide de fonctions... (qui faudrait elle m�me
	tester... vous voyez le cercle vicieux ?) j'ai
	d�roul� � la main les diff�rentes heuristiques
	sur un cas � 8 sommets et j'ai compar� avec ce
	que mes fonctions renvoyaient.
	Aussi via l'interface graphique on peut observer
	l'exactitude des heuristiques...
	
	Les testsUnitaires ont �t� effectu�s sur les 
	fonctions �crites pour le mode console. Depuis
	quelques changements ont d� �tre fait pour rendre
	compatibles les fonctions avec l'interface graphique.
	Cela explique la diff�rence de prototypes utilis�s
	pour certaines fonctions pour les testUnitaires.
*/

int testsMenu (void);
int afficheTests (void);
int testsListeSimple (void);
int testsListeDouble (void);
int testsGraphe (void);


#endif
