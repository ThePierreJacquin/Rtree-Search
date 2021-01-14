/**********************************************************************/
/*** fichier: TestTemps.c ***/
/*** calcule les performances de l'algorithme de recherche avec les R-Arbre***/
/*** et le compare a celles d'un algorithme na�f***/
/*** Ce fichier n'est pas compil� dans le makefile de base***/
/*** A l'�poque o� j'ai calcul� le temps, la fonction RTreeSearch ***/
 /*** ne proposait pas de cherche un deuxi�me point***/
/**********************************************************************/


#include <time.h>
#include "../include/mesh2d.h"
#include "../include/operations.h"
#include "../lib/rtree/rtree.h"

//On impl�mente les fonctions de chronom�trage
void start_timer(clock_t *timer)
{
	*timer = clock();             
}

float stop_timer(clock_t *timer)                  
{
	clock_t elapsed = clock() - *timer;
	return ((float) elapsed) / CLOCKS_PER_SEC;
}

//Algorithme na�f qui teste tous les points 1 par 1
int algo_naif(struct Vertex* point,struct Mesh* mesh)
{
	
	for(int i=0;i<mesh->ntri;i++)
	{
		if (point_in_tri(point, i, mesh))		
		{
			return i;
		}
	}
	return -1;
}

//On cr�e une fonction de Callback simple, qui n'affiche pas les r�sultats cette fois.
int MySearchCallback2(int id, struct Vertex* point, struct Mesh* mesh) 
{
	//On teste l'appartenance du point au triangle potentiel
	if (point_in_tri(point, id-1, mesh))
	{return 1;}
	else
	{return 0;}
    
}


void TestTemps(struct Mesh* mesh)
{
		//On teste la vitesse pour chaque puissance de 10. 
		//j'arr�te manuellement l'algorithme quand le temps d'�xecution d�passe une minute environ 
		for (int t=0;t<8;t++)
		{
			//premier chronom�tre pour le R-Arbre
			clock_t timer;
			start_timer(&timer);
		
			//On compte une seule fois le cout de cr�ation de l'arbre
			RTREENODE* root=RTreeCreate();
			Rtree_from_mesh(&root, mesh);

			printf("temps= %f\n",stop_timer(&timer));
			struct Vertex point;

			printf("\n Pour t=%d, on a \n",t);
			
			//On fait 10^t recherches de point al�atoires entre (0,0) et (1,1)
			for (int i=0;i<pow(10,t);i++)								
			{
				point.x = (rand() % 10000) / 10000.0;
				point.y = (rand() % 10000) / 10000.0;

				RTREEMBR search_rect = {{point.x,point.y,point.x,point.y}};
			
				RTreeSearch( root, &search_rect, MySearchCallback2, &point, mesh);

			}
			printf("Temps avec R-Arbre, %f\n",stop_timer(&timer));

			//Deuxi�me chronom�tre pour l'algorithme na�f
			clock_t timer2;

			start_timer(&timer2);

			for (int j=0;j<pow(10,t);j++)
			{
				point.x = (rand() % 10000) / 10000.0;					/*On chronom�tre l'algorithme na�f*/
				point.y = (rand() % 10000) / 10000.0;
				algo_naif(&point, mesh);
			}
			printf("Temps avec l'algorithme naif, %f\n",stop_timer(&timer2));
		}
}