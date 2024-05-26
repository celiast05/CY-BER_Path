
Projet MEF2 groupe G
# PROJET CY-BER PATH

![photo projet](https://github.com/celiast05/Projet/blob/main/image.img)

##  Table des matières

- [Introduction](#Introduction)
- [Pré-requis](#Pré-requis)
- [Guide d'installation](#Guide-d'installation)
- [Guide d'utilisation](#Guide-d'utilisation)
- [Structure du Projet](#Structure-du-projet)
- [Auteurs](#Auteurs)
  
## Introduction 📝

Notre projet est un jeu qui se joue à 2 joueurs ou plusieurs. Le but du jeu est de faire en sorte que les robots puissent atteidre leurs cibles avec le moins de déplacement possible. Pour cela, c'est à l'utilisateur de saisir le nombre de mouvements qu'il souhaite effectuer en début de partie. Une fois le nombre de mouvements indiquer par chacun des joueurs, c’est le joueur avec le nombre de mouvements le plus bas qui doit jouer. Par la suite notre programme se charge de compter le nombre de mouvements effectuer jusqu'à ce que le robot atteigne la cible. Le gagnant du jeu est la personne qui obtient le plus grand score à la fin d’un nombre de manches fixé à l’avance.


## Pré-requis

- GCC
- Make

## Guide d'installation 📔 

```bash
### Clonez le dépôt
git clone https://github.com/celiast05/CY-BER_Path.git 

### Accédez au répertoire du projet
cd CY-BER_Path

### Compilez le projet
make
```

## Guide d'utilisation 📋

### Exécuter le programme
./CY-BER_Path

### Exemple d'utilisation
Notre procédure pour placer les cibles aléatoirement.

```bash
void placeTarget (Grid gridGame, Coordinate coord){
    int createTarget = 0;
    while (createTarget < 18){
        coord = createCoordinate(rand() % gridGame.width, rand() % gridGame.height);
        if (validePlacementTarget(gridGame, coord)){
           gridGame.cases[coord.y][coord.x].type = TARGET;
           gridGame.cases[coord.y][coord.x].id = 1 + createTarget;
           createTarget++;
        }
    }
}
```

## Structure du projet 
La structure de notre projet est la suivante :

- CY-BER_Path/                             # Code source
- main.c                                   # Point d'entrée du programme
- game.c                                   # Exemple de module
  └── gcc –c createGrid.c -o createGrid.o  # Fichier d'en-tête
  └── gcc –c test_grid.c -o test_grid.o
  └── gcc –c game.c -o game.o
- gcc createGrid.o test_grid.o game.c -o   # Exécution 
- game.h                                   # Header commun
- Makefile                                 # Compilation
- README.md                                # Ce fichier


## Auteurs 👤  
👤 ASTIER Célia

👤 BIDI SINDA Grace

👤 NJANKOU NANA Charmelle

