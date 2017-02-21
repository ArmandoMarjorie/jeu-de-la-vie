EXEC= jeuVie

all: $(EXEC)

jeuVie: main.o jeuDeLaVie.o
	gcc -o jeuVie main.o jeuDeLaVie.o `sdl-config --libs`
	
main.o: main.c jeuDeLaVie.h
	gcc -c -Wall -Wextra main.c `sdl-config --cflags --libs`
	
jeuDeLaVie.o: jeuDeLaVie.c jeuDeLaVie.h
	gcc -c -Wall -Wextra jeuDeLaVie.c `sdl-config --cflags`

clean:
	rm -rf *.o
	
rmproper: clean
	rm -rf $(EXEC)
