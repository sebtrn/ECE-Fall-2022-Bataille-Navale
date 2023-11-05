#ifndef BATAILLE_NAVALE_2022_2023_GAME_H
#define BATAILLE_NAVALE_2022_2023_GAME_H

#include "header.h"
#include "array.h"
#include "player.h"


typedef struct
{
    t_ship* ship;
    MOVESMADE moveType;
    int isVisible;
}t_cell;

typedef struct
{
    t_player* playerArray[nbJoueurs];
    t_ship* shipArray[2*nbBateaux];
    t_DintArray array;
    t_cell cellGrid[tailleGrille*tailleGrille];
    bool isExit;
    bool isModeVisible;
    bool leaveMenu;
    int tour;
}t_game;


t_game* initGame();
void setGameInfo(t_game* game,t_player* player[nbJoueurs]);
void updateGrid(t_game* game);
t_ship* getShip(t_game* game,int indice);
void freeGame(t_game* game);
void saveGame(t_game* game,FILE* file);
void chargeGame(t_game* game,FILE* file);


//CellGrid Functions
void updateGridOnAction(t_game* game,int cellPos,ACTION actionType);

void saveCell(t_cell* cell,FILE* file);
void chargeCell(t_cell* cell,FILE* file);
char displayCellState(t_cell* cell,int cellPos);

//AI Functions
void computerMove(t_game* game,t_player* computer);

#endif //BATAILLE_NAVALE_2022_2023_GAME_H
