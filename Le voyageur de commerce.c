/**
 * \file Le voyageur de commerce.c
 * \brief Résoudre le problème du voyageur de 
 * commerce à l'aide d'heuristiques préétablies.
 * \author Victor.B
 * \version 1.1
 * \date 9 mai 2013
 *
 * Interface graphique fait avec GTK+3.6.4
 * utilisant cairo (pour les dessins).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>		//pour passer plusieurs arguments avec des ... dans une fonction.
#include <gtk/gtk.h>
#include <math.h>

#include "heuristic.h"
#include "constantes.h"

#define _PPV  0
#define _PPA  1
#define _IMC  2
#define _IPL  3

typedef struct
{
  GtkWidget *boutonP;
  GtkWidget *nbSommet;
  GtkWidget *distance;
  gint algo;
  gint largeur;
  gint hauteur;
}  mesArguments;

static gboolean onReset (GtkWidget *widget, gpointer data);
static gboolean onDeuxOpt (GtkWidget *widget, gpointer data);
static gboolean onDraw (GtkWidget *widget, cairo_t *cr, gpointer data);
static void activate_radio_action (GtkAction *action, GtkRadioAction *current, gpointer data);
void onValider(GtkWidget *widget, gpointer data);

static void menuAjouterWidget (GtkUIManager *, GtkWidget *, GtkContainer *);


static void menuOuvrir (GtkWidget *pWidget, gpointer donneesUser);
static void menuSauvegarder (GtkWidget *Widget, gpointer donneesUser);
static void menuQuitter (void);

static void menuAide (void);
static void menuAPropos (GtkWidget *pWidget, gpointer donneesUser);

void print_warning (char *format, ...);


/* Variable globale */
/* On fait comme on peu hein... */
Graphe* graphe = NULL;
Liste* listeSommets = NULL;
int rayon = 0;
float somme = 0;
int ouvertFichier = 0; //1 on a ouvert un fichier, 0 rien

/**
 * \fn int main (int argc, char* argv[])
 * \brief Fonction principale créant l'interface graphique
 *  est connectant les différents éléments à d'autres fonctions.
 *
 * \return 0 si tout est OK.
 */
