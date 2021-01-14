/**********************************************************************/
/*** fichier: mesh2d.c ***/
/*** Fonction d'initialisation et de destruction des structures Mesh,***/
/*** d�finition des structures Vertex, Triangle et Mesh ***/
/**********************************************************************/


#ifndef _MESH2D_H
#define _MESH2D_H

/* Structure Vertex correspondant � un sommet du maillage,
 * contient les coordonn�es x et y du sommet. */

struct Vertex {
	union {
		struct {
			double x,y;
		};
		double coord[2];
	};
};

/* Structure Triangle correspondant aux triangles d'une structure Mesh,
 * contient le num�ro des 3 sommets du Triangle */
struct Triangle {
	union {
		struct {
			int v1, v2, v3;
		};
		int idx[3];
	};
};


/* Structure Mesh correspondant � un maillage,
 * contient le nombre de sommets, le nombre de trianglees,
 * les coordonn�es des sommets et � quels sommet chaque
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

/* lib�re l'espace m�moire allou� � une structure Mesh
 * @param m : adresse de la structure Mesh.*/
void dispose_mesh(struct Mesh *mesh);


#endif