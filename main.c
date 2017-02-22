#include "jeuDeLaVie.h"
 
/* compilation : 

gcc -c -Wall -Wextra main.c $(sdl-config --cflags --libs)
gcc -c -Wall -Wextra jeuDeLaVie.c $(sdl-config --cflags)
gcc -o jeuVie main.o jeuDeLaVie.o $(sdl-config --libs)
*/

int main(int argc, char *argv[])
{
	SDL_Rect position;
	SDL_Surface *ecran = NULL;
	SDL_Event event;
	SDL_Surface *lignes[LONGUEUR] = {NULL};
	int continuer = 1;
	int i;
	Grille grille;
	
	/* Initialisation */
		
	/* Initialisation pour la fenêtre */
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE); 
	}
	ecran=SDL_SetVideoMode(LARGEUR, LONGUEUR, 32, SDL_HWSURFACE);
	if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
	{
		fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
   	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
	SDL_WM_SetCaption("Le jeu de la vie", NULL);
	printf("Initialisation de la fenetre -> OK\n");
	
	/* Initialisation pour le jeu */
	for(i=0; i<LONGUEUR; i++)
		lignes[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, ZOOM, ZOOM, 32, 0, 0, 0, 0);
	printf("Initialisation des surfaces -> OK\n");	
	initGrille(grille, ecran, position, lignes);
	printf("Initialisation de la grille -> OK\n");
	
	/* Le jeu */
	while (continuer)
	{
		update(grille, ecran, position, lignes);
		printf("Update -> OK\n");
	    SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
			continuer = 0;
		}
    }

	/* Fin */
	for (i=0; i<LONGUEUR; i++) 
        SDL_FreeSurface(lignes[i]);
	SDL_Quit();
	return EXIT_SUCCESS;
}

