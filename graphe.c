/**
 * \file graphe.c
 * \brief Structure de graphe
 * \author Victor.B
 * \version 1.1
 * \date 9 mai 2013
 *
 * Fonction de création et de manipulation de graphe.
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include <time.h>

#include "graphe.h"
#include "liste.h"
#include "viderLeCache.h"

/***************************************************************************
**			  PENSER A CHANGER POUR UNE MATRICE TRIANGULAIRE			  **
****************************************************************************/

/**
 * \fn Graphe* creerGraphe (int n)
 * \brief Fonction de création d'un graphe vide.
 *
 * \param n Nombre de sommets du graphe.
 * \return Graphe vide avec n sommets.
 */
Graphe* creerGraphe (int n)
{
	// allocation de graphe
	Graphe* graphe = (Graphe*) malloc (sizeof (Graphe));
	graphe->nSom = 0;
	graphe->sommet = nouvelleListe();
	graphe->valeur = (float**) malloc (n*sizeof(float*));

	// allocation de la matrice des couts de l'arc (i,j)
	if ( (graphe->valeur) == NULL)
		{
			fprintf(stderr, "Code de l'erreur : %d\n", errno);
			perror("Erreur ");
			exit (EXIT_FAILURE);
		}
	if ( ( graphe->valeur[0] = (float*) malloc (n*n*sizeof(float)) ) == NULL)
			{
				fprintf(stderr, "Code de l'erreur : %d\n", errno);
				perror("Erreur ");
				exit (EXIT_FAILURE);
			}

	// initialisation du tableau de pointeurs sur int
	int i;
	for (i = 0 ; i < n ; i++)
	{
		graphe->valeur[i] = graphe->valeur[0] + i*n;
	}

	// par défaut distance INFINI
	// entre les sommets et sommets non visites
	for (i = 0 ; i < n ; i++)
	{
		int j;
		for (j = 0 ; j < n ; j++)
		{
			graphe->valeur [i][j] = INFINI;
		}
	}
for (i = 0 ; i < n ; i++)
	graphe->valeur [i][i] = 0;

return graphe;
}

/**
 * \fn void desallouerGraphe (Graphe* graphe)
 * \brief Fonction qui supprime un graphe
 *
 * \param graphe Graphe à supprimer
 */
void desallouerGraphe (Graphe* graphe)
{
	graphe->sommet = viderListeSimple(graphe->sommet);
	free (graphe->valeur[0]);
	free (graphe->valeur);
	free (graphe);
	graphe = NULL;
}

/**
 * \fn static int rang (Graphe* graphe, int numeroSom)
 * \brief Fonction qui retourne le numéro du sommet recherché
 *
 * \param[in] graphe Graphe dans lequel recherché le sommet
 * \param[in] numeroSom Numero du sommet recherché dans le graphe.
 * \return Le numéro du sommet recherche s'il existe. -1 sinon.
 */
static int rang (Graphe* graphe, int numeroSom)
{
  /* Cette fonction peut sembler ne servir à rien mais
     elle est utile pour vérifier que tout ce passe bien
     et je l'ai implémenter pour le cas ou le graphe ne
     serait pas euclidien. Si on a envie d'apporter des
     améliorations au programme */
	Booleen trouve = FAUX;
	ListeSimple copie = graphe->sommet;
	while (copie != NULL && !trouve )
		{
			trouve = copie->numero == numeroSom;
			if (!trouve) copie = copie->lien;
		}

return trouve ? copie->numero : -1;		//retourne (-1) si pas trouvé
}

/**
 * \fn void ajouterUnSommet (Graphe* graphe, int numeroSom, int abscisse, int ordonnee)
 * \brief Fonction qui ajoute un sommet au graphe.
 *
 * \param[in] graphe Graphe dans lequel ajouter le sommet
 * \param[in] numeroSom Numero du sommet à ajouter au graphe
 * \param[in] abscisse Abscisse du sommet à ajouter au graphe
 * \param[in] ordonnee Ordonnée du sommet à ajouter au graphe
 */
void ajouterUnSommet (Graphe* graphe, int numeroSom, int abscisse, int ordonnee)
{
	if (rang (graphe, numeroSom) == -1) // si pas trouvé le sommet
	{
		if (graphe->nSom < SOMMETMAX) //on l'ajoute en position n+1
		{
            Coord monPoint;
            monPoint.x = abscisse ; monPoint.y = ordonnee;
			graphe->sommet = enlister (graphe->sommet, numeroSom, monPoint);
			graphe->nSom++;
		}
		else
			fprintf (stderr, "\nNombre de sommets > %d\n", SOMMETMAX);
	}
	else
		printf ("\n%d deja defini\n", numeroSom);
}

