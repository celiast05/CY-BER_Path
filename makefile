all : exec
creerGrille.o : creerGrille.c jeu.h
  gcc -o creerGrille.o -c creerGrille.c
test_grille.o : test_grille.c jeu.h
  gcc -o test_grille.o -c main.c
jeu.o : jeu.c jeu.h
  gcc -o jeu.o -c jeu.c
exec : test_grille.o jeu.o 
  gcc test_grille.o jeu.o creerGrille.o exec
