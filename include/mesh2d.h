/**********************************************************************/
/*** fichier: mesh2d.c ***/
/*** Fonction d'initialisation et de destruction des structures Mesh,***/
/*** définition des structures Vertex, Triangle et Mesh ***/
/**********************************************************************/


#ifndef _MESH2D_H
#define _MESH2D_H

/* Structure Vertex correspondant à un sommet du maillage,
 * contient les coordonnées x et y du sommet. */

struct Vertex {
	union {
		struct {
			double x,y;
		};
		double coord[2];
	};
};

/* Structure Triangle correspondant aux triangles d'une structure Mesh,
 * contient le numéro des 3 sommets du Triangle */
struct Triangle {
	union {
		struct {
			int v1, v2, v3;
		};
		int idx[3];
	};
};


/* Structure Mesh correspondant à un maillage,
 * contient le nombre de sommets, le nombre de trianglees,
 * les coordonnées des sommets et à quels sommet chaque
 * triangle correspond. */
struct Mesh {
	int nvert;
	int ntri;
	struct Vertex *vertices;
	struct Triangle *triangles;
};

/* Initialise une structure Mesh
 * @param m : adresse de la structure Mesh.*/
void initialize_mesh(struct Mesh *mesh);

/* libère l'espace mémoire alloué à une structure Mesh
 * @param m : adresse de la structure Mesh.*/
void dispose_mesh(struct Mesh *mesh);


#endif