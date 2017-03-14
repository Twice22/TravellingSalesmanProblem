#ifndef LISTE_SIMPLE_H
#define LISTE_SIMPLE_H

#include "booleen.h"
#include "point.h"

/**********************************************************************************
* PENSER A METTRE LES TYPEDEF DANS DES FICHIERS A PART ET A METTRE coord en Coord *
***********************************************************************************/

/*******************************************************************************
**			  LISTE SIMPLEMENT CHAINEE POUR LES INFOS SUR LES PTS 			  **
********************************************************************************/


typedef struct element
{
    int numero;     //numero du sommet
    Coord point; //include liste.h
    struct element *lien;
} Element;

typedef Element *ListeSimple;


ListeSimple nouvelleListe (void);
Booleen estListeVide (ListeSimple liste);
ListeSimple enlister (ListeSimple liste, int v, Coord monPoint);
ListeSimple delister (ListeSimple liste, int v);
ListeSimple viderListeSimple (ListeSimple liste);

// fonctions pour tester les autres
void parcourirListe (ListeSimple liste);

#endif
