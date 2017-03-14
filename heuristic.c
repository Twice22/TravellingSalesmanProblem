/**
 * \file heuristic.c
 * \brief Heuristiques
 * \author Victor.B
 * \version 1.1
 * \date 9 mai 2013
 *
 * Heuristiques pour le problème du voyageur de commerce.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "heuristic.h"


/**
 * \fn Liste* plusProcheVoisin(Graphe* graphe)
 * \brief Fonction de parcours du graphe par l'heuristique du plus proche voisin
 *
 * \param graphe Graphe à parcourir par l'heurisitique. Ne peut être NULL.
 * \return Liste des sommets parcourus en appliquant l'heuristique du plus proche voisin
 */
Liste* plusProcheVoisin(Graphe* graphe)
{
	Liste* listeSommets = creerListe();

	// Copie de la liste des sommets graphe->sommet
	ListeSimple copie = graphe->sommet;
	ListeSimple eltASuppr = graphe->sommet;
	ListeSimple eltCourantListeSimple = graphe->sommet;
	ListeSimple eltSuivant = graphe->sommet;

	// element du début pris aléatoirement dans la liste
    srand(time(NULL));
    int hasard = rand() % graphe->nSom;
    while (eltCourantListeSimple->numero != hasard)
        eltCourantListeSimple = eltCourantListeSimple->lien;

	float coutMinimal;

	while (!estListeVide(copie->lien))
	{
	    coutMinimal = INFINI;
		ListeSimple copie1 = copie;

        while (copie1 != NULL)
		{
			if (eltCourantListeSimple->numero != copie1->numero)
			{
				if (graphe->valeur[eltCourantListeSimple->numero][copie1->numero] < coutMinimal)
				{
				    coutMinimal = graphe->valeur[eltCourantListeSimple->numero][copie1->numero];
				    eltASuppr = eltCourantListeSimple;
				    eltSuivant = copie1;

				}
			}
			copie1 = copie1->lien;

		}
        eltCourantListeSimple = eltSuivant;
            if (eltASuppr == 0)    // si premier elt à ajouter
                {
                    ajouterEnTete (listeSommets, graphe->sommet->numero, graphe->sommet->point, coutMinimal);
                    copie = delister (copie, graphe->sommet->numero);
                }
		    else
                {
                    ajouterEnQueue (listeSommets, eltASuppr->numero, eltASuppr->point, coutMinimal);
                    copie = delister (copie, eltASuppr->numero);
                }
	}
	ajouterEnQueue (listeSommets, eltCourantListeSimple->numero, eltCourantListeSimple->point, graphe->valeur[eltCourantListeSimple->numero][hasard]);
    copie = delister (copie, eltCourantListeSimple->numero);
	return listeSommets;

}

/**
 * \fn Liste* plusProcheAddition (Graphe* graphe)
 * \brief Fonction de parcours du graphe par l'heuristique de l'insertion la plus proche
 *
 * \param graphe Graphe à parcourir par l'heurisitique. Ne peut être NULL.
 * \return Liste des sommets parcourus en appliquant l'heuristique de l'insertion la plus proche
 */
Liste* plusProcheAddition (Graphe* graphe)
{
	Liste* listeSommets = creerListe();

	// Copie de la liste des sommets graphe->sommet
	ListeSimple copie = graphe->sommet;
	ListeSimple copie2 = graphe->sommet;
	ListeSimple secondElt = graphe->sommet;
	ListeSimple eltASuppr = graphe->sommet;
	ListeSimple eltCourantListeSimple = graphe->sommet;

	// element du début pris aléatoirement dans la liste du graphe
    srand(time(NULL));
    int hasard = rand() % (graphe->nSom);
    while (eltCourantListeSimple->numero != hasard)
        eltCourantListeSimple = eltCourantListeSimple->lien;

    ajouterEnTete (listeSommets, eltCourantListeSimple->numero, eltCourantListeSimple->point, 0);
    copie = delister (copie, eltCourantListeSimple->numero);
    copie2 = delister (copie2, eltCourantListeSimple->numero);

	float coutMinimal = INFINI;

	//On cherche l'élément le plus proche du premier élément de la liste.
	while(copie2 != NULL)
    {
        if (graphe->valeur[hasard][copie2->numero] < coutMinimal)
        {
            coutMinimal = graphe->valeur[hasard][copie2->numero];
            secondElt = copie2;
        }
        copie2 = copie2->lien;
    }

    //On ajoute ce 2nd élt à la liste
    ajouterEnQueue (listeSommets, secondElt->numero, secondElt->point, coutMinimal);
    copie = delister (copie, secondElt->numero);

	while (!estListeVide(copie))
	{
	    coutMinimal = INFINI;
		ListeSimple copie1 = copie;

		Liste* vi;      //donne le sommet du tour T le plus proche de vk pour tout k
		Liste* vj;      //elt suivant i
		Liste* sommetCourant = listeSommets->suiv;



        while (sommetCourant->suiv->numeroSom != listeSommets->suiv->numeroSom)
        {
            copie1 = copie;
            while (copie1 != NULL)
            {
                if (graphe->valeur[sommetCourant->numeroSom][copie1->numero] < coutMinimal)
                {
                    coutMinimal = graphe->valeur[sommetCourant->numeroSom][copie1->numero];
                    eltASuppr = copie1;
                    vi = sommetCourant;
                    vj = (sommetCourant->suiv == listeSommets) ? vi->suiv->suiv : vi->suiv;
                }
                copie1 = copie1->lien;
            }
            sommetCourant = sommetCourant->suiv;

        }

        ajouterApres (vi, eltASuppr->numero, eltASuppr->point, graphe->valeur[eltASuppr->numero][vj->numeroSom]);
        modifierElement (vi, coutMinimal);
        copie = delister (copie, eltASuppr->numero);

	}

	return listeSommets;
}

