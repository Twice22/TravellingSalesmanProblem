/**
 * \file testsUnitaires.c
 * \brief Menu de Tests de toutes les fonctions.
 * \author Victor.B
 * \version 1.0
 * \date 15 avril 2012
 *
 * Tests en mode console
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "testsUnitaires.h"


/***********************************************************************
**			             MENU DES TESTS UNITAIRES     	    		  **
************************************************************************/

/**
 * \fn int testsMenu (void)
 * \brief Fonction affichant les options pour tester les fonctions.
 *
 * \return le numéro de l'option choisi.
 */
int testsMenu (void)
{
    int choix;
    printf ("\n\n##################################\n");
    printf ("#\t  MENU DES TESTS  \t#\n");
    printf ("##################################\n\n\n");

    printf("0. QUITTER LE PROGRAMME\n");
    printf("I. LISTES SIMPLEMENT CHAINEES\n");
    printf("II. LISTES DOUBLEMENT CHAINEES\n");
    printf("III. FONCTIONS DE MANIPULATION DES GRAPHES\n");
    //printf("IV. TESTER LES HEURISTIQUES\n");
    //printf("V. FONCTIONS ANNEXES\n");		//viderCache par exemple

    printf("\n");

    printf("Votre choix ?\t");
    scanf("%d", &choix);
    avoidBuffer();
    printf("\n");

    return choix;

}



/**
 * \fn int afficheTests (void)
 * \brief Fonction principale appelant les fonctions d'affichages
          Des différentes options choisies
 *
 * \return le programme s'est éxécuté correctement (0).
 */
int afficheTests (void)
{
    Booleen quit = FAUX;

    while (!quit)
    {
        switch (testsMenu())
        {
            case 0:
                quit = VRAI;
                break;

            case 1:
                testsListeSimple ();
                break;

            case 2:
                testsListeDouble();
                break;

            case 3:
                testsGraphe ();
                break;

            /*case 4:

                break;

            case 5:

                break; */


            default:
                printf("\n Merci de rentrez un nombre entre 1 et 5 !\n\n");
                break;
        }

        if (!quit)
        {
            printf("\n\nAppuyer sur une touche pour continuer\n");
            getchar();
        }
    }

    return 0;
}


/**
 * \fn int testsListeSimple (void)
 * \brief Fonction de tests des listes simples
 *
 * \return la fonction s'est éxécutée correctement (0).
 */
int testsListeSimple (void)
{
    Booleen quit = FAUX;
    ListeSimple liste;

    while (!quit)
    {
        int choix;

        printf ("\n\n##################################\n");
        printf ("#\t  LISTES SIMPLES  \t#\n");
        printf ("##################################\n\n\n");

        printf("0. Quittez le programme\n");
        printf("1. Creer une liste vide\n");
        printf("2. La liste creee est-elle vide ?\n");
        printf("3. Ajouter en queue de liste un element\n");
        printf("4. Enlever un element de la liste\n");
        printf("5. Afficher la liste courante\n");
        printf("6. Supprimer la liste courante\n");

        printf("\n");

        printf("Votre choix ?\t");
        scanf("%d", &choix);
        avoidBuffer();
        printf("\n");


        switch (choix)
        {
            case 0:
                quit = VRAI;
                break;

            case 1:
                {
                    liste = nouvelleListe ();
                    if (liste == NULL)
                        printf("La liste creee est bien vide. Pointeur sur NULL\n");
                    else
                        fprintf(stderr, "La liste n est pas vide dude !\n");
                }
                break;

            case 2:
                {
                    if (liste == NULL && estListeVide (liste))
                        printf("La liste creee est bien vide. Pointeur sur NULL\n");
                    else
                        fprintf(stderr, "La liste n est pas vide dude !\n");

                }
                break;

            case 3:
                {
                    int num;
                    Coord point;
                    printf("Quel numero ajouter en queue de liste ?\n");
                    scanf("%d", &num); avoidBuffer();
                    printf("Abscisse du point à ajouter :\t");
                    scanf("%d", &point.x); avoidBuffer();
                    printf("Ordonne du point à ajouter :\t");
                    scanf("%d", &point.y); avoidBuffer();

                    if (estListeVide (liste))
                    {
                        printf("La liste est vide...\n");
                        liste = enlister (liste, num, point);
                        printf("\n... L element vient d etre ajoute.");
                        printf(" Affichage de la liste : \n");
                        parcourirListe (liste);
                    }
                    else
                    {
                        printf("La liste contient deja des elements.\n");
                        printf("Verifiez que l elt ajoute est place en queue de liste.\n");
                        liste = enlister (liste, num, point);
                        printf(" Affichage de la liste : \n");
                        parcourirListe (liste);

                    }

                }
                break;

            case 4:
                {
                    int num;
                    Coord point;
                    parcourirListe (liste);
                    printf("Quel numero supprimer de la liste ?\n");
                    scanf("%d", &num); avoidBuffer();

                    liste = delister (liste, num);
                    printf("Verification. l element a t il ete enleve ?\n");
                    parcourirListe (liste);

                }
                break;

            case 5:
                {
                    printf("Rappelez vous des elements que vous avez ajouter\n");
                    printf("a la liste et comparez avec ceux qui s affichent maintenant :\n");
                    parcourirListe (liste);

                }
                break;

            case 6:
                {
                    printf("Suppresion de la liste courante\n");
                    liste = viderListeSimple (liste);
                    printf("Affichage des elts de la liste. ");
                    printf("Si aucun element la liste a ete supprime\n");
                    parcourirListe (liste);

                }
                break;

            default:
                printf("\n Merci de rentrez un nombre entre 0 et 6 !\n\n");
                break;
        }

        if (!quit)
        {
            printf("\n\nAppuyer sur une touche pour continuer\n");
            getchar();
        }
    }

    return 0;

}


