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
        case NORTH : return canMove(gridGame, createCoordinate(coord.x, coord.y-1), SOUTH);
        case WEST : return canMove(gridGame, createCoordinate(coord.x-1, coord.y), EAST);
        case SOUTH : return ! getCase(gridGame, coord).wallBottom; //! = ne pas; inverse bool
        case EAST : return ! getCase(gridGame, coord).wallRight;
    }
    // si ne marche pas rajouter return true 
}

Direction chooseDirection (char touche){
    switch (touche){
        case 'N' : 
          return NORTH;
        case 'S' :
          return SOUTH;
        case 'E' :
          return EAST;
        case 'O' : 
          return WEST;
    }
    return touche;
}

void incrementationRobot (Grid gridGame, Coordinate robot, Direction mouvement){
switch (mouvement) {
        case NORTH:
            while (robot.y > 0 && gridGame.cases[robot.y - 1][robot.x].wallBottom == false) {
                robot.y--;
            }
            break;
        case EAST:
            while (robot.x < gridGame.width - 1 && gridGame.cases[robot.y][robot.x].wallRight == false) {
                robot.x++;
            }
            break;
        case SOUTH:
            while (robot.y < gridGame.height - 1 && gridGame.cases[robot.y][robot.x].wallBottom == false) {
                robot.y++;
            }
            break;
        case WEST:
            while (robot.x > 0 && gridGame.cases[robot.y][robot.x - 1].wallRight == false) {
                robot.x--;
            }
            break;
    }
}

int actifPlayer (int *mouvement, int player){
    int min = 0;
    for (int i = 1; i < player; i++) {
        if (mouvement[i] < mouvement[min]) {
            min = i;
        }
    }
    return min;
}

void mooveRobot(Grid grille, Coordinate robot, int mouvements) {
    // Boucle pour effectuer chaque mouvement
    for (int i = 0; i < mouvements; i++) {
        // Afficher la grille après chaque mouvement
        printf("Grille après le mouvement %d:\n", i + 1);
        afficherGrille(grille);

        // Demander à l'utilisateur de saisir la direction du mouvement
        int direction;
        printf("Entrez la direction du mouvement pour le robot (0: Nord, 1: Est, 2: Sud, 3: Ouest): ");
        scanf("%d", &direction);

        // Déplacer le robot dans la direction spécifiée
        incrementationRobot(grille, robot, direction);
    }
}

void timeDisplacement(Grid gridGame, int difficultLevel, int player, int *movement) {
    Coordinate robot;
    Coordinate target;
    bool foundRobot = false;
    bool foundCible = false;
    int duration;
    switch (difficultLevel) {
        case 1: // Facile
          duration = 30;
          break;
        case 2: // Moyen
          duration = 20;
          break;
        case 3: // Difficile
          duration = 10;
          break;
        default:
          duration = 20; //par defaut dificulte moyenne
    }
    while (!foundRobot) {
        robot = createCoordinate(rand() % gridGame.width, rand() % gridGame.height);
        if (gridGame.cases[robot.y][robot.x].type == ROBOT) {
            foundRobot = true;
        }
    }

    while (!foundCible) {
        target = createCoordinate(rand() % gridGame.width, rand() % gridGame.height);
        if (gridGame.cases[target.y][target.x].type == TARGET) {
            foundCible = true;
        }
    }

    printf("Robot numéro %d\n", gridGame.cases[robot.y][robot.x].id);
    printf("Cible numéro %d\n", gridGame.cases[target.y][target.x].id);

    time_t start = time(NULL);
    printf("Vous avez %d secondes pour réfléchir...\n", duration);

    while (difftime(time(NULL), start) < duration) {
         // Wait for the specified duration
    }
    printf("\033[H\033[J"); // Effacer l'écran
    printf("Temps écoulé! \n");
     
    for (int i = 0; i < player; i++) {
        printf("Joueur %d, entrez votre nombre de mouvements: ", i + 1);
        scanf("%d", &movement[i]);
        mooveRobot(gridGame, robot, movement[i]);

    }
}

int askNbPlayer (){
    int nbPlayer, testPlayer;
    do {
        printf ("Saisisser le nombre de joueurs :");
        testPlayer = scanf ("%d", &nbPlayer);
        vide_file();
    }
    while (nbPlayer < 2 || testPlayer == 0);
    return nbPlayer;
}

int askDifficultLevel(){
    int level, testLevel;
    do{
        printf ("Choisisser une niveau de difficulté (1: facile, 2: moyen, 3: difficile)");
        testLevel = scanf("%d", &level);
        vide_file();
    }
    while (testLevel == 0 || level < 1 || level > 3);
    return level;
}
