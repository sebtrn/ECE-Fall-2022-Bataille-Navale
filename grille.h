#ifndef BATAILLE_NAVALE_2022_2023_GRILLE_H
#define BATAILLE_NAVALE_2022_2023_GRILLE_H

#include "player.h"
#include "header.h"
#include "game.h"

void displayGrid(t_game* game,DISPLAYMODE mode);
char displayCell(t_game* game,DISPLAYMODE mode,PLAYERTYPE p_type,int cellPos);
void displayGrid2(t_game* game,DISPLAYMODE mode,int i,char lettre,int ligne);

#endif //BATAILLE_NAVALE_2022_2023_GRILLE_H
