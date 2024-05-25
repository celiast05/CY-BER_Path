#include <stdio.h>
#include "game.h"
#include <time.h>
#include <stdlib.h>



int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int width = rand() % (MAX - MIN + 1) + MIN; // largeur
    int height = rand() % (MAX - MIN + 1) + MIN; // hauteur
    int nb_players, test_nb_players; 

    Grid grid = createGridEmpty(width, height); //CreerGrilleVide
    //grille.cases[1][4] = creeCase(CIBLE, 1, true, true);
    Coordinate coord;
    placeTarget(grid, coord);
    placeRobot(grid, coord);
    placeWalls(grid);
    displayGrid(grid);
  int duration;
  int difficult;

  do{
        printf("Combien de joueur joue ?\n");
        scanf("%d",&nb_players);
  }while(nb_players < 2 || nb_players > 4);
    printf("Choisissez un niveau de difficulté (1: facile, 2: moyen, 3: difficile): ");
    scanf("%d", &difficult);
    
    
  TimeDisplacement(grid, duration , nb_players);
    

      for (int i = 0; i < grid.width; i++) {
        free(grid.cases[i]);

     }
    free(grid.cases);
    return 0;
}

  
