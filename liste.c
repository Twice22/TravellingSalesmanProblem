/**
 * \file liste.c
 * \brief Liste doublement chaînées
 * \author Victor.B
 * \version 1.1
 * \date 9 mai 2013
 *
 * Liste doublement chaînées pour le stockage des sommets du graphe
 * par les différentes heurisitiques utilisées.
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "liste.h"


/***********************************************************************
**			  CREATION SUPPRESION ET VIDAGE DE LA LISTE				  **
************************************************************************/


/**
 * \fn Liste* creerListe (void)
 * \brief Fonction de création d'une liste doublement chaînées vide.
 *
 * \return Liste doublement chaînées vide.
 */
Liste* creerListe (void)
{
    Liste* maListe = (Liste *) malloc ( sizeof *maListe );
    if ( maListe != NULL )
    {
        maListe->prec = maListe;
        maListe->suiv = maListe;
    }
    return maListe;
}

/**
 * \fn void viderListe (Liste* liste)
 * \brief Fonction de vidage d'une liste doublement chaînées.
 *
 * \param liste Liste doublement chaînée à vider.
 */
// On vide la liste
void viderListe (Liste* liste)
{
    Liste *it, *next;

    for ( it = liste->suiv; it != liste; it = next )
    {
        next = it->suiv;  // on enregistre le pointeur sur l'élément suivant avant de supprimer l'élément courant
        free(it);         // on supprime l'élément courant
    }
}

/**
 * \fn void supprimerListe (Liste** maListe)
 * \brief Fonction de suppression d'une liste doublement chaînée
 *
 * \param maListe Liste doublement chaînée à supprimer
 */
void supprimerListe (Liste** maListe)
{
    viderListe( *maListe );  /* on vide d'abord la liste */
    free( *maListe ), *maListe = NULL;
}

/***********************************************************************
**					FONCTION DE MANIPULATION DES LISTES				  **
************************************************************************/

/**
 * \fn void ajouterAvant (Liste* monElement, int numeroSommet, Coord monPoint, float cout)
 * \brief Fonction qui permet d'ajouter un élément à la liste avant l'élément courant de ma liste.
 *
 * \param[in] monElement Elément courant de la liste.
 * \param[in] numeroSommet Numero du nouvel élément à ajouter à la liste.
 * \param[in] monPoint Coordonnées du nouvel élément à ajouter à la liste.
 * \param[in] cout Distance à parcourir entre le nouvel élément à ajouter et l'élement courant de la liste.
 */
//Ajouter un élement nouvel_element appelé nomSommet avant monElement de ma liste
void ajouterAvant (Liste* monElement, int numeroSommet, Coord monPoint, float cout)
{
    Liste* nouvelElement = (Liste *) malloc ( sizeof *nouvelElement );
    if ( nouvelElement != NULL )
    {
		// on affecte les informations au nouvel élément.
        nouvelElement->numeroSom = numeroSommet;
		nouvelElement->point = monPoint;
		nouvelElement->cout = cout;

        // on définit les pointeurs du nouvel élément
        nouvelElement->prec = monElement->prec;
        nouvelElement->suiv = monElement;

        // on modifie les éléments de la liste
        monElement->prec->suiv = nouvelElement;
        monElement->prec = nouvelElement;

    }
}

/**
 * \fn void ajouterApres (Liste* monElement, int numeroSommet, Coord monPoint, float cout)
 * \brief Fonction qui permet d'ajouter un élément à la liste après l'élément courant de ma liste.
 *
 * \param[in] monElement Elément courant de la liste.
 * \param[in] numeroSommet Numero du nouvel élément à ajouter à la liste.
 * \param[in] monPoint Coordonnées du nouvel élément à ajouter à la liste.
 * \param[in] cout Distance à parcourir entre l'élément courant de la lite et le nouvel élément à ajouter.
 */
//Ajouter un élement nouvel_element appelé nomSommet après monElement de ma liste
void ajouterApres (Liste* monElement, int numeroSommet, Coord monPoint, float cout)
{
    Liste* nouvelElement = (Liste *) malloc ( sizeof *nouvelElement );
    if ( nouvelElement != NULL )
    {
		// on affecte les informations au nouvel élément.
        nouvelElement->numeroSom = numeroSommet;
		nouvelElement->point = monPoint;
		nouvelElement->cout = cout;

        // on définit les pointeurs du nouvel élément
        nouvelElement->prec = monElement;
        nouvelElement->suiv = monElement->suiv;

        // on modifie les éléments de la liste
        monElement->suiv->prec = nouvelElement;
        monElement->suiv = nouvelElement;

    }
}

/**
 * \fn void ajouterEnTete (Liste* racine, int numeroSommet, Coord monPoint, float cout)
 * \brief Fonction qui permet d'ajouter un élément en tête de la liste.
 *
 * \param[in] racine Premier élément de la liste.
 * \param[in] numeroSommet numero du nouvel élément à ajouter en tête de liste.
 * \param[in] monPoint Coordonnées du nouvel élément à ajouter en tête de liste.
 * \param[in] cout Distance à parcourir entre l'élément à ajouter et l'élément courant de la liste.
 */
void ajouterEnTete (Liste* racine, int numeroSommet, Coord monPoint, float cout)
{
    ajouterApres (racine, numeroSommet, monPoint, cout);
}

/**
 * \fn void ajouterEnQueue (Liste* racine, int numeroSommet, Coord monPoint, float cout)
 * \brief Fonction qui permet d'ajouter un élément en queue de la liste.
 *
 * \param[in] racine Premier élément de la liste.
 * \param[in] numeroSommet numero du nouvel élément à ajouter en queue de liste.
 * \param[in] monPoint Coordonnées du nouvel élément à ajouter en queue de liste.
 * \param[in] cout Distance à parcourir entre l'élément à ajouter et l'élément courant de la liste.
 */
void ajouterEnQueue (Liste* racine, int numeroSommet, Coord monPoint, float cout)
{
    ajouterAvant (racine, numeroSommet, monPoint, cout);
}

/**
 * \fn void supprimerElement (Liste* elementASupprimer)
 * \brief Fonction qui permet de supprimer l'élément courant de la liste
 *
 * \param[in] elementASupprimer Element devant être supprimer de la liste.
 */
void supprimerElement (Liste* elementASupprimer)
{
	// On cache l'élément
    elementASupprimer->prec->suiv = elementASupprimer->suiv;
    elementASupprimer->suiv->prec = elementASupprimer->prec;

    // désalloue la mémoire associé à l'élément
    free(elementASupprimer);
}


/**
 * \fn void ecrireListe (Liste* liste)
 * \brief Fonction qui affiche à l'écran tous les éléments de la liste.
 *
 * \param[in] liste Liste des éléments à afficher à l'écran.
 */
void ecrireListe (Liste* liste)
{
	Liste* elementCourant = liste->suiv;
	float somme = 0;
	for ( ; elementCourant != liste ; elementCourant = elementCourant->suiv)
		{
			printf("S%d (%f) ", elementCourant->numeroSom, elementCourant->cout);
			somme += elementCourant->cout;

		}
	printf("\n\nTotale parcouru : %f\n\n", somme);
}

/**
 * \fn void modifierElement (Liste* liste, float cout)
 * \brief Fonction qui modifie la distance séparant l'élément courant de l'élément suivant.
 * \brief de la liste de l'élement suivant.
 *
 * \param[in] liste Element de la liste dont la distance doit être modifiée.
 * \param[in] cout Nouvelle valeur de la distance séparant l'élément courant de l'élement suivant.
 */
void modifierElement (Liste* liste, float cout) { liste->cout = cout;}

