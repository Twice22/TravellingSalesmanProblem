#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>

#include "listeSimple.h"
#include "constantes.h"


/***************************************************************
**			  AVAIT DEFINTION DU TABLEAU AVANT ICI 			  **
****************************************************************/

typedef float** Matrice;

typedef struct
{
	int nSom; // nombre de sommets
	Matrice valeur; // cout de l'arc (i, j)
	ListeSimple sommet;   //liste des coord des sommets numérotés de 0 à n
} Graphe;

Graphe* creerGraphe (int n);
void desallouerGraphe (Graphe* graphe);
void ajouterUnSommet (Graphe* graphe, int numeroSom, int abscisse, int ordonnee);
void ajouterUnArc (Graphe* graphe, int numeroSomD, int numeroSomA, float cout);

void lireBlancs (FILE* fichier);
int lireUnMot (FILE* fichier);
void lireUneCoord(FILE* fichier, int *abscisse, int *ordonnee);
Graphe* lireGraphe (FILE* fichier);

float distance(Coord pt1, Coord pt2);
void pointOuDisque(int largeur, int hauteur, char* pointOuDisque, int nbPoints, int* rayon);
void echange(Coord* a, Coord* b);
Graphe* completerGraphe(int largeur, int hauteur, int nbPoints, char* ptOuDisque, int* rayon, Graphe* graphe);
void sauvegarderGraphe(Graphe* graphe, Liste* liste, char* nomFichier);

/* fonction pour l'affichage en console. Inutile pour 
le programme final avec représentation graphique. */
void ecrireGraphe (Graphe* graphe);



#endif
