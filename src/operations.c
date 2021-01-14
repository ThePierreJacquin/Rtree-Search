/**********************************************************************/
/*** fichier: operations.c ***/
/*** contient toutes les op�rations n�c�ssaires � la recherche du triangle contenant le point:***/
/*** Test d'appartenance, cr�ation de R-arbre, recherche dans un R-Arbre ***/
/**********************************************************************/


#include <stdlib.h>
#include <stdio.h>	

#include "../include/mesh2d.h"
#include "../include/operations.h"
#include "../lib/rtree/rtree.h"


//Structure vecteur pour faciliter l'impl�mentation des diverses formules
typedef struct { double a, b;} vector;  

//Produit scalaire entre deux vecteurs
double scalar_product(vector A, vector B)
{
	return A.a * B.a + A.b * B.b ;  
}


int point_in_tri(struct Vertex* point, int tid, struct Mesh* mesh)
{
	struct Triangle t=mesh->triangles[tid];
	double x = point->x;
	double y = point->y;
	
	// On calcule les vecteurs  
	struct Vertex A = mesh->vertices[t.v1];
	struct Vertex B = mesh->vertices[t.v2];
	struct Vertex C = mesh->vertices[t.v3];
								   
	vector v0 = {C.x - A.x,C.y - A.y};
	vector v1 = {B.x - A.x,B.y - A.y};
	vector v2 = {x - A.x,y - A.y};

	// On calcule les produits vectoriels
	double sp00 = scalar_product(v0, v0);
	double sp01 = scalar_product(v0, v1);
	double sp02 = scalar_product(v0, v2);
	double sp11 = scalar_product(v1, v1);
	double sp12 = scalar_product(v1, v2);

	// On calcule les coordon�es du barycentre
	double invDenom = 1 / (sp00 * sp11 - sp01 * sp01);
	double u = (sp11 * sp02 - sp01 * sp12) * invDenom;
	double v = (sp00 * sp12 - sp01 * sp02) * invDenom;

	// On v�rifie si le point est dans le triangle
	return (u >= 0) && (v >= 0) && (u + v < 1);
}

//fonction max pour factoriser le code
double max(double x, double y, double z)
{
	double max=x;
	if (max<y){max=y;};								
	if (max<z){max=z;};
	return max;
}

//fonction min pour factoriser le code
double min(double x, double y, double z)
{
	double min=x;								
	if (min>y){min=y;};
	if (min>z){min=z;};
	return min;
}


void Rtree_from_mesh(RTREENODE** root,struct Mesh* mesh)
{

	for (int i=0;i<mesh->ntri;i++)
	{	
		//On r�cup�re les sommets de chaque triangle
		struct Vertex a=mesh->vertices[mesh->triangles[i].v1];
		struct Vertex b=mesh->vertices[mesh->triangles[i].v2];
		struct Vertex c=mesh->vertices[mesh->triangles[i].v3];

		//On cr�e son rectangle minimum d'inclusion 
		double ymax=max(a.y,b.y,c.y);
		double ymin=min(a.y,b.y,c.y);
		double xmax=max(a.x,b.x,c.x);								
		double xmin=min(a.x,b.x,c.x);								
		RTREEMBR bounding_box={{xmin,ymin,xmax,ymax}};
		
		//On l'ins�re dans l'arbre
		RTreeInsertRect(&bounding_box,i+1,root,0);					
	}
}

		
int MySearchCallback(int id, struct Vertex* point, struct Mesh* mesh) 
{
	//On teste l'appartenance du point au triangle potentiel
	if (point_in_tri(point, id-1, mesh))
	{
		struct Triangle t = mesh->triangles[id-1];
		printf("\nLe point est dans le triangle %d !\n",id-1);     
		printf("coordonn�es v1: %f,%f\n",mesh->vertices[t.v1].x,mesh->vertices[t.v1].y);
		printf("coordonn�es v2: %f,%f\n",mesh->vertices[t.v2].x,mesh->vertices[t.v2].y);
		printf("coordonn�es v3: %f,%f\n",mesh->vertices[t.v3].x,mesh->vertices[t.v3].y);
		return 0;
	}
	return 1;  
}

void Triangle_search(struct Mesh* mesh)
{
	int choice=1;
	
	struct Vertex point;

	//On cr�e le R-Arbre associ� au maillage
	printf("Creation de l'arbre \n...\n");
	RTREENODE* root=RTreeCreate();
	Rtree_from_mesh(&root, mesh);
	printf("Arbre cree \n...\n");

	while (choice==1)
	{
		//Cette mise � jour est n�c�ssaire pour que le programme 
		//ne fasse pas une boucle quand choice est une cha�ne de charact�re.
		choice=0;

		//On demande � l'utilisateur de choisir le point
		printf("Donnez les coordonn�es x et y du point espac�es d'une virgule :\n");
		if (scanf("%lf,%lf",&point.x,&point.y) == 2) //On v�rifie que les coordonn�es ont le bon format
		{
			//On cr�e le rectangle de recherche
			RTREEMBR search_rect = {{point.x,point.y,point.x,point.y}};  

			//On effectue la recherche
			int nhits = RTreeSearch( root, &search_rect, MySearchCallback, &point, mesh);
	
			if (nhits==0)
			{
				printf("Le point n'est contenu dans aucun des triangles du maillage\n");
			}
			//On propose � l'utilisateur de chercher un autre point sans avoir � recr�er l'arbre
			printf("\nSi vous souhaitez chercher un autre point, tapez 1, sinon tapez 0 :\n>>");
			scanf("%i",&choice);
		}
		else
		{
		//cas o� le format est mauvais
		printf("Les coordonnees n'ont pas le bon format\n...\n");
		//on clear le buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF){}
		//on renvoit l'utilisateur au choix des coordonn�es
		choice=1;
		}
	}
	//On d�salloue la m�moire associ�e au R-Arbre
	RTreeDestroy(root);
}



