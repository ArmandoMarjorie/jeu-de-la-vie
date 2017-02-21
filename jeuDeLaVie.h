#ifndef JEU_VIE
#define JEU_VIE
	
	#include <stdlib.h>
	#include <stdio.h>
	#include <SDL/SDL.h>
	
	#define VIVANTE 1
	#define MORTE 0
	#define LARGEUR 500
	#define LONGUEUR 500
	#define ZOOM 10
	
	typedef struct
	{
		int etatActuel;
		int etatPrecedent;
	}Case;
	
	typedef Case* Grille[LONGUEUR][LARGEUR];
	//longeur = nb de lignes
	//largeur = nb de colonnes
	
	void initGrille(Grille grille, SDL_Surface* ecran, SDL_Rect position, SDL_Surface *lignes[]);
	void update(Grille grille, SDL_Surface* ecran, SDL_Rect position, SDL_Surface *lignes[]);
	void coloriage(int i, int j, SDL_Surface* ecran, SDL_Rect position, SDL_Surface *lignes[]);
	
#endif