int main (int argc, char* argv[])
{
  GtkWidget* pFenetre = NULL;
  GtkWidget* pBoite = NULL;
  GtkUIManager* puiManager = NULL;
  GtkActionGroup* pActionGroupe = NULL;
  GtkWidget* menubar = NULL;
  GtkWidget* toolbar = NULL;
  
  GError* erreur;

  /* Widget pour sauvegarde icones en GTK_STOCK */
  GtkWidget* image;
  GtkIconFactory* factory;
  GtkIconSource* source;
  GtkIconSet* set;
  GtkStockItem item;
  
  char chemin[256];
  /* Fin des Widget utiles pour les icones */

  /* Grille pour placer mes WidGets */
  GtkWidget* table;
  
  /* Zone de dessin cairo */
  GtkWidget* area;

  /* Widget nb de sommets */
  GtkWidget* frame;

  /* Widget style de sommets */
  GtkWidget* styleSom;
  GtkWidget* boutonD;
  GtkWidget* boxSom;

  /* Widget GO */
  GtkWidget* Go;

  /* Widget 2-opt */
  GtkWidget* deuxOpt;

  /* séparateurs */
  GtkWidget* separateur1;
  GtkWidget* separateur2;
  GtkWidget* separateur3;  

  /* bouton Reset */
  GtkWidget* reset;

  /* affichage de la distance du parcours */
  char distanceBuffer[70];

  /* mesArguments */
  mesArguments mesArgs;

  /* Création du menu */
 static  GtkActionEntry entries[] =
    {
      { "FichierMenuAction",        NULL,              "Fichier",                    NULL,           NULL,           NULL                        },
      { "OuvrirAction",             GTK_STOCK_OPEN,    "_Ouvrir",                    "<control>O",   "Ouvrir",       G_CALLBACK (menuOuvrir)     },
      { "EnregistrerAction",        GTK_STOCK_SAVE_AS,  "Enregistrer sous",          "<control>S",   "Enregistrer",  G_CALLBACK (menuSauvegarder)},
      { "QuitterAction",            GTK_STOCK_QUIT,    "_Quitter",                   "<control>Q",   "Quitter",      G_CALLBACK (menuQuitter)    },
      { "AlgorithmesMenuAction",    NULL,              "Algorithmes",                NULL,           NULL,           NULL                        },
      { "AideMenuAction",           NULL,              "Aide",                       NULL,           NULL,           NULL                        },
      { "AideAction",               GTK_STOCK_HELP,    "Aide",                       "<release>F1",  "Aide",         G_CALLBACK(menuAide)        },
      { "AProposAction",            GTK_STOCK_ABOUT,   "_A propos",                  "<control>A" ,  "A Propos",     G_CALLBACK(menuAPropos)     }
    };

   
 static GtkRadioActionEntry radio_entries[] = 
   {
     { "PlusProcheVoisinAction",       "TSP_PROCHE",            "Plus Proche Voisin",         NULL,          "Plus Proche Voisin",       _PPV },
     { "PlusProcheAdditionAction",     "TSP_ADDITION",          "Plus Proche Addition",       NULL,          "Plus Proche Addition" ,    _PPA },
     { "InsertionMoindreCoutAction",   "TSP_MOINDRE_COUT",      "Insertion Moindre Cout",     NULL,          "Insertion Moindre Cout" ,  _IMC },
     { "InsertionPlusLointaineAction", "TSP_PLUS_LOIN",         "Insertion Plus Lointaine",   NULL,          "Insertion Plus Lointaine", _IPL },
   };


  /* Initialisation de GTK+ */
  gtk_init(&argc, &argv);

  /* Création de la fenetre */
  pFenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(pFenetre), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(pFenetre), "Le Voyageur De Commerce");
  gtk_window_set_default_size(GTK_WINDOW(pFenetre), 800, 600);
  gtk_window_set_resizable (GTK_WINDOW(pFenetre), TRUE);
  gtk_window_iconify (GTK_WINDOW(pFenetre));
  gtk_window_maximize (GTK_WINDOW(pFenetre));
  g_signal_connect(G_OBJECT(pFenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  /* création d'une structure pour les images */
  static struct
  {
     gchar *nomFichier;
     gchar *stockId;
  } stockIcones[] =
      {
	 { "plusProche.png", "TSP_PROCHE" },
	 { "plusAddition.png", "TSP_ADDITION" },
	 { "moindreCout.png", "TSP_MOINDRE_COUT" },
	 { "plusLoin.png", "TSP_PLUS_LOIN" }
      };
  static gint nbrIcones = G_N_ELEMENTS (stockIcones);

  /* chargement des images */
  factory = gtk_icon_factory_new();
  int i;
  for (i = 0 ; i < nbrIcones ; i++)
    {
      set = gtk_icon_set_new();
      source = gtk_icon_source_new();
            
      sprintf(chemin, "%s/", getcwd(chemin, sizeof(chemin)));
      strcat(chemin, stockIcones[i].nomFichier);
      gtk_icon_source_set_filename( source, chemin);
      gtk_icon_set_add_source( set, source );
      gtk_icon_source_free (source);
      gtk_icon_factory_add( factory, stockIcones[i].stockId , set );
      gtk_icon_set_unref (set);
    }
   gtk_icon_factory_add_default ( factory );
   g_object_unref (factory);

   /* Création d'une grille de subdivision de la fenetre */
   table = gtk_grid_new ();
   gtk_grid_set_column_homogeneous(GTK_GRID(table), TRUE);
   gtk_grid_set_row_homogeneous(GTK_GRID(table), TRUE);
   gtk_container_add(GTK_CONTAINER(pFenetre), GTK_WIDGET(table));
   
  /* Creation d'une vBox pour les icônes */
  /* Normalement c'est plutôt un hBox mais comprend pas
	si je fais une hBox le menu est vertical donc... */
  pBoite = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

  /* Creation du menu */
  pActionGroupe = gtk_action_group_new ("menuActionGroupe");
  gtk_action_group_add_actions (pActionGroupe, entries, G_N_ELEMENTS (entries), NULL);
  gtk_action_group_add_radio_actions (pActionGroupe, radio_entries, G_N_ELEMENTS (radio_entries), -1, (GCallback)activate_radio_action, &mesArgs);

  puiManager = gtk_ui_manager_new ();
  gtk_ui_manager_insert_action_group (puiManager, pActionGroupe, 0);
  gtk_ui_manager_add_ui_from_file (puiManager, "menu.xml", NULL);
  g_signal_connect (puiManager, "add_widget", G_CALLBACK (menuAjouterWidget), pBoite);

  erreur = NULL;
  gtk_ui_manager_add_ui_from_file (puiManager, "menu.xml", &erreur);
    
  if (erreur)
    {
        g_message ("La construction du menu a merdé: %s", erreur->message);
        g_error_free (erreur);
    }

  /********************** DEBUT DE L'INTERFACE ********************/

  /* Widget nombre de sommets */
  frame = gtk_frame_new("Nombre de sommets");
  mesArgs.nbSommet = gtk_spin_button_new_with_range(0,5000,1);
  gtk_container_add(GTK_CONTAINER(frame), mesArgs.nbSommet);


  /* Widget style de points */
  styleSom = gtk_frame_new("Style des sommets");

  boxSom = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_container_add(GTK_CONTAINER(styleSom), boxSom);

  mesArgs.boutonP = gtk_radio_button_new_with_label(NULL, "Points");
  gtk_box_pack_start(GTK_BOX(boxSom), mesArgs.boutonP, TRUE, FALSE, 0);
  boutonD = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(mesArgs.boutonP), "Disques");
  gtk_box_pack_start(GTK_BOX(boxSom), boutonD, TRUE, FALSE, 0);

  /* Bouton pour valider */
  Go = gtk_button_new_from_stock(GTK_STOCK_OK);

  /* Séparateur */
  separateur1 =  gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  separateur2 =  gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  separateur3 =  gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

  /* 2-opt bouton */
  deuxOpt = gtk_button_new_with_mnemonic("_2-opt");

  /* reset bouton */
  reset = gtk_button_new_with_mnemonic("_Reset");

  /* DrawingArea */
  area = gtk_drawing_area_new ();

  /* affiche de la distance du parcours */
  sprintf(distanceBuffer, "Distance : %f", somme);
  mesArgs.distance = gtk_label_new(distanceBuffer);

  /* Mis en place des widgets dans la fenetre */
  gtk_grid_attach(GTK_GRID (table), pBoite, 0, 0 , 18 ,1 );
  gtk_grid_attach(GTK_GRID (table), frame, 0, 1 ,3 ,1 );
  gtk_grid_attach(GTK_GRID (table), area, 3, 1, 15, 10); 
  gtk_grid_attach_next_to(GTK_GRID (table), styleSom, frame, GTK_POS_BOTTOM, 3, 1);
  gtk_grid_attach(GTK_GRID (table), separateur1, 0, 3, 3, 1);
  gtk_grid_attach(GTK_GRID (table), Go, 0, 4, 3, 1);
  gtk_grid_attach(GTK_GRID (table), separateur2, 0, 5, 3, 1);
  gtk_grid_attach(GTK_GRID (table), deuxOpt, 0, 6, 3, 1);
  gtk_grid_attach(GTK_GRID (table), separateur3, 0, 7, 3, 1);
  gtk_grid_attach(GTK_GRID (table), reset, 0, 8, 3, 1);
  gtk_grid_attach(GTK_GRID (table), mesArgs.distance, 0, 10, 3, 1);

  /* bordure autour de la DrawingArea */
  g_object_set (frame, "margin-left", 20, NULL);
  g_object_set (styleSom, "margin-left", 20, NULL);
  g_object_set (separateur1, "margin-left", 20, NULL);
  g_object_set (separateur2, "margin-left", 20, NULL);
  g_object_set (separateur3, "margin-left", 20, NULL);
  g_object_set (Go, "margin-left", 20, NULL);
  g_object_set (deuxOpt, "margin-left", 20, NULL);
  g_object_set (reset, "margin-left", 20, NULL);
  g_object_set (area, "margin", 20, NULL);

 
  g_signal_connect (G_OBJECT (area), "draw", G_CALLBACK (onDraw), &mesArgs);

  /************************ FIN DE L'INTERFACE *****************************/

  /********** L'appui sur Valider détermine l'algo
	      choisi et la représentation des sommets ********/
  g_signal_connect(G_OBJECT(Go), "clicked", G_CALLBACK(onValider), &mesArgs);
  g_signal_connect(G_OBJECT(deuxOpt), "clicked", G_CALLBACK(onDeuxOpt), NULL);
  g_signal_connect(G_OBJECT(reset), "clicked", G_CALLBACK(onReset), &mesArgs);


  /* Autorise l'utilisation des raccourcis. */
  gtk_window_add_accel_group (GTK_WINDOW (pFenetre), gtk_ui_manager_get_accel_group (puiManager));

  /* Boucle principale */
  gtk_widget_show_all(pFenetre);
  gtk_main();
  gtk_widget_destroy(pFenetre);

  return EXIT_SUCCESS;
}




