#ifndef BATAILLE_NAVALE_2022_2023_HEADER_H
#define BATAILLE_NAVALE_2022_2023_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>

#define tailleGrille 15
#define NbCases 225
#define NbDirections 2
#define defaultValue (-1)
#define nbJoueurs 2

#define taillePorteAvion 7
#define tailleCroiseur 5
#define tailleDestroyer 3
#define tailleSousMarin 1

#define nbPorteAvion 1
#define nbCroiseur 2
#define nbDestroyer 3
#define nbSousMarin 4
#define nbBateaux 10

#define lightRange 4

#define maxStr 100

enum DIRECTION {HORIZONTAL , VERTICAL};
typedef enum DIRECTION DIRECTION;
enum SHIPTYPE {PORTEAVION = 'P',CROISEUR = 'C',SOUSMARIN = 'S',DESTROYER = 'D'};
typedef enum SHIPTYPE SHIPTYPE;

enum PLAYERTYPE {PLAYER,COMPUTER};
typedef enum PLAYERTYPE PLAYERTYPE;

enum DISPLAYMODE {NONVISIBLE , VISIBLE};
typedef enum DISPLAYMODE DISPLAYMODE;

enum MOUVEMENT{NORD = 1 ,SUD , EST,OUEST};
typedef enum MOUVEMENT MOUVEMENT;

enum ACTION{TIRER,ECLAIRER,DEPLACER};
typedef enum ACTION ACTION;

enum MOVESMADE{NOTHING = ' ',FALL_IN_WATER = 'E',HIT_BOAT='T'};
typedef enum MOVESMADE MOVESMADE;
#endif //BATAILLE_NAVALE_2022_2023_HEADER_H
