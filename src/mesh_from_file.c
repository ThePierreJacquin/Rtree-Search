/**********************************************************************/
/*** fichier: mesh_from_file.c ***/
/*** Crée une structure Mesh à partir d'un fichier .poly.***/
/**********************************************************************/


#include <stdio.h>	// Used for fopen, fclose, fgets, sscanf and printf
#include <stdlib.h>	// Used for malloc and free 
#include <string.h> // Used for strcmp

#include "../include/mesh2d.h"
#include "../include/mesh_from_file.h"
#include "../lib/triangle/triangle.h"

#define LINE 128

void read_mesh_from_files(struct Mesh *m, const char* poly) 
{	int _[0];
	struct triangulateio in, out;

	
	//Lecture du fichier .poly
	FILE *f = fopen(poly, "r");
	char line[LINE];

	//On récupère le nombre de sommets
	fgets(line, LINE, f);while ((line[0] == '#')){fgets(line, LINE, f);}//le while est nécéssaire à chaque fgets() pour sauter les lignes de commentaires
	sscanf(line, "%i %i %i %i", &in.numberofpoints, _, &in.numberofpointattributes, _);
	in.pointlist = (REAL *) malloc(in.numberofpoints * 2 * sizeof(REAL));
	in.pointmarkerlist = (int *) malloc(in.numberofpoints * sizeof(int));

	//on récupère les sommets et leur coordonnées
	for (int i=0; i<in.numberofpoints; ++i) 
	{
		fgets(line, LINE, f);while ((line[0] == '#')){fgets(line, LINE, f);}
		sscanf(line, "%i %lf %lf %i",_,&in.pointlist[2*i], &in.pointlist[2*i+1],&in.pointmarkerlist[i]);
	}

	//on récupère le nombre de segments
	fgets(line, LINE, f);while ((line[0] == '#')){fgets(line, LINE, f);}
	sscanf(line, "%i %i ", &in.numberofsegments, _);
	in.segmentlist = (int *) malloc(in.numberofsegments * 2 * sizeof(int));
	in.segmentmarkerlist =(int *) malloc(in.numberofsegments * sizeof(int));

	//on récupère les segments et leur sommets respectifs
	for (int i=0; i<in.numberofsegments; ++i) 
	{
		fgets(line, LINE, f);while ((line[0] == '#')){fgets(line, LINE, f);}
		sscanf(line, "%i %i %i %i",_, &in.segmentlist[2*i], &in.segmentlist[2*i+1],&in.segmentmarkerlist[i]);
	}
	
	//On récupère le nombre de trous
	fgets(line, LINE, f);while ((line[0] == '#')){fgets(line, LINE, f);}
	sscanf(line, "%i ", &in.numberofholes);
	in.holelist = (REAL *) malloc(in.numberofholes * 2 * sizeof(REAL));
	in.numberofregions = 0;

	//On récupère les trous
	for (int i=0; i<in.numberofholes; ++i) 
	{
		fgets(line, LINE, f);while ((line[0] == '#')){fgets(line, LINE, f);}
		sscanf(line, "%i %lf %lf",_,&in.holelist[2*i], &in.holelist[2*i+1]);
	}
	fclose(f);

	//on initie les variables de sorties de l'algorithme
	out.pointlist = (REAL *) NULL;           
	out.pointattributelist = (REAL *) NULL;
	out.trianglelist = (int *) NULL;          
	out.triangleattributelist = (REAL *) NULL;
	out.segmentlist = (int *) NULL;
	out.segmentmarkerlist = (int *) NULL;
	out.edgelist = (int *) NULL;
	out.edgemarkerlist = (int *) NULL;

	//appel de triangulate()
	triangulate("Qqz", &in, &out, (struct triangulateio *) NULL);


	//On rentre les triangles dans la structure Mesh
	m->nvert=out.numberofpoints;
	m->vertices = malloc(m->nvert * sizeof(struct Vertex));

	for (int i=0; i<m->nvert;i++)
	{
		m->vertices[i].x=out.pointlist[2*i];
		m->vertices[i].y=out.pointlist[2*i+1];
	}
	
	m->ntri=out.numberoftriangles;
	m->triangles = malloc(m->ntri * sizeof(struct Triangle));

	for (int i=0; i<m->ntri; ++i) 
	{
		m->triangles[i].v1=out.trianglelist[3*i];
		m->triangles[i].v2=out.trianglelist[3*i+1];
		m->triangles[i].v3=out.trianglelist[3*i+2];
	}
	
	//On libère toutes les variables utilisées
	free(in.pointlist);
	free(in.pointmarkerlist);
	free(in.regionlist);
	free(in.holelist);
	free(in.segmentlist);
	free(in.segmentmarkerlist);

	free(out.pointlist);
	free(out.pointattributelist);
	free(out.trianglelist);
	free(out.triangleattributelist);
	free(out.edgelist);
	free(out.edgemarkerlist);
	free(out.segmentlist);
	free(out.segmentmarkerlist);
	return 0;}
