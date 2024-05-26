#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void vide_file(){ // Sert à éviter les faute de frappe
  while(getchar()!='\n'){
  }
}

Case getCase(Grid gridGame, Coordinate coord){
    return gridGame.cases[coord.y][coord.x];
}

bool canMove (Grid gridGame, Coordinate coord, Direction direction){
    if(coord.x < 0 || coord.y < 0 || coord.x >= gridGame.width || coord.y >= gridGame.height) { //on sort de la grille
        return false;
    }

    switch (direction) {
        case NORTH :
          return canMove(gridGame, createCoordinate(coord.x, coord.y-1), SOUTH);
        case WEST : 
          return canMove(gridGame, createCoordinate(coord.x-1, coord.y), EAST);
        case SOUTH : 
          return ! getCase(gridGame, coord).wallBottom; //! = ne pas; inverse bool
        case EAST : 
          return ! getCase(gridGame, coord).wallRight;
    }
    // si ne marche pas rajouter return true 
}

char getDirection (){
    char input;

    printf ("Entree une direction et appuyer sur Entree (N pour NORTH, E pour EAST, S pour SOUTH, W pour WEST, q pour quitter):\n");
    scanf ("%c", &input);
    if (input != 'N' && input != 'E' && input != 'S' && input != 'W' && input != 'Q') {
        vide_file();
        return getDirection(); // Demande à nouveau une direction à l'utilisateur
    }
    return input;
}

Direction chooseDirection (char input){
    Direction direction;
    switch (input){
        case 'N' : 
          direction = NORTH;
          break;
        case 'S' :
          direction = SOUTH;
          break;
        case 'E' :
          direction = EAST;
          break;
        case 'O' :
          direction = WEST;
          break;
    }
    return direction;
}

int timeReflexion(int difficultLevel){
    int reflexion;
    switch (difficultLevel){
        case 1 : 
          reflexion = 30;
          break;
        case 2 : 
          reflexion = 20;
          break;
        case 3 : 
          reflexion = 10;
          break;
        default :
          reflexion = 20;
          break;
    }
    return reflexion;
}



int actifPlayer (int *movement, int player){
    int min = 0;
    for (int i = 1; i < player; i++) {
        if (movement[i] < movement[min]) {
            min = i;
        }
    }
    return min;
}

void movementRobot(Grid gridGame, Direction direction, Coordinate robot, int *moveCount){
    int robotId = gridGame.cases[robot.y][robot.x].id;
    while (canMove(gridGame, robot, direction)){
        gridGame.cases[robot.y][robot.x].type = EMPTY;
        gridGame.cases[robot.y][robot.x].id = 0;
        switch (direction){
            case  NORTH :
              robot.y = robot.y - 1;
              break;
            case EAST :
              robot.x = robot.x + 1;
              break;
            case SOUTH :
              robot.y = robot.y + 1;
              break;
            case WEST :
              robot.x = robot.x - 1;
              break;
        }
        (*moveCount)++;
        gridGame.cases[robot.y][robot.x].type = ROBOT;
        gridGame.cases[robot.y][robot.x].id = robotId;

    }
}


void copyGrid (Grid gridGame, Grid copy){
    copy.height = gridGame.height;
    copy.width = gridGame.width;
    copy.cases = malloc(copy.height * sizeof(Case*));
    if (copy.cases == NULL){
        printf ("Erreur d'allocation");
        exit (1);
    }
    for (int y = 0; y < copy.height; y++){
        copy.cases[y] = malloc(copy.width * sizeof(Case));
        if (copy.cases[y] == NULL){
        printf ("Erreur d'allocation");
        exit (2);
        }
        for (int x = 0; x < copy.width; x++){
            copy.cases[y][x] = gridGame.cases[y][x];
        }
    }
}
