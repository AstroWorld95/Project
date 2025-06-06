#include <stdio.h>
#include <stdlib.h>
#include "Pion.h"
#include "Grille.h"
#include <time.h>
#include <ncurses.h>

pion* allouer_pion(int x, int y){
    pion* Pion = malloc(sizeof(pion));
    if (!Pion) {
        printf("Erreur allocation pion");
        exit(2);
    }
    Pion->x = x;
    Pion->y = y;
    Pion->x_old = x;
    Pion->y_old = y;
    return Pion;
}


void desallouer_pion(pion* P){
    free(P);
}

void placer_pion(pion* P, int x, int y, Grille* L){
    P->x_old = P->x;
    P->y_old = P->y;
    P->x = x;
    P->y = y;
    L->tab[P->x][P->y] = PION; // <-- Met à jour la grille
    
}

void Pion_deplacer(pion* P, Evenement e, Grille* L) {
    P->x_old = P->x;
    P->y_old = P->y;

    /*Mettre à jour la position du pion selon l'événement*/
    switch (e) {
        case HAUT:
            if (P->x > 1) P->x--;
            break;
        case BAS:
            if (P->x < L->n - 2) P->x++;
            break;
        case GAUCHE:
            if (P->y > 1) P->y--;
            break;
        case DROITE:
            if (P->y < L->m - 2) P->y++;
            break;
    }
}


void jouer_pion(pion* P, Grille* L) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    halfdelay(1);
    int s;
    do {
        s = getch();
        Evenement e;
        switch (s) {
            case KEY_UP: e = HAUT; break;
            case KEY_DOWN: e = BAS; break;
            case KEY_LEFT: e = GAUCHE; break;
            case KEY_RIGHT: e = DROITE; break;
            default: continue;
        }
        Pion_deplacer(P, e, L);
        L->tab[P->x_old][P->y_old]=RIEN;
        if (L->tab[P->x][P->y] == TRESOR) {
            L->tab[P->x][P->y] = PION;
            Grille_redessiner(L);
            break;
        }
        if (L->tab[P->x][P->y] == PIEGE) {
            L->tab[P->x][P->y] = RIEN;
            printf("\nVous avez perdu\n");
            endwin();
            exit(0);
        }
        L->tab[P->x][P->y] = PION;
        Grille_redessiner(L);
    } while (s != 27);
    endwin();
}


void jouer_pion_auto(pion* P, Grille* L) {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    halfdelay(3); // Délai court pour getch()

    int s;
    Evenement direction = DROITE; // Direction initiale
    int fini = 0;

    do {
        s = getch();
        switch (s) {
            case KEY_UP: direction = HAUT; break;
            case KEY_DOWN: direction = BAS; break;
            case KEY_LEFT: direction = GAUCHE; break;
            case KEY_RIGHT: direction = DROITE; break;
            case 27: fini = 1; break; // Touche Echap pour quitter
            default: break; // Si aucune touche, continue dans la même direction
        }

        // Déplacement automatique dans la direction courante
        Pion_deplacer(P, direction, L);
        L->tab[P->x_old][P->y_old] = RIEN;

        if (L->tab[P->x][P->y] == TRESOR) {
            L->tab[P->x][P->y] = PION;
            Grille_redessiner(L);
            fini = 1; // Gagné
        } else if (L->tab[P->x][P->y] == PIEGE) {
            L->tab[P->x][P->y] = RIEN;
            printf("\nVous avez perdu\n");
            endwin();
            exit(0);
        } else {
            L->tab[P->x][P->y] = PION;
            Grille_redessiner(L);
        }

    } while (!fini);

    endwin();
}

