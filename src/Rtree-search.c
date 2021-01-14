/**********************************************************************/
/*** fichier: Rtree-search.c ***/
/*** A partir d'un maillage de triangles décrit par un fichier .poly,***/
/*** permet de rechercher le triangle contenant un point, s'il existe***/
/**********************************************************************/


#include <stdlib.h>	
#include <stdio.h>	
#include <string.h>
#include "../include/mesh2d.h"
#include "../include/operations.h"
#include "../include/mesh_from_file.h"

int main(){
									
	//je vais créer un maillage exemple à l'aide du programme Triangle de Shewchuk

	//30 est une longueur arbitraire pour éviter les 'segmentation fault'
	char *nom[30];
	char poly[36]="data/";

	//On récupère l'emplacement du fichiers
	printf("Donnez le nom du fichier .poly\n/data/");
	scanf("%s",nom);
	strcat(&poly,&nom);
	printf("...\n");
	
	//initialisation du maillage
	printf("Initialisation du maillage\n...\n");
	struct Mesh m;
	initialize_mesh(&m);
	read_mesh_from_files(&m, &poly); 
	printf("Maillage obtenu: %i points et %i triangles\n...\n",m.nvert,m.ntri);

	TestTemps(&m);
	//Triangle_search(&m);	
		
	dispose_mesh(&m);	
}