#ifndef POINT_H
#define POINT_H 1

/**
 * \struct Coord
 * \brief Coordonnée d'un point.
 *
 * Coord est une structure donnant la position d'un
 * point selon l'axe des abscisses (x) et selon l'axe
 * des ordonnées (y) dans le plan euclidien.
 */
typedef struct
{
	int x;
	int y;
} Coord;

#endif
