/**
 * \file listeSimple.c
 * \brief Liste simplement cha�n�e
 * \author Victor.B
 * \version 1.1
 * \date 9 mai 2013
 *
 * Liste simplement ch�in�e utilis� pour stocker les sommets
 * du graphe non encore ajouter � la tourn�e par les heuristiques
 */

#include <stdlib.h>
#include <stdio.h>

#include "listeSimple.h"


/***********************************************************************
**			  FONCTIONS DE MANIPULATION DE LA LISTE SIMPLE 			  **
************************************************************************/

/**
 * \fn ListeSimple nouvelleListe (void)
 * \brief Fonction qui cr�� une liste simplement cha�n�e vide.
 *
 * \return Liste simplement cha�n�e vide.
 */
ListeSimple nouvelleListe (void)
{
  return NULL;
}

/**
 * \fn Booleen estListeVide (ListeSimple liste)
 * \brief Fonction indiquant si la liste en param�tre est vide ou non.
 *
 * \param liste Liste dont il faut dire si elle est vide ou non.
 * \return bool�en valant VRAI (1) si la liste est vide et FAUX (0) sinon.
 */
Booleen estListeVide (ListeSimple liste)
{
  return ( liste == NULL );
}

/**
 * \fn ListeSimple enlister (ListeSimple liste, int v, Coord monPoint)
 * \brief Fonction qui ins�re un nouvel �l�ment dans la liste.
 *
 * \param[in] liste Liste dans laquelle ins�rer le nouvel �l�ment.
 * \param[in] v Numero de l'�lement � ins�rer dans la liste.
 * \param[in] monPoint Coordonn�e de l'�l�ment � ins�rer � la liste.
 * \return la liste incr�menter du nouvel �l�ment.
 */
ListeSimple enlister (ListeSimple liste, int v, Coord monPoint)
{

    ListeSimple ptrNouvelElement, ptrCourant, ptrPred;

    if (estListeVide(liste))
        {
            // Affectation des infos au nouvel �lement et return liste
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

    // Affectation des informations au nouvel �lement
    ptrNouvelElement = malloc (sizeof(Element));
    ptrNouvelElement->numero = v;
    ptrNouvelElement->point = monPoint;

    // On r�alise le lien
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
 * \brief Fonction qui suppprime un �l�ment de la liste rep�r� par son num�ro
 *
 * \param[in] liste Liste de laquelle supprimer l'�l�ment.
 * \param[in] v Numero de l'�lement de la liste � supprimer.
 * \return la liste d�cr�menter de l'�l�ment � supprimer.
 */
// pas besoin de connnaitre les coord car li� au numero de sommet.
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
            // on libere la memoire allou�e � l'elt
            free (ptrCourant);
            }
        }

    return liste;
}

/**
 * \fn void parcourirListe (ListeSimple liste)
 * \brief Fonction qui affiche � l'�cran les �l�ments de la liste.
 *
 * \param[in] liste Liste des �l�ments � afficher � l'�cran.
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
 * \param[in] liste Liste � vider
 * \return La liste vid�e.
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
