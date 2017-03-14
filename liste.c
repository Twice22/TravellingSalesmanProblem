/**
 * \file liste.c
 * \brief Liste doublement cha�n�es
 * \author Victor.B
 * \version 1.1
 * \date 9 mai 2013
 *
 * Liste doublement cha�n�es pour le stockage des sommets du graphe
 * par les diff�rentes heurisitiques utilis�es.
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
 * \brief Fonction de cr�ation d'une liste doublement cha�n�es vide.
 *
 * \return Liste doublement cha�n�es vide.
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
 * \brief Fonction de vidage d'une liste doublement cha�n�es.
 *
 * \param liste Liste doublement cha�n�e � vider.
 */
// On vide la liste
void viderListe (Liste* liste)
{
    Liste *it, *next;

    for ( it = liste->suiv; it != liste; it = next )
    {
        next = it->suiv;  // on enregistre le pointeur sur l'�l�ment suivant avant de supprimer l'�l�ment courant
        free(it);         // on supprime l'�l�ment courant
    }
}

/**
 * \fn void supprimerListe (Liste** maListe)
 * \brief Fonction de suppression d'une liste doublement cha�n�e
 *
 * \param maListe Liste doublement cha�n�e � supprimer
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
 * \brief Fonction qui permet d'ajouter un �l�ment � la liste avant l'�l�ment courant de ma liste.
 *
 * \param[in] monElement El�ment courant de la liste.
 * \param[in] numeroSommet Numero du nouvel �l�ment � ajouter � la liste.
 * \param[in] monPoint Coordonn�es du nouvel �l�ment � ajouter � la liste.
 * \param[in] cout Distance � parcourir entre le nouvel �l�ment � ajouter et l'�lement courant de la liste.
 */
//Ajouter un �lement nouvel_element appel� nomSommet avant monElement de ma liste
void ajouterAvant (Liste* monElement, int numeroSommet, Coord monPoint, float cout)
{
    Liste* nouvelElement = (Liste *) malloc ( sizeof *nouvelElement );
    if ( nouvelElement != NULL )
    {
		// on affecte les informations au nouvel �l�ment.
        nouvelElement->numeroSom = numeroSommet;
		nouvelElement->point = monPoint;
		nouvelElement->cout = cout;

        // on d�finit les pointeurs du nouvel �l�ment
        nouvelElement->prec = monElement->prec;
        nouvelElement->suiv = monElement;

        // on modifie les �l�ments de la liste
        monElement->prec->suiv = nouvelElement;
        monElement->prec = nouvelElement;

    }
}

/**
 * \fn void ajouterApres (Liste* monElement, int numeroSommet, Coord monPoint, float cout)
 * \brief Fonction qui permet d'ajouter un �l�ment � la liste apr�s l'�l�ment courant de ma liste.
 *
 * \param[in] monElement El�ment courant de la liste.
 * \param[in] numeroSommet Numero du nouvel �l�ment � ajouter � la liste.
 * \param[in] monPoint Coordonn�es du nouvel �l�ment � ajouter � la liste.
 * \param[in] cout Distance � parcourir entre l'�l�ment courant de la lite et le nouvel �l�ment � ajouter.
 */
//Ajouter un �lement nouvel_element appel� nomSommet apr�s monElement de ma liste
void ajouterApres (Liste* monElement, int numeroSommet, Coord monPoint, float cout)
{
    Liste* nouvelElement = (Liste *) malloc ( sizeof *nouvelElement );
    if ( nouvelElement != NULL )
    {
		// on affecte les informations au nouvel �l�ment.
        nouvelElement->numeroSom = numeroSommet;
		nouvelElement->point = monPoint;
		nouvelElement->cout = cout;

        // on d�finit les pointeurs du nouvel �l�ment
        nouvelElement->prec = monElement;
        nouvelElement->suiv = monElement->suiv;

        // on modifie les �l�ments de la liste
        monElement->suiv->prec = nouvelElement;
        monElement->suiv = nouvelElement;

    }
}

/**
 * \fn void ajouterEnTete (Liste* racine, int numeroSommet, Coord monPoint, float cout)
 * \brief Fonction qui permet d'ajouter un �l�ment en t�te de la liste.
 *
 * \param[in] racine Premier �l�ment de la liste.
 * \param[in] numeroSommet numero du nouvel �l�ment � ajouter en t�te de liste.
 * \param[in] monPoint Coordonn�es du nouvel �l�ment � ajouter en t�te de liste.
 * \param[in] cout Distance � parcourir entre l'�l�ment � ajouter et l'�l�ment courant de la liste.
 */
void ajouterEnTete (Liste* racine, int numeroSommet, Coord monPoint, float cout)
{
    ajouterApres (racine, numeroSommet, monPoint, cout);
}

/**
 * \fn void ajouterEnQueue (Liste* racine, int numeroSommet, Coord monPoint, float cout)
 * \brief Fonction qui permet d'ajouter un �l�ment en queue de la liste.
 *
 * \param[in] racine Premier �l�ment de la liste.
 * \param[in] numeroSommet numero du nouvel �l�ment � ajouter en queue de liste.
 * \param[in] monPoint Coordonn�es du nouvel �l�ment � ajouter en queue de liste.
 * \param[in] cout Distance � parcourir entre l'�l�ment � ajouter et l'�l�ment courant de la liste.
 */
void ajouterEnQueue (Liste* racine, int numeroSommet, Coord monPoint, float cout)
{
    ajouterAvant (racine, numeroSommet, monPoint, cout);
}

/**
 * \fn void supprimerElement (Liste* elementASupprimer)
 * \brief Fonction qui permet de supprimer l'�l�ment courant de la liste
 *
 * \param[in] elementASupprimer Element devant �tre supprimer de la liste.
 */
void supprimerElement (Liste* elementASupprimer)
{
	// On cache l'�l�ment
    elementASupprimer->prec->suiv = elementASupprimer->suiv;
    elementASupprimer->suiv->prec = elementASupprimer->prec;

    // d�salloue la m�moire associ� � l'�l�ment
    free(elementASupprimer);
}


/**
 * \fn void ecrireListe (Liste* liste)
 * \brief Fonction qui affiche � l'�cran tous les �l�ments de la liste.
 *
 * \param[in] liste Liste des �l�ments � afficher � l'�cran.
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
 * \brief Fonction qui modifie la distance s�parant l'�l�ment courant de l'�l�ment suivant.
 * \brief de la liste de l'�lement suivant.
 *
 * \param[in] liste Element de la liste dont la distance doit �tre modifi�e.
 * \param[in] cout Nouvelle valeur de la distance s�parant l'�l�ment courant de l'�lement suivant.
 */
void modifierElement (Liste* liste, float cout) { liste->cout = cout;}

