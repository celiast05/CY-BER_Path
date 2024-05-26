#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Case createCase (TypeCase type, int id,bool wallRight, bool wallBottom) {
    Case case1;
    case1.type = type;
    case1.id = id;
    case1.wallRight = wallRight;
    case1.wallBottom = wallBottom;
    return case1; // permet de d'initialiser les composantes de la structure Case pour case1
}

Grid createGridEmpty (int widht, int height){
    Grid gridGame;
    gridGame.width = widht;
    gridGame.height = height; // permet de d'initialiser les composantes de la structure Grille pour grilleJeu
    gridGame.cases = malloc(height * sizeof(Case*));
    if (gridGame.cases == NULL){
        printf ("Erreur d'allocation");
        exit (1);
    } // on cree le tableau 2D de la structure Grille

    for(int y = 0; y < height; y++){
        gridGame.cases[y] = malloc(widht * sizeof(Case));
        if (gridGame.cases[y] == NULL){
            printf ("Erreur d'allocation");
            exit (2);
        }

       for(int x=0; x<widht; x++){
            gridGame.cases[y][x] = createCase(EMPTY, -1, x == widht-1, y == height-1); // -1 car pas d'id 
        } 
    }
    return gridGame;
}

Coordinate createCoordinate (int x, int y) {
    Coordinate coord;
    coord.x = x;
    coord.y = y;
    return coord; // permet d'initialiser les composantes de la structure Coordonnee pour coord
}

void displayCase (Case case1) {
    switch (case1.type){ // on affiche en fonction du contenu d'une case 
        case EMPTY :
          printf ("  ");
          break;

        case ROBOT :
          couleur("32");
          printf ("%d ", case1.id);
          couleur("0");
          break;
        
        case TARGET :
          couleur("36");
          printf ("%d", case1.id);
          couleur("0");
          if (case1.id < 10){
            printf (" ");
          }
          break;
    }

   // printf ("|"); //condition ? siTrue : siFalse -> (case1.murDroit ? "|" : " ")

}

void displayGrid (Grid gridGame){
    for (int x = 0; x < gridGame.width; x++){
        printf ("+--"); //affiche le bord superieur de la grille
    }
    printf ("+\n"); // affiche le coin supérieur droit de la grille

    for (int y = 0; y < gridGame.height; y++){
        printf("|");

        for (int x = 0; x < gridGame.width; x++){
            displayCase(gridGame.cases[y][x]);
            if (gridGame.cases[y][x].wallRight && x != gridGame.width-1){
                couleur("31");
                printf("|");
                couleur("0");
            }
            else {
                printf("|");
            }
        }
        printf ("\n+");

        for (int x = 0; x < gridGame.width; x++){
            if (gridGame.cases[y][x].wallBottom && y != gridGame.height - 1){
                couleur("31");
                printf("--");
                couleur("0");
                printf("+");
            }
            else {
                printf("--+");
            }
            /*if(grilleJeu.cases[y][x].murBas) printf("--+");
            else printf("  +"); // 3 espaces pour que ce soit alignés */
        }
        printf ("\n"); 
    }
}

bool validePlacementTarget(Grid gridGame, Coordinate target) {
    // Vérifier si la coordonnée est sur les bords de la grille
    if (target.x == 0 || target.x == gridGame.width - 1 || target.y == 0 || target.y == gridGame.height - 1 ) {
        return false;
    }

    // Vérifier la case de la cible et les cases adjacentes pour s'assurer qu'il n'y a pas de cible déjà présente
    for (int k = -1; k <= 1; k++) {
        for (int j = -1; j <= 1; j++) {
            int newX = target.x + k;
            int newY = target.y + j;

            // Vérifier si les nouvelles coordonnées sont à l'intérieur de la grille
            if (newX >= 0 && newX < gridGame.height && newY >= 0 && newY < gridGame.width) {
                // Vérifier si la case contient déjà une cible
                if (gridGame.cases[newY][newX].type == TARGET) {
                    return false;
                }
            }
        }
    }

    // Si toutes les conditions sont satisfaites, le placement est valide
    return true;
}

void placeTarget (Grid gridGame, Coordinate targetCoord[]){
    int createTarget = 0;
    while (createTarget < 18){
        Coordinate coord = createCoordinate(rand() % gridGame.width, rand() % gridGame.height);
        if (validePlacementTarget(gridGame, coord)){
           gridGame.cases[coord.y][coord.x].type = TARGET;
           gridGame.cases[coord.y][coord.x].id = 1 + createTarget;
           targetCoord[createTarget] = coord;
           createTarget++;
        }
    }
}

bool validePlacementRobot(Grid gridGame, Coordinate robot){
  if (gridGame.cases[robot.y][robot.y].type == ROBOT || gridGame.cases[robot.y][robot.y].type == TARGET){
    return false;
  }
  return true;
}

void placeRobot(Grid gridGame, Coordinate robotCoord[]){
    int createRobot = 0;
    while (createRobot < 4){
        Coordinate coord = createCoordinate(rand() % gridGame.width, rand() % gridGame.height);
        if (validePlacementRobot(gridGame, coord)){
            gridGame.cases[coord.y][coord.x].type = ROBOT;
            gridGame.cases[coord.y][coord.x].id = 1 + createRobot;
            robotCoord[createRobot] = coord;
            createRobot++;
        }
    }
}


void placeWall(Grid gridGame) {
    for (int i = 0; i < 2; i++) {  // Bord supérieur
        int x = rand() % gridGame.width;
        if (x < gridGame.width - 1) {
            gridGame.cases[0][x].wallRight = true;
        }
    }
    for (int i = 0; i < 2; i++) { // Bord inférieur
        int x = rand() % gridGame.width;
        if (x < gridGame.width - 1) {
            gridGame.cases[gridGame.height - 1][x].wallRight = true;
        }
    }
    for (int i = 0; i < 2; i++) { // Bord gauche
        int y = rand() % gridGame.height;
        if (y < gridGame.height - 1) {
            gridGame.cases[y][0].wallBottom = true;
        }
    }
    for (int i = 0; i < 2; i++) { // Bord droit
        int y = rand() % gridGame.height;
        if (y < gridGame.height - 1) {
            gridGame.cases[y][gridGame.width - 1].wallBottom = true;
        }
    }
    
    for (int y = 0; y < gridGame.height; y++){
        for (int x = 0; x < gridGame.width; x++){
            if (gridGame.cases[y][x].type == TARGET){
                int wall = rand() % 4;
                int newWall;
                do {
                    newWall = rand() % 4;
                }
                while (newWall == wall || newWall == wall + 2 || newWall == wall - 2);

                if (wall == NORTH || newWall == NORTH) {
                    if (y > 0) {
                        gridGame.cases[y - 1][x].wallBottom = true;
                    }
                }
                if (wall == EAST || newWall == EAST) {
                    if (x < gridGame.width - 1) {
                        gridGame.cases[y][x].wallRight = true;
                    }
                }
                if (wall == SOUTH || newWall == SOUTH) {
                    if (y < gridGame.height - 1) {
                        gridGame.cases[y][x].wallBottom = true;
                    }
                }
                if (wall == WEST || newWall == WEST) {
                    if (x > 0) {
                        gridGame.cases[y][x - 1].wallRight = true;
                    }
                }
            }
        }
    }
        
}
