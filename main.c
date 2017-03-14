/**
 * \file main.c
 * \brief Menu en mode console
 * \author Victor.B
 * \version 1.0
 * \date 13 avril 2013
 *
 * Utilisation du programme en mode console.
 * Vesion 1.0 du programme (fichier obsolète).
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include "heuristic.h"
#include "constantes.h"
#include "testsUnitaires.h"

/**
 * \fn int menu (void)
 * \brief Fonction affichant les options à choisir pour éxécuter le programme.
 *
 * \return le numéro de l'option choisi.
 */
int menu (void)
{
    int choix;
    printf ("\n\n##################################\n");
    printf ("#\t MENU DES GRAPHES\t#\n");
    printf ("##################################\n\n\n");

    printf("0. Fermer le programme\n\n");

	printf("1. Algorithme du plus proche voisin\n");
    printf("2. Algorithme de l insertion la plus proche\n");
    printf("3. Algorithme de l insertion la moins couteuse\n");
    printf("4. Algorithme de l insertion la plus éloignee\n");
    printf("5. Amelioration locale du parcours par l algorithme 2-opt\n\n");

    printf("6. Creer un graphe a partir d un fichier\n");
    printf("7. Sauvegarder le graphe courant\n");
    printf("8. Reinitialiser tout\n\n");

    printf("9. Tester les fonctions\n");

    printf("\n");

    printf("Votre choix ?\t");
    scanf("%d", &choix);
    avoidBuffer();
    printf("\n");

    return choix;

}

/**
 * \fn int main (int argc, char *argv[])
 * \brief Fonction principale appelant les autres fonctions.
 *
 * \return le programme s'est éxécuté correctement (0).
 */
int main (int argc, char *argv[])
{
    Graphe* graphe;
    Booleen quit = FAUX;
	Liste* listeSommets= NULL;
	int rayon = 0;

    while (!quit)
    {
        switch (menu())
        {
            case 0:     // Fermer le programme
                quit = VRAI;
                break;

            case 1:
                {
                    graphe = completerGraphe(1920, 1080, &rayon, graphe);
                    listeSommets = plusProcheVoisin(graphe);
                    ecrireListe (listeSommets);
                }
                break;

            case 2:
                {
                    graphe = completerGraphe(1920, 1080, &rayon, graphe);
                    listeSommets = plusProcheAddition (graphe);
                    ecrireListe (listeSommets);
                }
                break;

            case 3:
                {
                    graphe = completerGraphe(1920, 1080, &rayon, graphe);
                    listeSommets = insertionMoindreCout (graphe);
                    ecrireListe (listeSommets);
                }
                break;

            case 4:
                {
                    graphe = completerGraphe(1920, 1080, &rayon, graphe);
                    listeSommets = insertionPlusLointaine(graphe);
                    ecrireListe (listeSommets);
                }
                break;

            case 5:
                {
                    deuxOpt (graphe, listeSommets);
                    ecrireListe (listeSommets);
                }
                break;

           /* case 6:
                printf("\nalgorithme pas encore dispo !\n\n");
                break; */

            case 6:     // Création du graphe à partir d'un fichier
            {
                char nomFichier [50];
                printf("Nom du fichier contenant le graphe ?\t");
                scanf("%s", nomFichier); avoidBuffer();
                FILE* fichier = fopen(nomFichier, "r");
                    if (fichier == NULL)
                        {
                            printf("Code de l'erreur : %d\n", errno);
                            perror(nomFichier);
                        }
                    else
                        {
                            graphe = lireGraphe (fichier);           // changer pour compter le nombre de sommets !!
                            fclose(fichier);
                        }
            } break;

			case 7:
                sauvegarderGraphe(graphe);
                break;

            case 8:
                desallouerGraphe (graphe);
                break;

            case 9:
                afficheTests();
                break;


            default:
                printf("\n Merci de rentrez un nombre entre 0 et 8 !\n\n");
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
