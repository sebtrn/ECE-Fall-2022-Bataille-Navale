//
// Created by ti-yo on 20/11/2022.
//

#ifndef BATAILLE_NAVALE_2022_2023_PLAYER_H
#define BATAILLE_NAVALE_2022_2023_PLAYER_H

#include "header.h"
#include "ship.h"
#include "array.h"

typedef struct t_player
{
    t_ship* playerShips[nbBateaux];
    PLAYERTYPE p_type;
    int flashRocket;
}t_player;


t_ship* getShipFromPlayer(t_player* player,int pos);

t_player* initPlayer(PLAYERTYPE type,t_DintArray* array);
void freePlayer(t_player* player);
void savePlayer(t_player* player,FILE* file);
void chargePlayer(t_player* player,FILE* file);

#endif //BATAILLE_NAVALE_2022_2023_PLAYER_H
