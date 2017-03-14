OBJETS = "Le voyageur de commerce.o" heuristic.o graphe.o listeSimple.o liste.o viderLeCache.o 

CC = gcc

CFLAGS = -Wall -g

EXEC = "Le voyageur de commerce"

all : $(EXEC) clean

Le voyageur de commerce : $(OBJETS)
	cc `pkg-config --cflags --libs gtk+-3.0` -lm $^ -o $@

Le voyageur de commerce.o : "Le voyageur de commerce.c" heuristic.h constantes.h
	cc `pkg-config --cflags --libs gtk+-3.0` -o $@ -c $<

heuristic.o : heuristic.c heuristic.h graphe.h liste.h
	$(CC) $(CFLAGS) -o $@ -c $<

graphe.o : graphe.c graphe.h listeSimple.h constantes.h viderLeCache.h
	$(CC) $(CFLAGS) -o $@ -c -lm $<

listeSimple.o : listeSimple.c listeSimple.h booleen.h point.h
	$(CC) $(CFLAGS) -o $@ -c $<

liste.o : liste.c liste.h point.h
	$(CC) $(CFLAGS) -o $@ -c $<

viderLeCache.o : viderLeCache.c viderLeCache.c
	$(CC) $(CFLAGS) -o $@ -c $<


# suppresion des fichiers intermédiaires
clean : 
	rm -f *.o

mrproper : clean
	rm -rf $(EXEC)
