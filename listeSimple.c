/**
 * \file listeSimple.c
 * \brief Liste simplement chaînée
 * \author Victor.B
 * \version 1.1
 * \date 9 mai 2013
 *
 * Liste simplement châinée utilisé pour stocker les sommets
 * du graphe non encore ajouter à la tournée par les heuristiques
 */

#include <stdlib.h>
#include <stdio.h>

#include "listeSimple.h"


/***********************************************************************
**			  FONCTIONS DE MANIPULATION DE LA LISTE SIMPLE 			  **
************************************************************************/

/**
 * \fn ListeSimple nouvelleListe (void)
 * \brief Fonction qui créé une liste simplement chaînée vide.
 *
 * \return Liste simplement chaînée vide.
 */
ListeSimple nouvelleListe (void)
{
  return NULL;
}

/**
 * \fn Booleen estListeVide (ListeSimple liste)
 * \brief Fonction indiquant si la liste en paramètre est vide ou non.
 *
 * \param liste Liste dont il faut dire si elle est vide ou non.
 * \return booléen valant VRAI (1) si la liste est vide et FAUX (0) sinon.
 */
Booleen estListeVide (ListeSimple liste)
{
  return ( liste == NULL );
}

/**
 * \fn ListeSimple enlister (ListeSimple liste, int v, Coord monPoint)
 * \brief Fonction qui insére un nouvel élément dans la liste.
 *
 * \param[in] liste Liste dans laquelle insérer le nouvel élément.
 * \param[in] v Numero de l'élement à insérer dans la liste.
 * \param[in] monPoint Coordonnée de l'élément à insérer à la liste.
 * \return la liste incrémenter du nouvel élément.
 */
ListeSimple enlister (ListeSimple liste, int v, Coord monPoint)
{

    ListeSimple ptrNouvelElement, ptrCourant, ptrPred;

    if (estListeVide(liste))
        {
            // Affectation des infos au nouvel élement et return liste
            ptrNouvelElement = malloc ( sizeof(Element) );
            ptrNouvelElement->numero = v;
            ptrNouvelElement->point = monPoint;
            ptrNouvelElement->lien = NULL;
            return ptrNouvelElement;
        }

    // On demarre le parcours
    ptrCourant = liste;
    ptrPred = NULL;

    while ((ptrCourant != NULL ) && ptrCourant->numero != v)
    {
        ptrPred = ptrCourant;
        ptrCourant = ptrCourant->lien;
    }
    if ((ptrCourant != NULL ) && ptrCourant->numero == v)
        {
            // L'entier est deja present
            printf( "L'entier %d est deja present\n\n", v );
            return liste;
        }

    // Affectation des informations au nouvel élement
    ptrNouvelElement = malloc (sizeof(Element));
    ptrNouvelElement->numero = v;
    ptrNouvelElement->point = monPoint;

    // On réalise le lien
    ptrNouvelElement->lien = ptrCourant;

    //On test les effets de bords
    if ( ptrCourant == liste ) // Insertion en debut de liste
        return ptrNouvelElement;
    else
        {
            ptrPred->lien = ptrNouvelElement;
            return liste;
        }
}

/**
 * \fn ListeSimple delister (ListeSimple liste, int v)
 * \brief Fonction qui suppprime un élément de la liste repéré par son numéro
 *
 * \param[in] liste Liste de laquelle supprimer l'élément.
 * \param[in] v Numero de l'élement de la liste à supprimer.
 * \return la liste décrémenter de l'élément à supprimer.
 */
// pas besoin de connnaitre les coord car lié au numero de sommet.
ListeSimple delister (ListeSimple liste, int v)                           
{
    ListeSimple ptrCourant = liste , ptrPred = NULL;

     while ((ptrCourant != NULL ) && (ptrCourant->numero != v))
        {
            ptrPred = ptrCourant;
            ptrCourant = ptrCourant->lien;
        }

    if ((ptrCourant != NULL) && (ptrCourant->numero == v))
        {
        // L'entier est present dans la liste, on le supprime

        if (ptrCourant == liste) // C'est le premier de la liste
            liste = ptrCourant->lien;
        else
            {
            // on saute par dessus l'element a supprimer
            ptrPred->lien = ptrCourant->lien;
            // on libere la memoire allouée à l'elt
            free (ptrCourant);
            }
        }

    return liste;
}

/**
 * \fn void parcourirListe (ListeSimple liste)
 * \brief Fonction qui affiche à l'écran les éléments de la liste.
 *
 * \param[in] liste Liste des éléments à afficher à l'écran.
 */
void parcourirListe (ListeSimple liste)
{

    ListeSimple ptrCourant = liste;
    while ( ptrCourant != NULL )
        {
            printf ( "S%d [%d,%d] ", ptrCourant->numero, ptrCourant->point.x, ptrCourant->point.y);
            ptrCourant = ptrCourant->lien;
        }
    printf ( "\n" );
}

/**
 * \fn ListeSimple viderListeSimple (ListeSimple liste)
 * \brief Fonction qui vide une liste.
 *
 * \param[in] liste Liste à vider
 * \return La liste vidée.
 */
ListeSimple viderListeSimple (ListeSimple liste)
{
    ListeSimple ptrCourant = liste, ptrTmp;

    while (ptrCourant != NULL)
    {
        ptrTmp = ptrCourant;
        ptrCourant = ptrCourant->lien;
        free (ptrTmp);
    }
    return NULL;
}