/**
 * \fn Liste* insertionMoindreCout (Graphe* graphe)
 * \brief Fonction de parcours du graphe par l'heuristique de l'insertion la moins coûteuse
 *
 * \param graphe Graphe à parcourir par l'heurisitique. Ne peut être NULL.
 * \return Liste des sommets parcourus en appliquant l'heuristique de l'insertion la moins coûteuse
 */
Liste* insertionMoindreCout (Graphe* graphe)
{
    Liste* listeSommets = creerListe();

    // Copie de la liste des sommets graphe->sommet
    ListeSimple copie = graphe->sommet;
    ListeSimple secondElt = graphe->sommet;
    ListeSimple copie2 = graphe->sommet;
    ListeSimple eltASuppr = graphe->sommet;
    ListeSimple eltCourantListeSimple = graphe->sommet;

	// initialise la liste avec le premier élt du graphe
    srand(time(NULL));
    int hasard = rand() % graphe->nSom;
    while (eltCourantListeSimple->numero != hasard)
        eltCourantListeSimple = eltCourantListeSimple->lien;

    ajouterEnTete (listeSommets, eltCourantListeSimple->numero, eltCourantListeSimple->point, 0);
    copie = delister (copie, eltCourantListeSimple->numero);
    copie2 = delister (copie2, eltCourantListeSimple->numero);

	float coutMinimal = INFINI;

	//On cherche l'élément le plus proche du premier élément de la liste.
	while(copie2 != NULL)
	  {
	    if (graphe->valeur[hasard][copie2->numero] < coutMinimal)
	      {
		coutMinimal = graphe->valeur[hasard][copie2->numero];
		secondElt = copie2;
	      }
	    copie2 = copie2->lien;
	  }

    //On ajoute ce 2nd élt à la liste
    ajouterEnQueue (listeSommets, secondElt->numero, secondElt->point, coutMinimal);
    copie = delister (copie, secondElt->numero);

	while (!estListeVide(copie))
	{
	    coutMinimal = INFINI;
		ListeSimple copie1 = copie;

		Liste* vi;
		Liste* vj;
		Liste* sommetCourant = listeSommets->suiv;
		Liste* sommetSuivant = sommetCourant->suiv;

            //on parcourt une fois les éléments de la liste
            while (sommetCourant->suiv->numeroSom != listeSommets->suiv->numeroSom)
            {
                sommetSuivant = (sommetCourant->suiv == listeSommets) ? sommetCourant->suiv->suiv : sommetCourant->suiv;
                // tant qu'on est pas arrivée au bout de la liste

                copie1 = copie;
                while (copie1 != NULL)
                {
                    if (graphe->valeur[sommetCourant->numeroSom][copie1->numero] +
                        graphe->valeur[copie1->numero][sommetSuivant->numeroSom] -
                        graphe->valeur[sommetCourant->numeroSom][sommetSuivant->numeroSom] < coutMinimal)
                    {
                        coutMinimal =   graphe->valeur[sommetCourant->numeroSom][copie1->numero] +
                                        graphe->valeur[copie1->numero][sommetSuivant->numeroSom] -
                                        graphe->valeur[sommetCourant->numeroSom][sommetSuivant->numeroSom];

                        eltASuppr = copie1;
                        vi = sommetCourant;
                        vj = sommetSuivant;
                    }
                    copie1 = copie1->lien;
                }

            sommetCourant = sommetCourant->suiv;
            }

            ajouterApres (vi, eltASuppr->numero, eltASuppr->point, graphe->valeur[eltASuppr->numero][vj->numeroSom]);
            modifierElement (vi, graphe->valeur[vi->numeroSom][eltASuppr->numero]);
            copie = delister (copie, eltASuppr->numero);

	}

	return listeSommets;
}