/**
 * \fn static gboolean onReset (GtkWidget *widget, gpointer data)
 * \brief Fonction qui réinitialise le graphe à zéro.
 *
 * \param[in] widget Objet relié à l'appelle de cette fonction.
 * \param[in] data Données fournies par l'utilisateur à la fonction.
 * \return TRUE.
 */
static gboolean onReset (GtkWidget *widget, gpointer data)
{
  mesArguments * mesArgs = (mesArguments *) data;
  char nouvelleDistance[70];

  if (listeSommets != NULL)
    {      
      supprimerListe (&listeSommets);
      desallouerGraphe (graphe);
      somme = 0;
      sprintf(nouvelleDistance, "Distance : %f", somme);
      gtk_label_set_text (GTK_LABEL(mesArgs->distance), nouvelleDistance);
    }
  return TRUE;
}

/**
 * \fn static gboolean onDeuxOpt (GtkWidget *widget, gpointer data)
 * \brief Fonction qui applique l'algorithme 2-Opt au parcours.
 *
 * \param[in] widget Objet relié à l'appelle de cette fonction.
 * \param[in] data Données fournies par l'utilisateur à la fonction.
 * \return TRUE.
 */
static gboolean onDeuxOpt (GtkWidget *widget, gpointer data)
{
  if (listeSommets != NULL)
    {      
      deuxOpt (graphe, listeSommets);    
      
    }
  return TRUE;  

}


