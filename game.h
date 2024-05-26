#ifndef JEU_H
#define JEU_H
#include <stdbool.h>

#define MAX 20
#define MIN 15
#define MAXHALF 5
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

Case createCase (TypeCase type, int id,bool wallRight, bool wallBottom);
Grid createGridEmpty (int width, int height);
Coordinate createCoordinate(int x, int y);
void displayCase (Case case1);
void displayGrid (Grid gridGame);
bool validePlacementTarget(Grid gridGame, Coordinate target);
void placeTarget (Grid gridGame, Coordinate targetCoord[]);
bool validePlacementRobot(Grid gridGame, Coordinate robot);
void placeRobot(Grid gridGame, Coordinate robotCoord[]);
void placeWall (Grid gridGame);

void vide_file();
Case getCase(Grid grid, Coordinate coords);
bool canMove (Grid grille, Coordinate coords, Direction direction);
char getDirection();
Direction chooseDirection (char input);
int timeReflexion(int difficultLevel);
int actifPlayer (int *movement, int player);
void movementRobot(Grid gridGame, Direction direction, Coordinate robot, int *moveCount);
void copyGrid (Grid gridGame, Grid copy);

#endif