/**
 * \fn Liste* insertionPlusLointaine(Graphe* graphe)
 * \brief Fonction de parcours du graphe par l'heuristique de l'insertion la plus éloignée
 *
 * \param graphe Graphe à parcourir par l'heurisitique. Ne peut être NULL.
 * \return Liste des sommets parcourus en appliquant l'heuristique de l'insertion la plus éloignée
 */
Liste* insertionPlusLointaine(Graphe* graphe)
{
    Liste* listeSommets = creerListe();

	// Copie de la liste des sommets graphe->sommet
	ListeSimple copie = graphe->sommet;
	ListeSimple copie1 = graphe->sommet;
	ListeSimple copie2 = graphe->sommet;
	ListeSimple eltASuppr = graphe->sommet;
	ListeSimple eltASupprTemp = graphe->sommet;

	//  Trouver les deux éléments les plus éloignés
	ListeSimple sommetInit = graphe->sommet;
	ListeSimple sommetFinal = graphe->sommet;
	float plusEloigne = 0, plusEloigneTemp = 0;
	while (copie1 != NULL)
    {
        copie2 = copie1->lien;
        while (copie2 != NULL)
        {
            if (graphe->valeur[copie2->numero][copie1->numero] > plusEloigne)
                {
                    plusEloigne = graphe->valeur[copie2->numero][copie1->numero];
                    sommetInit = copie1; sommetFinal = copie2;
                }
            copie2 = copie2->lien;
        }
        copie1 = copie1->lien;
    }

    //initialise la liste avec les deux premiers élts les plus eloignes
    ajouterEnTete (listeSommets, sommetInit->numero, sommetInit->point, plusEloigne);
    copie = delister (copie, sommetInit->numero);

    ajouterEnQueue (listeSommets, sommetFinal->numero, sommetFinal->point, plusEloigne);
    copie = delister (copie, sommetFinal->numero);

    while (!estListeVide(copie))
	{
	    copie1 = copie;
	    plusEloigne = 0;

		Liste* vi;
		Liste* vj;
		Liste* sommetCourant = listeSommets->suiv;
		Liste* sommetSuivant = sommetCourant->suiv;


		//  Recherche du sommet le plus éloigné des sommets du tour
		while (copie1 != NULL)
        {
            sommetCourant = listeSommets->suiv;
            plusEloigneTemp = graphe->valeur[copie1->numero][sommetCourant->numeroSom];

            // tant qu'on a pas parcouru tous les sommets du tour
            while (sommetCourant->suiv->numeroSom != listeSommets->suiv->numeroSom)
            {
                if (graphe->valeur[copie1->numero][sommetCourant->numeroSom] <= plusEloigneTemp)
                {
                    plusEloigneTemp = graphe->valeur[copie1->numero][sommetCourant->numeroSom];
                    eltASupprTemp = copie1;
                }
                sommetCourant = sommetCourant->suiv;
            }
            if (plusEloigneTemp > plusEloigne)
            {
                plusEloigne = plusEloigneTemp;
                eltASuppr = eltASupprTemp;
            }
            copie1 = copie1->lien;
        }

        //  Recherche du segment le plus proche
        sommetCourant = listeSommets->suiv;
        float plusPetiteDistance = INFINI;
        while (sommetCourant->suiv->numeroSom != listeSommets->suiv->numeroSom)
            {
                sommetSuivant = (sommetCourant->suiv == listeSommets) ? sommetCourant->suiv->suiv : sommetCourant->suiv;
                if (graphe->valeur[sommetCourant->numeroSom][eltASuppr->numero] +
                    graphe->valeur[eltASuppr->numero][sommetSuivant->numeroSom] -
                    graphe->valeur[sommetCourant->numeroSom][sommetSuivant->numeroSom] < plusPetiteDistance)
                {
                    plusPetiteDistance = graphe->valeur[sommetCourant->numeroSom][eltASuppr->numero] +
                                         graphe->valeur[eltASuppr->numero][sommetSuivant->numeroSom] -
                                         graphe->valeur[sommetCourant->numeroSom][sommetSuivant->numeroSom];

                    vi = sommetCourant;
                    vj = sommetSuivant;

                }
                sommetCourant = sommetCourant->suiv;
            }
        //  Ajout des élts à la liste listeSommets
        ajouterApres (vi, eltASuppr->numero, eltASuppr->point, graphe->valeur[eltASuppr->numero][vj->numeroSom]);
        modifierElement (vi, graphe->valeur[vi->numeroSom][eltASuppr->numero]);
        copie = delister (copie, eltASuppr->numero);
	}

return listeSommets;

}

