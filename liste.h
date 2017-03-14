#ifndef LISTE_H
#define LISTE_H

#include "point.h"

/***********************************************************************
**	             LISTE DOUBLEMENT CHAINEE POUR LE PARCOURS            **
************************************************************************/


typedef struct e
{
	float cout;	//cout pour passer du sommet prec à celui-ci
	Coord point;
    int numeroSom; // nom des sommets
    struct e* prec;
    struct e* suiv;
} Liste;


Liste* creerListe (void);
void viderListe (Liste* liste);
void supprimerListe (Liste** liste);

void ajouterAvant (Liste* monElement, int numeroSommet, Coord monPoint, float cout);
void ajouterApres (Liste* monElement, int numeroSommet, Coord monPoint, float cout);
void ajouterEnTete (Liste* racine, int numeroSommet, Coord monPoint, float cout);
void ajouterEnQueue (Liste* racine, int numeroSommet, Coord monPoint, float cout);
void supprimerElement (Liste* elementASupprimer);

void ecrireListe (Liste* liste);
void modifierElement (Liste* liste, float cout);


#endif
