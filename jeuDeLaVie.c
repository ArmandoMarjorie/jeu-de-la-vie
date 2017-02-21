#include <time.h>
#include "jeuDeLaVie.h"

/* Initialise la grille au hasard */
void initGrille(Grille grille, SDL_Surface* ecran, SDL_Rect position, SDL_Surface *lignes[])
{
	int i,j;
	srand(time(NULL));
	
	for(i=0; i<LONGUEUR; i+=ZOOM)
		for(j=0; j<LARGEUR; j+=ZOOM)
		{
			grille[i][j] = malloc(sizeof(Case)); 
			grille[i][j]->etatActuel=grille[i][j]->etatPrecedent=rand()%2;
			if(grille[i][j]->etatActuel==VIVANTE)
				coloriage(i,j,ecran,position,lignes);
		}
}

/* se base sur les états précédents (en interne)*/
void update(Grille grille, SDL_Surface* ecran, SDL_Rect position, SDL_Surface *lignes[])
{
	int i,j;
	int cptVoisinsVivants;
	
	for(i=0; i<LONGUEUR; i+=ZOOM) //ligne
	{
		for(j=0;j<LARGEUR; j+=ZOOM) //colonne
		{
			cptVoisinsVivants=0;
			printf("%d %d\n",i,j);
			if(grille[i][j]==NULL)
				break;
			
			if(grille[i][j-ZOOM]!=NULL && grille[i][j-ZOOM]->etatPrecedent==VIVANTE) //cellule a gauche
			{
				printf("%d %d\n",i,j-ZOOM);
				printf("cellule a gauche\n");
				cptVoisinsVivants++;
			}
			if(grille[i][j+ZOOM]!=NULL && grille[i][j+ZOOM]->etatPrecedent==VIVANTE) //cellule a droite
			{
				printf("%d %d\n",i,j+ZOOM);
				printf("cellule a droite\n");
				cptVoisinsVivants++;
			}
			if(grille[i-ZOOM][j]!=NULL && grille[i-ZOOM][j]->etatPrecedent==VIVANTE) //cellule en haut
			{
				printf("%d %d\n",i-ZOOM,j);
				printf("cellule en haut\n");
				cptVoisinsVivants++;
			}
			if(grille[i+ZOOM][j]!=NULL && grille[i+ZOOM][j]->etatPrecedent==VIVANTE) //cellule en bas
			{
				printf("%d %d\n",i+ZOOM,j);
				printf("cellule en bas\n");
				cptVoisinsVivants++;
			}
			if(grille[i-ZOOM][j-ZOOM]!=NULL && grille[i-ZOOM][j-ZOOM]->etatPrecedent==VIVANTE) //cellule en haut a gauche
			{
				printf("%d %d\n",i-ZOOM,j-ZOOM);
				printf("cellule en haut a gauche\n");
				cptVoisinsVivants++;
			}
			if(grille[i-ZOOM][j+ZOOM]!=NULL && grille[i-ZOOM][j+ZOOM]->etatPrecedent==VIVANTE) //cellule en haut a droite
			{
				printf("%d %d\n",i-ZOOM,j+ZOOM);
				printf("cellule en haut a droite\n");
				cptVoisinsVivants++;
			}
			if(grille[i+ZOOM][j-ZOOM]!=NULL && grille[i+ZOOM][j-ZOOM]->etatPrecedent==VIVANTE) //cellule en bas a gauche
			{
				printf("%d %d\n",i+ZOOM,j-ZOOM);
				printf("cellule en bas a gauche\n");
				cptVoisinsVivants++;
			}
			if(grille[i+ZOOM][j+ZOOM]!=NULL && grille[i+ZOOM][j+ZOOM]->etatPrecedent==VIVANTE) //cellule en bas a droite
			{
				printf("%d %d\n",i+ZOOM,j+ZOOM);
				printf("cellule en bas a droite\n");
				cptVoisinsVivants++;
			}
			
			//printf("\tCase %d\n",cpt);
			/* Si une cellule est morte et a exactement 3 voisins vivants */
			if(grille[i][j]!=NULL && grille[i][j]->etatPrecedent==MORTE && cptVoisinsVivants==3)
			{
				printf("Je deviens vivante !\n");
				grille[i][j]->etatActuel=VIVANTE;
			}
			
			/* Si une cellule est vivante et a 2 ou 3 voisins vivants elle reste vivante, sinon elle meurt */
			else if(grille[i][j]!=NULL && grille[i][j]->etatPrecedent==VIVANTE && !(cptVoisinsVivants==2 || cptVoisinsVivants==3) )
			{
				printf("Je meurs !\n");
				grille[i][j]->etatActuel=MORTE;
			}
			
			if(grille[i][j]!=NULL && grille[i][j]->etatActuel==VIVANTE)
				coloriage(i,j,ecran,position,lignes);
		}
	}
	
	for(i=0; i<LARGEUR; i+=ZOOM)
		for(j=0; j<LONGUEUR; j+=ZOOM)
			if(grille[i][j]!=NULL)
				grille[i][j]->etatPrecedent = grille[i][j]->etatActuel;
}

/* se base sur les états actuels (en externe : update sur l'écran) */
void coloriage(int i, int j, SDL_Surface* ecran, SDL_Rect position, SDL_Surface *lignes[])
{
	int k;
	position.x = j; // La position horizontale dépend du numéro de la colonne
	position.y = i; // La position verticale dépend du numéro de la ligne
	
	SDL_FillRect(lignes[i], NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); // Dessin
	SDL_BlitSurface(lignes[i], NULL, ecran, &position); // Collage
	
	printf("Je dessine !\n\n\n");
	SDL_Flip(ecran);
	for(k=0; k<4000; k++); //pour faire une pause entre les dessins
}