/**
 * \fn void deuxOpt (Graphe* graphe, Liste* listeSommets)
 * \brief Fonction d'amélioration du tour par l'algorithme 2-opt.
 *
 * \param[in] graphe Graphe à parcourir. Ne peut être NULL.
 * \param[in] listeSommets Liste du parcours à modifier.
 */
void deuxOpt (Graphe* graphe, Liste* listeSommets)
{
	Liste* copie = listeSommets->suiv;
	Liste *copie1, *copie1Suiv, *copieSuiv, *copieSuivTemp, *copie1Courant, *avantCopie, *copie1Courant2, *copieSuiv2;

	int tempNum;
	Coord tempPoint;

	// tant qu'on a pas fait tout le tour des sommets
	while (copie->suiv->numeroSom != listeSommets->suiv->numeroSom)
	{
		copie1 = (copie->suiv == listeSommets || copie->suiv->suiv == listeSommets) ? copie->suiv->suiv->suiv : copie->suiv->suiv;
		avantCopie = (copie->prec == listeSommets) ? copie->prec->prec : copie->prec;

		while (copie1->numeroSom != avantCopie->numeroSom)
		{
		    copie1Suiv = (copie1->suiv == listeSommets) ? copie1->suiv->suiv : copie1->suiv;
            copieSuiv = (copie->suiv == listeSommets) ? copie->suiv->suiv : copie->suiv;
            copie1Courant = copie1;     //pour ne pas modifier copie1 dans la boucle
            copieSuivTemp = copie1Courant;

            copie1Courant2 = copie1Courant;
            copieSuiv2 = copieSuiv;

		    if (copie->cout + copie1->cout >
					graphe->valeur[copie->numeroSom][copie1->numeroSom] +
					graphe->valeur[copieSuiv->numeroSom][copie1Suiv->numeroSom])
		   {
                //inverse le sens des sommets
		        while (copie1Courant->numeroSom != copieSuiv->numeroSom)
                {
                    tempNum = copieSuiv->numeroSom;
                    tempPoint = copieSuiv->point;

                    copieSuiv->numeroSom = copie1Courant->numeroSom;
                    copieSuiv->point = copie1Courant->point;

                    copie1Courant->numeroSom = tempNum;
                    copie1Courant->point = tempPoint;

                    copieSuiv = (copieSuiv->suiv == listeSommets) ? copieSuiv->suiv->suiv : copieSuiv->suiv;
                    if (copie1Courant->numeroSom != copieSuiv->numeroSom)
                    {
                        if (copie1Courant->prec == listeSommets)
                            copie1Courant = copie1Courant->prec->prec;
                        else
                            copie1Courant = copie1Courant->prec;
                    }

                }

                //Change les valeurs des sommets inversés
                while (copieSuiv2->numeroSom != copie1Courant2->numeroSom)
                {
                    copieSuiv2->cout = (copieSuiv2->suiv == listeSommets) ? graphe->valeur[copieSuiv2->numeroSom][copieSuiv2->suiv->suiv->numeroSom] : graphe->valeur[copieSuiv2->numeroSom][copieSuiv2->suiv->numeroSom];
                    copieSuiv2 = (copieSuiv2->suiv == listeSommets) ? copieSuiv2->suiv->suiv : copieSuiv2->suiv;
                }

                // Change les valeurs des deux sommets qui ont changé de sommet cible
                copie->cout = (copie->suiv == listeSommets) ? graphe->valeur[copie->numeroSom][copie->suiv->suiv->numeroSom] : graphe->valeur[copie->numeroSom][copie->suiv->numeroSom];
                copieSuivTemp->cout = (copieSuivTemp->suiv == listeSommets) ? graphe->valeur[copieSuivTemp->numeroSom][copieSuivTemp->suiv->suiv->numeroSom] : graphe->valeur[copieSuivTemp->numeroSom][copieSuivTemp->suiv->numeroSom];


		   }
			copie1 = (copie1->suiv == listeSommets) ? copie1->suiv->suiv : copie1->suiv;

		}
		copie = copie->suiv;
	}

}
