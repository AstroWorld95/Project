#ifndef GRILLE_H
#define GRILLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

enum grille {RIEN, MUR, PION, PIEGE, TRESOR};

typedef struct {
    int n;
    int m;
    enum grille ** tab ;
}Grille;


Grille * Grille_initialiser (int n, int m);

void Grille_desallouer (Grille* L);

void Grille_redessiner(Grille *L);

void Grille_vider (Grille *L);

void position_mur(Grille *L);

void position_piege(Grille *L);

void position_tresor(Grille *L);

Grille* Grille_charger_fichier(const char* nom_fichier, int* pion_x, int* pion_y);

#endif
