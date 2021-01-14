/**********************************************************************/
/*** fichier: mesh_from_file.c ***/
/*** Crée une structure Mesh à partir d'un fichier .ele et d'un fichier.node.***/
/**********************************************************************/

#ifndef _MESH_FROM_FILE_H
#define _MESH_FROM_FILE_H


/* Remplit une structure Mesh à partir d'un fichier ".node" et d'un fichier ".ele".
 * @param m : adresse de la structure Mesh.
 * @param filename1 : adresse du fichier ".poly".*/
void read_mesh_from_files(struct Mesh *m, const char* poly);

#endif
