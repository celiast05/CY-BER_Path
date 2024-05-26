#include <stdio.h>
#include "game.h"
#include <time.h>
#include <stdlib.h>



int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int widht = rand() % (MAX - MIN + 1) + MIN;
  int height = rand() % (MAX - MIN + 1) + MIN;
  int nbPlayer, testPlayer, difficult, testDifficult, reflexion, testMovement, playerMin;
  int nbHalf = 1;
  int moveCount = 0;
  char input, testInput;
  Coordinate *robotCoord = malloc(4 * sizeof(Coordinate));
  if (robotCoord == NULL){
    printf("Erreur d'allocation");
    exit (1);
  }
  Coordinate *targetCoord = malloc(18 * sizeof(Coordinate));
  if (targetCoord == NULL){
    printf("Erreur d'allocation");
    exit(2);
  }
  Direction direction;

  do {
    printf ("Saisisser le nombre de joueurs : ");
    testPlayer = scanf("%d", &nbPlayer);
    vide_file();
  }
  while (nbPlayer < 2 || testPlayer == 0);

  int *movement = malloc(nbPlayer * sizeof(int));
  if (movement == NULL){
    printf ("Erreur d'allocation");
    exit(3);
  }
  int *points = malloc(nbPlayer * sizeof(int));
  if (points == NULL){
    printf("Erreur d'allocation");
    exit (4);
  }
  int movementAchieved = 0;

 do {
    printf ("Saisisser le niveau de difficulté souhaité (1: facile, 2: moyen, 3: difficile) : ");
    testDifficult = scanf("%d", &difficult);
    vide_file();
  }
  while (difficult < 1 || difficult > 3|| testDifficult == 0);


  Grid grid = createGridEmpty(widht, height);
  Grid copy;
  placeTarget(grid, targetCoord);
  placeRobot(grid, robotCoord);
  placeWall(grid);
  displayGrid(grid);
  copyGrid(grid, copy); 
  
  printf("Manche %d/5\n", nbHalf);

  while (nbHalf < MAXHALF){
    nbHalf++;
    int robotAlea = rand() % 4;
    int targetAlea = rand() % 18;
    int idRobot = grid.cases[robotCoord[robotAlea].y][robotCoord[robotAlea].x].id;
    int idTarget = grid.cases[targetCoord[targetAlea].y][targetCoord[targetAlea].x].id;

    printf ("Robot numéro %d\n", idRobot);
    printf ("Cible numéro %d\n", idTarget);

    int duration = timeReflexion(difficult);
    time_t start = time(NULL);
    printf("Vous avez %d secondes pour réfléchir à vos mouvements...", duration);
    while (difftime(time(NULL), start) < duration){

    }
    printf ("Temps écoulé !");
    printf("\033[2J\033[H");

    for (int i = 0; i < nbPlayer ; i++){
      do {
        printf ("Joueur %d entrer le nombre de mouvement nécessaire : ", i+1);
        testMovement = scanf("%d", &movement[i]);
        vide_file();
      }
      while (movement[i] < 1 || testMovement == 0);
    }

    playerMin = actifPlayer(movement, nbPlayer);
    printf (" C'est au joueur %d de jouer\n", playerMin + 1);
    displayGrid(copy);

    while (1){

      input = getDirection();

      if(input == 'q'){
        break;
      }

      direction = chooseDirection(input);
      movementRobot(grid, direction, robotCoord[robotAlea], &moveCount);
      displayGrid(grid);
      if(robotCoord[playerMin].x == targetCoord[targetAlea].x && robotCoord[playerMin].y == targetCoord[targetAlea].y){
        if (movementAchieved == movement[playerMin]){
          points[playerMin] = points[playerMin] + 2;
          break;
        }
        else if (movementAchieved < movement[playerMin]){
          points[playerMin] = points[playerMin] - 1;
          break;
        }
        else if(movementAchieved > movement[playerMin]){
          for (int i = 0; i < nbPlayer; i++){
            if (i != nbPlayer){
              points[i] = points[i] + 1;
            }
          }
          
        }
      }
      
    }
  }

  int meilleurScore = points[0];
  int gagnant = 0;
  for (int i = 1; i < nbPlayer; i++) {
    if (points[i] > meilleurScore) {
      meilleurScore = points[i];
      gagnant = i;
    }
  }

  printf ("Le gagnant est le joueur %d avec %d points", gagnant + 1, meilleurScore);

  for (int i = 0; i < grid.height; i++) {
    free(grid.cases[i]);

  }
  free(grid.cases);
  free(robotCoord);
  free(targetCoord);
  free(movement);
  free(points);

  return 0;
}
