/**********************************************************************/
/*** fichier: mesh2d.c ***/
/*** Fonction d'initialisation et de destruction des structures Mesh***/
/**********************************************************************/



#include <stdlib.h>
#include "../include/mesh2d.h"

void initialize_mesh(struct Mesh *mesh)
{
	mesh->nvert = 0;
	mesh->ntri = 0;
	mesh->vertices = NULL;
	mesh->triangles = NULL;
}

void dispose_mesh(struct Mesh *mesh)
{
	mesh->nvert = 0;
	mesh->ntri = 0;
	free(mesh->vertices);
	mesh->vertices = NULL;
	free(mesh->triangles);
	mesh->triangles = NULL;
}
