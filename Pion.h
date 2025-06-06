#ifndef PION_H
#define PION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "Grille.h"



typedef struct pion_s{
    int x;
    int y;
    int x_old;
    int y_old;
}pion;

typedef enum Evenement {HAUT, BAS, DROITE, GAUCHE}Evenement;

pion * allouer_pion(int x, int y);

void desallouer_pion(pion* P);

void placer_pion(pion* P, int x, int y, Grille* L);

void jouer_pion(pion* P, Grille* L);

void Pion_deplacer(pion* P, Evenement e, Grille* L);

void jouer_pion_auto(pion* P, Grille* L);



#endif