/**
 * \fn static gboolean onDraw (GtkWidget *widget, cairo_t *cr, gpointer data) 
 * \brief Fonction qui dessine le graphe dans la zone prévue à cet effet.
 *
 * \param[in] widget Objet relié à l'appelle de cette fonction.
 * \param[in] cr Variable permettant de dessiner dans la zone de dessin.
 * \param[in] data Données fournies par l'utilisateur à la fonction.
 * \return FALSE.
 */
static gboolean onDraw (GtkWidget *widget, cairo_t *cr, gpointer data) 
{
  int i = 0;
  char tampon[5];
  char nouvelleDistance[70];
  mesArguments * mesArgs = (mesArguments *) data;
  mesArgs->largeur = gtk_widget_get_allocated_width(widget);
  mesArgs->hauteur = gtk_widget_get_allocated_height(widget);

  cairo_set_source_rgb (cr, 0.0 , 0.0 , 0.0); //fond noir
  cairo_paint (cr);
  cairo_stroke(cr);

  if (listeSommets != NULL)
    {
      cairo_set_source_rgb(cr, 0, 1, 0);
      
      Liste* elementCourant = listeSommets->suiv;
      Liste* elementSuivant = elementCourant->suiv;
      float somme = 0;
      
      if (rayon == 0)    // Si on a choisi l'option Points
	{
	  cairo_set_line_width(cr, 0.5);
	  for ( ; elementCourant != listeSommets ; elementCourant = elementCourant->suiv)
	    {

	      cairo_move_to(cr, elementCourant->point.x, elementCourant->point.y);
	      cairo_line_to(cr, elementSuivant->point.x, elementSuivant->point.y);
	      cairo_stroke(cr);
	      somme += elementCourant->cout;
	      elementSuivant = (elementSuivant->suiv == listeSommets) ? elementSuivant->suiv->suiv : elementSuivant->suiv;
	      /* On pourrait réduire ici le test puisqu'il concerne le dernier élément de la liste mais bon...
			qu'est-ce qu'un O(n) fasse à un O(n²) ? Pas grand chose... même si O(1) c'est mieux... */

	    }
	}
      else // représentation sous forme de disques
	{
	  cairo_text_extents_t extents;
	  cairo_set_line_width(cr, rayon/4);
	  for ( ; elementCourant != listeSommets ; elementCourant = elementCourant->suiv)
	    {
	      cairo_set_source_rgb(cr, 0, 1, 0);
	      cairo_move_to(cr, elementCourant->point.x, elementCourant->point.y);
	      cairo_line_to(cr, elementSuivant->point.x, elementSuivant->point.y);
	      cairo_stroke(cr);
	      
	      cairo_set_source_rgb(cr, 1, 0, 0);
	      cairo_arc(cr, elementCourant->point.x, elementCourant->point.y, rayon, 0, 2 * M_PI);
	      cairo_fill(cr);
	      
	      cairo_set_source_rgb(cr, 0, 0, 0);
	      cairo_set_font_size(cr, rayon);
	      sprintf(tampon, "%i", i);
	      
	      cairo_text_extents(cr, tampon, &extents);
	      cairo_move_to(cr, elementCourant->point.x - extents.width/2, elementCourant->point.y + extents.height/2);
	      cairo_show_text(cr, tampon);
	      i++;

	      somme += elementCourant->cout;
	      elementSuivant = (elementSuivant->suiv == listeSommets) ? elementSuivant->suiv->suiv : elementSuivant->suiv;
	      // Idem... On peut éviter ce test et réduire la compléxité mais bon...

	    }
	}
      sprintf(nouvelleDistance, "Distance : %f", somme);
      gtk_label_set_text (GTK_LABEL(mesArgs->distance), nouvelleDistance);
    }
  
  return FALSE;
}