/**
 * \fn void ajouterUnArc (Graphe* graphe, int numeroSomD, int numeroSomA, float cout)
 * \brief Fonction qui relie un sommet à un autre du graphe
 *
 * \param[in] graphe Graphe dans lequel relier les 2 sommets
 * \param[in] numeroSomS Numero du sommet de départ
 * \param[in] numeroSomA Numero du sommet d'arrivée
 * \param[in] cout Distance entre les deux sommets
 */
void ajouterUnArc (Graphe* graphe, int numeroSomD, int numeroSomA, float cout)
{
	int rd = rang (graphe, numeroSomD);
	int rg = rang (graphe, numeroSomA);
	graphe->valeur [rd][rg] = cout;

}

/***********************************************************************
**			  FONCTION DE LECTURE ET D'ECRITURE D'UN GRAPHE			  **
************************************************************************/


/***********************************************************************
**   format du fichier à lire :										  **
**																	  **
**   S0 [12,25] S1 [12,25] S2 [12,25] S3 [12,25] ;					  **
**   S0 : S1 (10) S2 (12) S3 (12) ;									  **
**   S1 : S0 (30) S2 (33) S3 (15) ;									  **
**   S2 : S0 (18) S1 (12) S3 (14);									  **
**   S3 : S0 (33) S1 (17) S2 (21);									  **
************************************************************************/

int c; // représente le caractère lu

/**
 * \fn void lireBlancs (FILE* fichier)
 * \brief Fonction qui ignore les espaces et les S à la lecture d'un fichier
 *
 * \param[in] fichier Fichier texte que doit lire la fonction
 */
void lireBlancs (FILE* fichier)
{
    while ( ( (c==' ') || (c=='\n') || (c==13) ) && !feof(fichier) )    // 13 : retour chariot !
        c = getc(fichier);
}

/**
 * \fn int lireUnMot (FILE* fichier)
 * \brief Fonction qui lit un numero de sommet dans un fichier de type au format 'graphe'
 *
 * \param[in] fichier Fichier texte au format 'graphe' que doit lire la fonction
 * \return Le numéro du sommet lu si pas d'erreur. (-1) sinon.
 */
int lireUnMot (FILE* fichier)
{
    if (c !=';')
    {
            int cint;
            fscanf(fichier, "%i", &cint);
                c = getc(fichier); //passe [
                while (isdigit (c))
                    c = getc(fichier);

        lireBlancs(fichier);

        return cint;
    }
    return -1;

}

/**
 * \fn void lireUneCoord(FILE* fichier, int *abscisse, int *ordonnee)
 * \brief Fonction qui lit les coordonnées d'un sommet dans un fichier tete au format 'graphe'
 *
 * \param[in] fichier Fichier texte au format 'graphe' que doit lire la fonction
 * \param[in] abscisse Abscisse du sommet lu dans le fichier texte
 * \param[in] ordonnee Ordonnée du sommet lu dans le fichier texte
 */
void lireUneCoord(FILE* fichier, int *abscisse, int *ordonnee)
{
    fscanf(fichier, "%d", abscisse);
    c = getc(fichier); //passe [
        while (isdigit (c))
            c = getc(fichier);
    fscanf(fichier, "%d", ordonnee);
    c = getc(fichier); //passe ,
        while (isdigit (c))
            c = getc(fichier);
    c = getc(fichier); //passe ]
    lireBlancs(fichier);
}

/**
 * \fn Graphe* lireGraphe (FILE* fichier, int n)
 * \brief Fonction qui fournit un pointeur sur un graphe construit à partir
 * \brief d'un fichier texte au format 'graphe'. graphe doit être non NULL.
 *
 * \param[in] fichier Fichier texte au format 'graphe' que doit lire la fonction
 * \param[in] n (Nombre de sommets)+1 que contient le fichier texte.
 * \return un pointeur sur le graphe créé.
 */
Graphe* lireGraphe (FILE* fichier)
{
    int n;
    fscanf (fichier, "%i", &n);
    Graphe* graphe = creerGraphe (n);

    Booleen fini = FAUX;
    // lire les noms des sommets
    c = getc(fichier); // passe le nombre de sommets
    c = getc(fichier); // c global
    while (!fini)
    {
        int abscisse, ordonnee, numeroSomD;
        numeroSomD = lireUnMot (fichier);

            if (numeroSomD == -1) break;

        lireUneCoord (fichier, &abscisse, &ordonnee);
        ajouterUnSommet (graphe, numeroSomD, abscisse, ordonnee);
    }

    while (c != EOF)
    {
        c = getc(fichier); // passe ;
        c = getc(fichier);
        int numeroSomD;
        numeroSomD = lireUnMot (fichier); // lit le sommet de départ
        lireBlancs(fichier);
        if (c != ':')
        {
            if (c != EOF) printf ("Manque : %c (%d)\n", c,c);
            return graphe;
        }
        c = getc(fichier); // passe :
        while (c != ';')
        {
            int numeroSomA;
            lireBlancs (fichier);
            numeroSomA = lireUnMot (fichier); // lit les sommets d'arrivée
            lireBlancs(fichier);
            float cout;

                fscanf (fichier, "%f", &cout);
                c = getc (fichier); // passer )
                if (c != ')') printf ("Manque )\n");
                c = getc (fichier);
                lireBlancs (fichier); // prochain à analyser
                ajouterUnArc (graphe, numeroSomD, numeroSomA, cout);
        }
    }
    return graphe;
}