/**
 * \fn int testsListeDouble (void)
 * \brief Fonction de tests des listes doubles
 *
 * \return la fonction s'est éxécutée correctement (0).
 */
int testsListeDouble (void)
{
    Booleen quit = FAUX;
    Liste* liste;

    while (!quit)
    {
        int choix;

        printf ("\n\n##################################\n");
        printf ("#\t  LISTES DOUBLES  \t#\n");
        printf ("##################################\n\n\n");

        printf("0. Quittez le programme\n");
        printf("1. Creer une liste vide\n");
        printf("2. Supprimer la liste\n");
        printf("3. Ajouter un element en tete de liste\n");
        printf("4. Ajouter un element en queue de liste\n");
        printf("5. Supprimer un element de la liste\n");
        printf("6. Afficher les elements de la liste\n");
        printf("7. Modifier le cout de l element courant de la liste\n");

        printf("\n");

        printf("Votre choix ?\t");
        scanf("%d", &choix);
        avoidBuffer();
        printf("\n");


        switch (choix)
        {
            case 0:
                quit = VRAI;
                break;

            case 1:
                {
                    liste = creerListe ();
                    if (liste->prec == liste && liste->suiv == liste)
                        printf("La liste creee est bien vide. Pointeur sur NULL\n");
                    else
                        fprintf(stderr, "La liste n est pas vide dude !\n");
                }
                break;

            case 2: //Si supprimerListe fonctionne alors viderListe fonctionne
                {
                    if (liste->prec != liste && liste->suiv != liste)
                    {
                        printf("La liste n est pas vide.\n");
                        printf("Suppression de la liste...\n");
                        supprimerListe (liste);
                        if (liste == NULL)
                            printf("La liste a ete videe.\n");
                        else
                            fprintf(stderr, "What the fuck, the list isn't empty bro'!\n");

                    }
                    else
                        fprintf(stderr, "La liste est deja vide dude !\n");

                }
                break;

            case 3: //Si ajouterEnTete fonctionne alors forcement AjouterApres fonctionne
                {
                    int num;
                    float cout;
                    Coord point;
                    printf("Quel numero ajouter en queue de liste ?\n");
                    scanf("%d", &num); avoidBuffer();
                    printf("Abscisse du point à ajouter :\t");
                    scanf("%d", &point.x); avoidBuffer();
                    printf("Ordonne du point à ajouter :\t");
                    scanf("%d", &point.y); avoidBuffer();
                    printf("distance de l'element courant a l'element suivant:\t");
                    scanf("%f", &cout); avoidBuffer();

                    if (liste->prec != liste && liste->suiv != liste)
                    {
                        printf("La liste est vide...\n");
                        ajouterEnTete (liste, num, point, cout);
                        printf("\n... L element vient d etre ajoute.");
                        printf(" Affichage de la liste : \n");
                        ecrireListe (liste);
                    }
                    else
                    {
                        printf("La liste contient deja des elements.\n");
                        printf("Verifiez que l elt ajoute est place en tete de liste.\n");
                        ajouterEnTete (liste, num, point, cout);
                        printf(" Affichage de la liste : \n");
                        ecrireListe (liste);

                    }

                }
                break;

            case 4: //Si ajouterEnQueue fonctionne alors forcement AjouterAvant fonctionne
                {
                    int num;
                    float cout;
                    Coord point;
                    printf("Quel numero ajouter en queue de liste ?\n");
                    scanf("%d", &num); avoidBuffer();
                    printf("Abscisse du point à ajouter :\t");
                    scanf("%d", &point.x); avoidBuffer();
                    printf("Ordonne du point à ajouter :\t");
                    scanf("%d", &point.y); avoidBuffer();
                    printf("distance de l'element courant a l'element suivant:\t");
                    scanf("%f", &cout); avoidBuffer();

                    if (liste->prec != liste && liste->suiv != liste)
                    {
                        printf("La liste est vide...\n");
                        ajouterEnQueue (liste, num, point, cout);
                        printf("\n... L element vient d etre ajoute.");
                        printf(" Affichage de la liste : \n");
                        ecrireListe (liste);
                    }
                    else
                    {
                        printf("La liste contient deja des elements.\n");
                        printf("Verifiez que l elt ajoute est place en queue de liste.\n");
                        ajouterEnQueue (liste, num, point, cout);
                        printf(" Affichage de la liste : \n");
                        ecrireListe (liste);

                    }

                }
                break;

            case 5:
                {
                    int num;
                    Coord point;
                    Liste* copie = liste->suiv;
                    ecrireListe (liste);
                    printf("Quel numero supprimer de la liste ?\n");
                    scanf("%d", &num); avoidBuffer();

                    while (copie->numeroSom != num && copie->suiv != liste->suiv)
                        copie = copie->suiv;

                    if (copie->suiv != liste->suiv)
                        {
                            supprimerElement (copie);
                            printf("L element a t il ete supprime ?\n");
                            ecrireListe (liste);
                        }
                    else
                        printf("cet element n est pas present dans la liste\n");

                }
                break;

            case 6:
                {
                    printf("Rappelez vous des elements que vous avez ajouter\n");
                    printf("a la liste et comparez avec ceux qui s affichent maintenant :\n");
                    ecrireListe (liste);

                }
                break;

            case 7:
                {
                    int num;
                    float cout;
                    Liste* copie = liste->suiv;
                    printf("Modification de la distance de l element\n");
                    printf("De quel numero souhaitez vous modifier l'element ?\n");
                    scanf("%d", &num); avoidBuffer();
                    printf("distance de l'element courant a l'element suivant:\t");
                    scanf("%f", &cout); avoidBuffer();

                    while (copie->numeroSom != num && copie->suiv != liste->suiv)
                        copie = copie->suiv;

                    if (copie->suiv != liste->suiv)
                        {
                            modifierElement (copie, cout);
                            printf("Affichage des elts de la liste. ");
                            printf("Regardez si la distance a ete modifiee\n");
                            ecrireListe (liste);
                        }
                    else
                        fprintf(stderr,"Ben faut entrer un numero existant ducon !\n");

                }
                break;

            default:
                printf("\n Merci de rentrez un nombre entre 0 et 7 !\n\n");
                break;
        }

        if (!quit)
        {
            printf("\n\nAppuyer sur une touche pour continuer\n");
            getchar();
        }
    }

    return 0;

}

