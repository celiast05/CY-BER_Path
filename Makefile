all : exec
createGrid.o : createGrid.c game.h
  gcc -o createGrid.o -c createGrid.c
test_grid.o : test_grid.c game.h
  gcc -o test_grid.o -c main.c
game.o : game.c game.h
  gcc -o game.o -c game.c
exec : test_grid.o game.o createGrid.o
  gcc test_grid.o game.o createGrid.o exec
