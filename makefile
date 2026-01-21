CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: play

play : pile.o lecturePPM.o couleur.o bloc.o main.o 
	$(CC) $(CFLAGS) -o play pile.o lecturePPM.o couleur.o  main.o

pile.o: pile.c pile.h
	$(CC) $(CFLAGS) -c pile.c

lecturePPM.o: lecturePPM.c lecturePPM.h
	$(CC) $(CFLAGS) -c lecturePPM.c

couleur.o: couleur.c couleur.h
	$(CC) $(CFLAGS) -c couleur.c

bloc.o: bloc.c bloc.h
	$(CC) $(CFLAGS) -c bloc.c

main.o: main.c pile.h bloc.h couleur.h lecturePPM.h
	$(CC) $(CFLAGS) -c main.c
