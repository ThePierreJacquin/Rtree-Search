/**********************************************************************/
/*** fichier: operations.h ***/
/*** contient toutes les op�rations n�c�ssaires � la recherche du triangle contenant le point:***/
/*** Test d'appartenance, cr�ation de R-arbre, recherche dans un R-Arbre ***/
/**********************************************************************/

#ifndef _OPERATION_H
#define _OPERATION_H

#include "../lib/rtree/rtree.h"

/* Renvoit 1 si le point est dans le triangle, 0 sinon.
 * @param point : adresse d'une structure point .
 * @param tid : num�ro du triangle dans le maillage.
 * @param mesh : adresse du maillage.*/
int point_in_tri(struct Vertex* point, int tid, struct Mesh* mesh);

/* Cr�e un R-tree � partir d'un maillage 2d. 
 * @param rtree : adresse du R-tree.
 * @param mesh : adresse du maillage.*/
void Rtree_from_mesh(RTREENODE** rtree,struct Mesh* mesh);

/* permet � l'utilisateur de chercher � quel triangles du maillage appartient un point du plan.
 * @param mesh : adresse du maillage.*/
void Triangle_search(struct Mesh* mesh);

#endif
