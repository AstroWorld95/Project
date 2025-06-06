#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grille.h"
#include "Pion.h"

int main() {
    srand(time(NULL)); // Graine aléatoire

    // ===== Grille générée =====
    Grille* G = Grille_initialiser(10, 10);
    position_mur(G);
    position_piege(G);
    position_tresor(G);
    pion* Pion = allouer_pion(4, 2);
    placer_pion(Pion, 4, 2, G);
    jouer_pion(Pion, G);

    printf("Ceci est un test pour vous montrer le système du jeu \n");

    // ===== grille.txt =====
    int px1, py1;
    Grille* G1 = Grille_charger_fichier("grille.txt", &px1, &py1);
    placer_pion(Pion, px1, py1, G1);
    jouer_pion(Pion, G1);

    // ===== grille2.txt =====
    int px2, py2;
    Grille* G2 = Grille_charger_fichier("grille2.txt", &px2, &py2);
    placer_pion(Pion, px2, py2, G2);
    jouer_pion(Pion, G2);

    // ===== grille3.txt =====
    int px3, py3;
    Grille* G3 = Grille_charger_fichier("grille3.txt", &px3, &py3);
    placer_pion(Pion, px3, py3, G3);
    jouer_pion(Pion, G3);

    // ===== grille4.txt =====
    int px4, py4;
    Grille* G4 = Grille_charger_fichier("grille4.txt", &px4, &py4);
    placer_pion(Pion, px4, py4, G4);
    jouer_pion(Pion, G4);

    // ===== grille5.txt =====
    int px5, py5;
    Grille* G5 = Grille_charger_fichier("grille5.txt", &px5, &py5);
    placer_pion(Pion, px5, py5, G5);
    jouer_pion_auto(Pion, G5);

    // ===== grille6.txt =====
    int px6, py6;
    Grille* G6 = Grille_charger_fichier("grille6.txt", &px6, &py6);
    placer_pion(Pion, px6, py6, G6);
    jouer_pion_auto(Pion, G6);

    // ===== grille7.txt =====
    int px7, py7;
    Grille* G7 = Grille_charger_fichier("grille7.txt", &px7, &py7);
    placer_pion(Pion, px7, py7, G7);
    jouer_pion_auto(Pion, G7);

    // ===== grille8.txt =====
    int px8, py8;
    Grille* G8 = Grille_charger_fichier("grille8.txt", &px8, &py8);
    placer_pion(Pion, px8, py8, G8);
    jouer_pion_auto(Pion, G8);

    // ===== grille9.txt =====
    int px9, py9;
    Grille* G9 = Grille_charger_fichier("grille9.txt", &px9, &py9);
    placer_pion(Pion, px9, py9, G9);
    jouer_pion_auto(Pion, G9);

    // ===== grille10.txt =====
    int px10, py10;
    Grille* G10 = Grille_charger_fichier("grille10.txt", &px10, &py10);
    placer_pion(Pion, px10, py10, G10);
    jouer_pion_auto(Pion, G10);

    // ===== Libération des ressources =====
    Grille_vider(G);    Grille_desallouer(G);
    Grille_vider(G1);   Grille_desallouer(G1);
    Grille_vider(G2);   Grille_desallouer(G2);
    Grille_vider(G3);   Grille_desallouer(G3);
    Grille_vider(G4);   Grille_desallouer(G4);
    Grille_vider(G5);   Grille_desallouer(G5);
    Grille_vider(G6);   Grille_desallouer(G6);
    Grille_vider(G7);   Grille_desallouer(G7);
    Grille_vider(G8);   Grille_desallouer(G8);
    Grille_vider(G9);   Grille_desallouer(G9);
    Grille_vider(G10);  Grille_desallouer(G10);

    desallouer_pion(Pion);

    endwin();
    
    printf("\nFélicitations vous avez réussi a passer les 10 niveaux,Vous méritez un cookie pour votre victoire \n");

    return 0;
}