/**
 * \fn static void menuAjouterWidget (GtkUIManager * puiManager, GtkWidget * pWidget, GtkContainer * pBoite)
 * \brief Fonction qui ajoute les Widgets au menu et à la barre d'outils.
 *
 * \param[in] puiManager La descriptions des widgets à ajouter.
 * \param[in] pWidget Les différents widgets à ajouter.
 * \param[in] pBoite Le "récipient" qui va recevoir les widgets.
 */
static void menuAjouterWidget (GtkUIManager * puiManager, GtkWidget * pWidget, GtkContainer * pBoite)
{
   gtk_box_pack_start(GTK_BOX (pBoite), pWidget, FALSE, FALSE, 0);
   gtk_widget_show (pWidget);
   return;
}

/***************************************************************
**			     	OUVRIR UN FICHIER GRAPHE 				  **
****************************************************************/
/**
 * \fn static void menuOuvrir (GtkWidget *pWidget, gpointer donneesUser)
 * \brief Fonction qui ouvre un fichier graphe enregistré avec le programme.
 *
 * \param[in] pWidget Le widget qui a appelé cette fonction.
 * \param[in] donneesUser Les données de l'utilisateur si nécessaire.
 */
static void menuOuvrir (GtkWidget *pWidget, gpointer donneesUser)
{
  /* Création de la boite de dialogue */
  GtkWidget *pDialogue = NULL;
  pDialogue = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  /* Si l'utilisateur souhaite ouvrir un fichier */
  if (gtk_dialog_run (GTK_DIALOG (pDialogue)) == GTK_RESPONSE_ACCEPT)
  {
    gchar *nomFichier = NULL;

    nomFichier = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pDialogue));
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
      {
	print_warning ("Impossible d'ouvrir le fichier %s\n", nomFichier);
      }
    else
      {
	if (graphe != NULL)
	  desallouerGraphe (graphe);
	graphe = lireGraphe (fichier);
	fclose(fichier);
	ouvertFichier = 1;
      }
    //g_free (nomFichier), nomFichier = NULL;
  }
  gtk_widget_destroy (pDialogue);

}