/**
 * \fn int testsGraphe (void)
 * \brief Fonction de tests des fonctions de manipulation des graphes
 *
 * \return la fonction s'est éxécutée correctement (0).
 */
int testsGraphe (void)
{
    Booleen quit = FAUX;
    Graphe* graphe;

    while (!quit)
    {
        int choix;

        printf ("\n\n##################################\n");
        printf ("#\t  TESTS DES GRAPHES  \t#\n");
        printf ("##################################\n\n\n");

        printf("0. Quittez le programme\n");
        printf("1. Creer un graphe de n sommets\n");
        printf("2. Supprimer le graphe courant\n");
        printf("3. Retourner le numéro du sommets si présent dans le graphe\n");
        printf("4. Ajouter un sommet au graphe courant\n");
        printf("5. Ajouter un arc au graphe courant\n\n");

        printf("6. Distance entre les points A et B du plan\n");
        printf("7. Echanger deux points A et B du plan\n");
        printf("8. Calcule du rayon adéquate des disques représentant les sommets\n");
        printf("9. Creer un graphe de n sommets aléatoirement\n\n");

        printf("10. Lire un fichier graphe\n");
        printf("11. Ecrire a l'ecran les infos du graphe\n");
        printf("12. Sauvegarder le graphe dans un fichier texte\n");

        printf("\n");

        printf("Votre choix ?\t");
        scanf("%d", &choix);
        avoidBuffer();
        printf("\n");


        switch (choix)
        {
            case 0:
                quit = VRAI;
                break;

            case 1:
                {
                    int num = 0;
                    printf("Combien de sommets voulez-vous dans le graphe ?\t");
                    scanf("%d", &num); avoidBuffer();
                    graphe = creerGraphe (num);
                    printf("Affichage du graphe initialise :\n\n");
                    ecrireGraphe (graphe);
                }
                break;

            case 2:
                {
                    printf("Suppresion du graphe courant...\n");
                    if (graphe == NULL)
                        printf("Le graphe a bien ete detruit bro' !\n");
                    else
                        fprintf(stderr, "Erreur detectee : Le graphe n'a pas ete supprime");
                }
                break;

			case 3:
                {
                    int num;
                    printf("Pensez a creer un graphe aleatoirement avant d appeler cette fonction\n");
                    printf("Pour cela choisissez l'option 9 lors de l'apparition du menu.\n");
                    printf("Si vous rentrez un numero de sommet plus petit que le nombre\n");
                    printf("de sommets dans le graphe alors il va retourner ce nombre. Sinon (-1)\n");
                    printf("Rentrez un numero de sommets present ou non dans le graphe :\t");
                    scanf("%d", &num); avoidBuffer();
                    printf("numero = %d. Si (-1) pas dans le graphe !", rang (graphe, num));
                }
                break;

            case 4:
                {
                    int numSom = 0;
                    Coord point;
                    printf("Pour tester cette fonction vous devez seulement avoir cree un graphe vide\n");
                    printf("Pour cela choisissez l'option 1 dans le menu\n");
                    printf("Ajout d'un sommet au graphe. (ajout d'un sommet a un liste)\n");

                    printf("Quel numero de sommet ajouter au graphe ?\t");
                    scanf("%d", &numSom); avoidBuffer();
                    printf("Abscisse du point à ajouter :\t");
                    scanf("%d", &point.x); avoidBuffer();
                    printf("Ordonne du point à ajouter :\t");
                    scanf("%d", &point.y); avoidBuffer();

                    ajouterUnSommet (graphe, numSom, point.x, point.y);
                    parcourirListe (graphe->sommet);

                }
                break;

            case 5:
                {
                    int numSomD = 0, numSomA = 0, nbSom = 0;
                    float cout;
                    printf("Pour tester cette fonction vous devez seulement avoir cree un graphe vide\n");
                    printf("Pour cela choisissez l'option 1 dans le menu\n");
                    printf("Ajout d'un arc au graphe. (ajout d'une distance a la matrice des distances)\n");

                    printf("Quel est le num du sommet de depart ?\t");
                    scanf("%d", &numSomD); avoidBuffer();
                    printf("Quel est le num du sommet d'arrivee ?\t");
                    scanf("%d", &numSomA); avoidBuffer();
                    printf("Quel est la distance entre ces deux sommets ?\t");
                    scanf("f", &cout); avoidBuffer();

                    printf("Nombre de sommets dans le graphe (Entrez le bon nombre !) :");
                    scanf("%d", &nbSom); avoidBuffer();

                    ajouterUnArc (graphe, numSomD, numSomA, cout);

                    // affichage de la matrice changée
                    int i, j;
                    for (i = 0 ; i < nbSom ; i++)
                    {
                        for (j = 0 ; j < nbSom ; j++)
                        {
                            printf("%f  ", graphe->valeur[i][j]);
                        }
                        printf("\n");
                    }

                }
                break;

            case 6:
                {
                    Coord pointA;
                    Coord pointB;
                    printf("Abscisse du point A :\t");
                    scanf("%d", &pointA.x); avoidBuffer();
                    printf("Ordonne du point A :\t");
                    scanf("%d", &pointA.y); avoidBuffer();

                    printf("Abscisse du point B :\t");
                    scanf("%d", &pointB.x); avoidBuffer();
                    printf("Ordonne du point B :\t");
                    scanf("%d", &pointB.y); avoidBuffer();

                    printf("La distance est de %f\n", distance(pointA, pointB));
                    printf("A vous de verifier sur une feuille !\n");

                }
                break;

            case 7:
                {
                    Coord pointA;
                    Coord pointB;
                    printf("Abscisse du point A :\t");
                    scanf("%d", &pointA.x); avoidBuffer();
                    printf("Ordonne du point A :\t");
                    scanf("%d", &pointA.y); avoidBuffer();

                    printf("Abscisse du point B :\t");
                    scanf("%d", &pointB.x); avoidBuffer();
                    printf("Ordonne du point B :\t");
                    scanf("%d", &pointB.y); avoidBuffer();

                    printf("A est en [%d, %d] et B en [%d, %d]\n", pointA.x, pointA.y, pointB.x, pointB.y);
                    echange(&pointA, &pointB);
                    printf("A est en [%d, %d] et B en [%d, %d]\n", pointA.x, pointA.y, pointB.x, pointB.y);
                    printf("Est-ce que les coordonnees ont ete changees ?\n");

                }
                break;

            case 8:
                {
                    int largeur, hauteur, nbPoints, rayon = 0;

                    printf("Largeur de la fenetre ?\t");
                    scanf("%d", &largeur); avoidBuffer();
                    printf("Hauteur de la fenetre ?\t");
                    scanf("%d", &hauteur); avoidBuffer();
                    printf("Nombre de sommets dans la fenetre ?\t");
                    scanf("%d", &nbPoints); avoidBuffer();

                    pointOuDisque(largeur, hauteur, nbPoints, &rayon);
                    printf("rayon adequate = %d\n", rayon);
                    printf(" 2*pi*rayon^2*nbPoints = %f < %d = largeur*hauteur ?\n", 2*3.14*rayon*rayon*nbPoints, largeur*hauteur);
                    printf("Le coeff 2 dans la verif vient de la consideration du plus mauvais cas !\n");

                }
                break;

            case 9:
                {
                    printf("Vous devez utiliser cette fonction sans avoir appele d'autres fonctions avant !\n");
                    int largeur, hauteur, nbPoints, rayon = 0;

                    printf("Largeur de la fenetre ?\t");
                    scanf("%d", &largeur); avoidBuffer();
                    printf("Hauteur de la fenetre ?\t");
                    scanf("%d", &hauteur); avoidBuffer();

                    graphe = completerGraphe(largeur, hauteur, &rayon, graphe);

                    printf("Affichage des infos du graphe ainsi cree\n");
                    ecrireGraphe (graphe);
                }
                break;

           /* case 10:
                {
					fonctions modifiée car pour l'éxécuter il fallait connaitre le
					nombre de sommets à l'intérieur du fichier et cette information
					n'était pas présentes dans le fichier directement...

                }
                break; */

            case 11:
                {
                    printf("Fonctions deja utilisee lors du choix 9...\n");
                    printf("Pour l'utilisez correctement faites le choix 9 puis 11...\n");
                    ecrireGraphe (graphe);

                }
                break;

            case 12:
                {
                    printf("Pour l'utilisez correctement faites le choix 9 puis 12...\n");
                    printf("Verifiez alors que le fichier texte enregistre contient bien les infos affichees en console !\n");
                    sauvegarderGraphe(graphe);
                }
                break;

            default:
                printf("\n Merci de rentrez un nombre entre 0 et 12 !\n\n");
                break;
        }

        if (!quit)
        {
            printf("\n\nAppuyer sur une touche pour continuer\n");
            getchar();
        }
    }

    return 0;

}
