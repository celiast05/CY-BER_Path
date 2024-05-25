#ifndef JEU_H
#define JEU_H
#include <stdbool.h>

#define MAX 20
#define MIN 15
#define couleur(param) printf("\033[%sm",param)

typedef enum {
    NORTH,
    EAST,
    SOUTH, 
    WEST
} Direction;

typedef enum {
    EMPTY,
    ROBOT,
    TARGET
} TypeCase;

typedef struct {
    TypeCase type;
    int id;
    bool wallRight;
    bool wallBottom;
} Case;

typedef struct {
    int width;
    int height;
    Case **cases;
} Grid;

typedef struct {
    int x;
    int y;
} Coordinate;


void vide_file();

Case createCase (TypeCase type, int id,bool wallRight, bool wallBottom);
Grid createGridEmpty (int width, int height);

void displayCase (Case case1);
void displayGrid (Grid gridGame);

Coordinate createCoordinate(int x, int y);
Case getCase(Grid grid, Coordinate coords);

bool canMove (Grid grille, Coordinate coords, Direction direction);
bool validePlacementTarget(Grid gridGame, Coordinate target);
void placeTarget (Grid gridGame, Coordinate coord);
bool validePlacementRobot(Grid gridGame, Coordinate robot);
void placeRobot(Grid gridGame, Coordinate coord);
void placerWall (Grid gridGame);

Direction chooseDirection (char touche);
void incrementationRobot (Grid gridGame, Coordinate robot, Direction mouvement);
int actifPlayer (int *mouvement, int player);
void chronometrerDeplacement(Grid gridGame, int difficultLevel, int player, int *mouvement);

#endif