/**
 * \fn void print_warning (char *format, ...)
 * \brief Fonction qui écrit une alerte si le fichier "graphe" ne peut s'ouvrir
 *
 * \param[in] format Endroit où est placé le fichier.
 */
void print_warning (char *format, ...)
{
  va_list va;

  va_start (va, format);
  fprintf (stderr, "Erreur : ");
  vfprintf (stderr, format, va);
  fprintf (stderr, "\n");
  }

/***************************************************************
**			     SAUVEGARDER LE GRAPHE COURANT		    	  **
****************************************************************/
/**
 * \fn static void menuSauvegarder (GtkWidget *pWidget, gpointer DonnesUser)
 * \brief Fonction qui ouvre un fichier graphe enregistré avec le programme.
 *
 * \param[in] pWidget Le widget qui a appelé cette fonction.
 * \param[in] donneesUser Les données de l'utilisateur si nécessaire.
 */
static void menuSauvegarder (GtkWidget *pWidget, gpointer DonnesUser)
{
  GtkWidget *pDialogue = NULL;
  gchar *chemin;

  pDialogue = gtk_file_chooser_dialog_new ("Sauvegarder le fichier", NULL,
					  GTK_FILE_CHOOSER_ACTION_SAVE,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
					  NULL);
  if (gtk_dialog_run (GTK_DIALOG (pDialogue)) == GTK_RESPONSE_ACCEPT)
    {
      chemin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (pDialogue));
      sauvegarderGraphe(graphe, listeSommets, chemin);
    }
  gtk_widget_destroy (pDialogue);
}

/***************************************************************
**			     	QUITTER L'APPLICATION			    	  **
****************************************************************/
/**
 * \fn static void menuQuitter (void)
 * \brief Fonction permettant de quitter le programme.
 *
 */
static void menuQuitter (void)
{
   gtk_main_quit ();
   return;
}

/***************************************************************
**			        MENU AIDE PAS ESTHETIQUE		    	  **
****************************************************************/
/**
 * \fn static void menuAide (void)
 * \brief Fonction permettant d'afficher l'aide.
 *
 */
