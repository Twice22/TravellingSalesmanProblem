/**
 * \file viderLeCache.c
 * \brief Vide le buffer
 * \author Victor.B
 * \version 1.0
 * \date 13 avril 2013
 *
 */

#include <stdio.h>

/**
 * \fn void avoidBuffer()
 * \brief Fonction qui vide le Buffer pour éviter des erreurs aux niveaux des saisies.
 */
void avoidBuffer()
{
  int c = 0;
  while( (c=getchar()) != '\n' && c != EOF);
}
