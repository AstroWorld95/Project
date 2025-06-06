#include <stdio.h>
#include <stdlib.h>
#include "Pion.h"
#include "Grille.h"
#include <time.h>
#include <ncurses.h>

Grille * Grille_initialiser(int n, int m){

    Grille* L=malloc(sizeof(Grille));
    if(L==NULL){
        printf("Place non alloué\n");
        exit(2);
    }
    L->n=n;
    L->m=m;

    L->tab=malloc(sizeof (enum  grille* )* n );
    for (int i=0;i<n;i++)
    {
        L->tab[i]=malloc (sizeof(enum grille) * m );
        }
        return L;

    }


void Grille_desallouer(Grille* L){
    
    for (int i=0;i<L->n;i++)
    {
        free(L->tab[i]);
        
        }
        
    free(L->tab);
    free(L);
    L = NULL;

}

void Grille_vider (Grille *L){


 for (int i=0;i<L->n;i++)
    {
        for (int j=0;j<L->m;j++)
        L->tab[i][j]=RIEN;
    }


}

void Grille_redessiner (Grille* L) {
    printf("\33[2J"); /* Efface tout l'écran */
    printf("\33[H");  /* Place le curseur en haut à gauche */
    for (int i = 0; i < L->n; i++) {
        for (int j = 0; j < L->m; j++) {
            switch (L->tab[i][j]) {
                case RIEN:   printf("\33[40m  "); break;  // Noir
                case MUR:    printf("\33[42m  "); break;  // Vert
                case PION:   printf("\33[41m  "); break;  // Rouge
                case PIEGE:  printf("\33[44m  "); break;  // Bleu
                case TRESOR: printf("\33[43m  "); break;  // Jaune
            }
        }
        printf("\033[0m\033[1E"); // <-- Saut de ligne à la fin de CHAQUE ligne
    }
    fflush(stdout);
}



void position_mur(Grille *L) {
    for (int i = 0; i < L->n; i++) {
        for (int j = 0; j < L->m; j++) {
            
            if (i == 0 || i == L->n - 1 || j == 0 || j == L->m - 1) {
                L->tab[i][j] = MUR;
            } else {
                L->tab[i][j] = RIEN;
            }
        }
    }
}

void position_piege(Grille *L){
    int x = rand()%(L->n-2)+1;
    int y= rand()%(L->m-2)+1;

    L->tab[x][y]=PIEGE;

}

void position_tresor(Grille *L){
    int x = rand()%(L->n-2)+1;
    int y= rand()%(L->m-2)+1;

    L->tab[x][y]=TRESOR;

}

// Fonction pour charger la grille depuis un fichier
Grille* Grille_charger_fichier (const char* nom_fichier, int* pion_x, int* pion_y){
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur ouverture fichier");
        exit(2);
    }

    int lignes, colonnes;
    if (fscanf(fichier, "%d %d\n", &lignes, &colonnes) != 2) {
        fprintf(stderr, "Format du fichier incorrect.\n");
        fclose(fichier);
        exit(2);
    }

    Grille* G = Grille_initialiser(lignes, colonnes);
    if (!G) {
        fclose(fichier);
        exit(2);
    }

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            int c = fgetc(fichier);

            while (c == '\n' || c == '\r') {
                c = fgetc(fichier);
                if (c == EOF) break; 
            }


 /*fgetc(fichier) revoie EOF si il y'a une erreur de lecture ou si la fin du fichier est atteinte*/
            if (c == EOF) {
                fprintf(stderr, "Fichier trop court, ligne %d colonne %d.\n", i, j);//stderr standar error
                Grille_desallouer(G);
                fclose(fichier);
                exit(2);
            }

            switch (c) {
                case 'M':
                    G->tab[i][j] = MUR;
                    break;
                case 'Q':
                    G->tab[i][j] = PIEGE;
                    break;
                case 'B':
                    G->tab[i][j] = TRESOR;
                    break;
                case 'P':
                    G->tab[i][j] = RIEN; // On remplace le P par du vide
                    *pion_x = i;
                    *pion_y = j;
                    break;
                case ' ':
                default:
                    G->tab[i][j] = RIEN;
                    break;
            }
        }
    }

    fclose(fichier);

    return G;
}