static void menuAide (void)
{
  GtkWidget *pWindow;
  GtkWidget *pDialogue = NULL;
  GtkWidget* texteAide;
  gchar* sUtf8;

  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(pWindow),"Aide");
  gtk_window_set_default_size(GTK_WINDOW(pWindow),600,800);

  texteAide = gtk_label_new(NULL);

  sUtf8 = g_locale_to_utf8("		  \t<b>AIDE</b>		      \n\n\n"
                           "\t - Sélectionnez un Algorithme parmi  \n"
                           " \tles quatre disponibles dans le  \n"
                           "\t menu ou la barre d'outils. 	      \n"
                           "				      \n"
                           "\t - Rentrez le nombre de sommets      \n"
                           "   	       	      	 	      \n"
                           " \t- Choisissez le type de réprésenta  \n"
                           " \ttion des sommets : Point ou Disque  \n"
                           "      	   	     	      	      \n"
                           "\t - Appuyez sur Valider pour éxécuter \n"
                           " \tle programme.		     	      \n"
                           "				      \n"
                           "\t - Vous  pouvez lire  la distance du \n"
                           " \tparcours  dans  le  coin  inférieur \n"
                           " \tgauche du programme.	    	      \n"
                           "				      \n\n\n"

                           "\t <b>Note</b> : Pour voir apparaitre le par  \n"
                           "\t cours à l'écran vous devez redimens \n"
                           "\t sioner la fenetre [BUG]	      \n\n\n"

                           " \t<b>Info</b> : Vous pouvez également sauve- \n"
                           "\t garder  un graphe, ouvrir un graphe \n"
                           "\t déjà  sauvegardé,  utiliser  l'algo \n"
                           " \t2-opt  pour  améliorer un  parcours \n"
                           " \tdéjà existant...	     	      \n\n"
			   , -1, NULL, NULL, NULL);
  
  gtk_label_set_markup(GTK_LABEL(texteAide), sUtf8);
  gtk_container_add(GTK_CONTAINER(pWindow),texteAide);
			   gtk_widget_show_all(pWindow);
			   
  g_free(sUtf8);
  gtk_widget_destroy (pDialogue);
  return;
}


/***************************************************************
**			     		   MENU A PROPOS			    	  **
****************************************************************/
/**
 * \fn static void menuAPropos (GtkWidget *pWidget, gpointer donneesUser)
 * \brief Fonction qui affiche le menu A Propos.
 *
 * \param[in] pWidget Le widget qui a appelé cette fonction.
 * \param[in] donneesUser Les données de l'utilisateur si nécessaire.
 */
static void menuAPropos (GtkWidget *pWidget, gpointer donneesUser)
{
  GtkWidget *AProposDialogue = NULL;

  AProposDialogue = gtk_about_dialog_new ();
  gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (AProposDialogue), "1.1");
  gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG (AProposDialogue), "Voyageur de Commerce");
  
  {
    const gchar *auteurs[2] = {"Victor BUSA", NULL};

    gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (AProposDialogue), auteurs);
  }
  {
    gchar *contenu = NULL;

    if (g_file_get_contents ("COPYING", &contenu, NULL, NULL))
    {
      gchar *utf8 = NULL;

      utf8 = g_locale_to_utf8 (contenu, -1, NULL, NULL, NULL);
      g_free (contenu), contenu = NULL;
      gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (AProposDialogue), utf8);
      g_free (utf8), utf8 = NULL;
    }
  }
  gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (AProposDialogue), "http://www.telecom-sudparis.eu/fr_accueil.html");
  {
    GdkPixbuf *logo = NULL;

    logo = gdk_pixbuf_new_from_file ("logo.png", NULL);
    gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (AProposDialogue), logo);
  }
  gtk_dialog_run (GTK_DIALOG (AProposDialogue));
  gtk_widget_destroy (AProposDialogue);
}

/**
 * \fn static void activate_radio_action (GtkAction *action, GtkRadioAction *current, gpointer data)
 * \brief Fonction qui permet de savoir qu'elle algorithme a été choisi.
 *
 * \param[in] action ??
 * \param[in] current L'algorithme qui est sélectionné
 * \param[in] data Les données de l'utilisateur (nécessaire ici).
 */
static void activate_radio_action (GtkAction *action, GtkRadioAction *current, gpointer data)
{
  /*g_message ("Radio action \"%s\" selected", 
    gtk_action_get_name (GTK_ACTION (current))); */
  mesArguments * mesArgs = (mesArguments *) data;
  mesArgs->algo = gtk_radio_action_get_current_value (current);
}