/**
 * \fn void ecrireGraphe (Graphe* graphe)
 * \brief Fonction qui affiche sur la console les éléments du graphe
 *
 * \param[in] graphe Le graphe dont ont veut afficher les éléments
 */
void ecrireGraphe (Graphe* graphe)
{
    ListeSimple copie = graphe->sommet;
    ListeSimple copie1 = graphe->sommet;
    while (copie != NULL)
		{
		    printf ("S%d [%d,%d] ", copie->numero, copie->point.x, copie->point.y);
		    copie = copie->lien;
		}
	printf (";\n");

	while (copie1 != NULL)
	{
	    ListeSimple copie2 = graphe->sommet;
		printf ("\nS%d : ", copie1->numero);
		while (copie2 != NULL)
			{
				printf ("S%d ", copie2->numero);
				printf (" (%f) ", graphe->valeur [copie1->numero][copie2->numero] );
				copie2 = copie2->lien;

            }
        copie1 = copie1->lien;
    }
		printf (";");
}

/**
 * \fn float distance(Coord pt1, Coord pt2)
 * \brief Fonction qui retourne la distance entre 2 points
 *
 * \param[in] pt1 coordonnées du premier point.
 * \param[in] pt2 coordonnées du deuxième point.
 * \return un flottant représentant la distance entre les deux points.
 */
float distance(Coord pt1, Coord pt2)
{
    return sqrt((pt2.x - pt1.x)*(pt2.x - pt1.x) + (pt2.y - pt1.y)*(pt2.y - pt1.y));
}


/**
 * \fn void pointOuDisque(int largeur, int hauteur, int nbPoints, int* rayon)
 * \brief Fonction qui demande si on veut un affichage par points
 * \brief ou par disques. Si on choisit par points alors un sommet
 * \brief est représenté par un pixel. Si on choisit par disque alors
 * \brief la fonction détermine un rayon adéquate aux vus des données.
 *
 * \param[in] largeur Largeur de la fenêtre où sont contenus les sommets
 * \param[in] hauteur Hauteur de la fenêtre où sont contenus les sommets
 * \param[in] nbPoints Nombre de sommets dans le graphe.
 * \param[out] rayon Rayon adequate des disques représentant les sommets
 */
void pointOuDisque(int largeur, int hauteur, char* pointOuDisque, int nbPoints, int* rayon)
{
    int espace = largeur*hauteur;
    if (nbPoints < SOMMETMAX)
        /* pas besoin d effectuer ce test car cette fonction est appelée
        par la fonction creerLaListeSommets qui effectue ce test */
    {
        if (!strcmp(pointOuDisque, "Points"))
        {
            *rayon = 0;
        }

        else    // type Disque choisi
        {
            float spacing = 0.20;

            // SOMMMETMAX << espace donc pas de test sur l'espace dispo
            *rayon = (int) sqrt(espace*spacing/(nbPoints))/2;
        }
    }
    else
        fprintf(stderr, "\nErreur: le nombre entre : %d dépasse %d\n\n", nbPoints, SOMMETMAX);


}

/**
 * \fn void echange(Coord* a, Coord* b)
 * \brief Fonction qui echange deux valeurs.
 *
 * \param[out] a Coordonnée du point A
 * \param[out] b Coordonnée du point B
 */