/**
 * \fn void onValider(GtkWidget *widget, gpointer data)
 * \brief Fonction qui applique les heuristiques en fonction des options choisies.
 *
 * \param[in] widget Le widget relié à cette action
 * \param[in] data Les données de l'utilisateur (nécessaire ici).
 */
void onValider(GtkWidget *widget, gpointer data)
{
    GtkWidget *pInfo;
    GtkWidget *pWindow;
    GSList *pList;
    const gchar *sLabel;

    mesArguments * mesArgs = (mesArguments *) data;

    /* Récupération de la liste des boutons */
    pList = gtk_radio_button_get_group(GTK_RADIO_BUTTON(mesArgs->boutonP));

    /* Parcours de la liste */
    while(pList)
    {
        /* Le bouton est-il sélectionné */
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pList->data)))
        {
            /* OUI -> on copie le label du bouton */
            sLabel = gtk_button_get_label(GTK_BUTTON(pList->data));
            /* On met la liste a NULL pour sortir de la boucle */
            pList = NULL;
        }
        else
        {
            /* NON -> on passe au bouton suivant */
            pList = g_slist_next(pList);
        }
    }    

    int nbSom = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mesArgs->nbSommet));

    switch(mesArgs->algo)
      {
      case 0:
	{ 
	  if (ouvertFichier != 1)
	    graphe = completerGraphe(mesArgs->largeur, mesArgs->hauteur, nbSom, sLabel, &rayon, graphe);
	  else
	    {
	      pointOuDisque(mesArgs->largeur, mesArgs->hauteur, sLabel, graphe->nSom, &rayon);
	      ouvertFichier = 0;
	    }
	  listeSommets = plusProcheVoisin(graphe);
	} break;

      case 1:
	{
	  if (ouvertFichier != 1)
	    graphe = completerGraphe(mesArgs->largeur, mesArgs->hauteur, nbSom, sLabel, &rayon, graphe);
	  else
	    {
	      pointOuDisque(mesArgs->largeur, mesArgs->hauteur, sLabel, graphe->nSom, &rayon);
	      ouvertFichier = 0;
	    }
	  listeSommets = plusProcheAddition (graphe);
	} break;

      case 2:
	{
	  if (ouvertFichier != 1)
	    graphe = completerGraphe(mesArgs->largeur, mesArgs->hauteur, nbSom, sLabel, &rayon, graphe);
	  else
	    {
	      pointOuDisque(mesArgs->largeur, mesArgs->hauteur, sLabel, graphe->nSom, &rayon);
	      ouvertFichier = 0;
	    }
	  listeSommets = insertionMoindreCout (graphe);
	} break;
	
      case 3:
	{
	  if (ouvertFichier != 1)
	    {
	      graphe = completerGraphe(mesArgs->largeur, mesArgs->hauteur, nbSom, sLabel, &rayon, graphe);
	    }
	  else
	    {
	      pointOuDisque(mesArgs->largeur, mesArgs->hauteur, sLabel, graphe->nSom, &rayon);
	      ouvertFichier = 0;
	    }
	  listeSommets = insertionPlusLointaine(graphe);
	} break;

      default:
	{
	  pWindow = gtk_widget_get_toplevel(GTK_WIDGET(data));

	  pInfo = gtk_message_dialog_new (GTK_WINDOW(pWindow),
					  GTK_DIALOG_MODAL,
					  GTK_MESSAGE_INFO,
					  GTK_BUTTONS_OK,
					  g_locale_to_utf8("Vous n'avez pas selectionné d'algorithme !\n", -1, NULL, NULL, NULL));

	  gtk_dialog_run(GTK_DIALOG(pInfo));

	  gtk_widget_destroy(pInfo);
	} break;

      }

}