void echange(Coord* a, Coord* b)
{
    Coord temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * \fn Graphe* completerGraphe(int largeur, int hauteur, int* rayon, Graphe* graphe)
 * \brief Fonction qui tire aléatoirement des coordonnées du plan et qui les placent
 * \brief dans la liste simplement chaînée des sommets du graphe. Les points ainsi
 * \brief créés dans le plan ne se recouvrent pas. graphe doit être non NULL.
 *
 * \param[in] largeur Largeur de la fenêtre où sont contenus les sommets
 * \param[in] hauteur Hauteur de la fenêtre où sont contenus les sommets
 * \param[out] rayon Rayon adequate des disques représentant les sommets
 * \param[in] graphe Graphe qui doit contenir la liste créée.
 * \return un pointeur sur Graphe.
 */
Graphe* completerGraphe(int largeur, int hauteur, int nbPoints, char* ptOuDisque, int* rayon, Graphe* graphe)
{
    int nbPixels = largeur*hauteur;

    if (nbPoints > SOMMETMAX)
    {
		fprintf(stderr, "\nErreur: le nombre entre : %d depasse %d\n\n", nbPoints, SOMMETMAX);
        return NULL;
    }

    graphe = creerGraphe (nbPoints);
    pointOuDisque(largeur, hauteur, ptOuDisque, nbPoints, rayon);

    if (*rayon == 0)     // Il a choisi la représentation par point.
    {
        Coord* tabSommet = (Coord*) malloc(nbPixels * sizeof(Coord));
        int i, j;
        for (i = 0 ; i < largeur ; i++ )
        {
            for (j = 0 ; j < hauteur ; j++)
            {
                tabSommet[i + j*largeur].x = i;
                tabSommet[i + j*largeur].y = j;
            }
        }

        srand(time(NULL));
        //melange des valeurs
        for (i = 0 ; i < largeur ; i++ )
        {
            for (j = 0 ; j < hauteur ; j++)
            {
                echange(&tabSommet[i + j*largeur], &tabSommet[(rand () % largeur) + (rand () % hauteur)*largeur]);
            }

        }

        //remplir la liste avec les nbPoints premiers points du sommet.
        for (i = 0 ; i < nbPoints ; i++)
        {
            graphe->sommet = enlister (graphe->sommet, i, tabSommet[i]);
            graphe->nSom++;

            //crer la matrice
            graphe->valeur[i][i] = 0;
            for (j = i+1 ; j < nbPoints ; j++)
            {
                graphe->valeur[i][j] = graphe->valeur[j][i] = distance(tabSommet[i], tabSommet[j]);
            }
        }

        free(tabSommet);

    }
    else    // C'est un disque. On tire des points à la force "brute".
    {
        Coord* tabDisques = (Coord*) malloc(nbPoints * sizeof(Coord));

        //initialisation du tableau des coords des centres des disques à (-1,-1) sauf .[0]
        int i, j;
        tabDisques[0].x = *rayon + rand()%(largeur-2* (*rayon) );
        tabDisques[0].y = *rayon + rand()%(hauteur-2* (*rayon) );
        for (i = 1 ; i < nbPoints ; i++)
        {
            tabDisques[i].x = -1; tabDisques[i].y = -1;
        }

        // remplissage du tab avec coord des centres des disques sans recouvrement
        i = 1;
        while (i < nbPoints)
        {
            tabDisques[i].x = *rayon + rand()%(largeur-2* (*rayon) );
            tabDisques[i].y = *rayon + rand()%(hauteur-2* (*rayon) );
            j = 0;
            while (j < i && distance(tabDisques[j], tabDisques[i]) > 2* (*rayon) )
                j++;
            if (j == i)   //pas de recouvrement
			i++;
        }

        // remplissage de la liste des sommets de la structure de graphe
        for (i = 0 ; i < nbPoints ; i++)
        {
            graphe->sommet = enlister (graphe->sommet, i, tabDisques[i]);
            graphe->nSom++;


            //crer la matrice
            graphe->valeur[i][i] = 0;
            for (j = i+1 ; j < nbPoints ; j++)
            {
                graphe->valeur[i][j] = graphe->valeur[j][i] = distance(tabDisques[i], tabDisques[j]);
            }
        }

        free(tabDisques);
    }

    return graphe;
}

/**
 * \fn void sauvegarderGraphe(Graphe* graphe, Liste* liste)
 * \brief Sauvegarde des données d'un graphe dans un fichier texte.
 *
 * \param[in] graphe Graphe à sauvegarder.
 */
void sauvegarderGraphe(Graphe* graphe, Liste* liste, char* nomFichier)
{
    FILE* sauvegarde = fopen(nomFichier, "w");
            if (sauvegarde == NULL)
            {
                printf ("Code de l'erreur : %d\n", errno);
                perror("nomFichier");
            }
            else
            {
                fprintf(sauvegarde, "%i\n", graphe->nSom+1);
                Liste* elementCourant = liste->suiv;
                for ( ; elementCourant != liste ; elementCourant = elementCourant->suiv)
                {
                    fprintf(sauvegarde, "S%d [%d,%d] ", elementCourant->numeroSom, elementCourant->point.x, elementCourant->point.y);
                }
                fputs(";\n", sauvegarde);
            }

            int i;
            for (i = 0 ; i < graphe->nSom ; i++)
			{
				fprintf(sauvegarde, "S%d : ", i);

                int j;
                for (j = 0 ; j < graphe->nSom ; j++)
				{
					fprintf(sauvegarde, "S%d (", j);
					fprintf(sauvegarde, "%f) ", graphe->valeur[i][j]);
				}
			fprintf(sauvegarde, ";\n");
			}

    fclose(sauvegarde);
}

