#ifndef BATAILLE_NAVALE_2022_2023_SHIP_H
#define BATAILLE_NAVALE_2022_2023_SHIP_H
#include "header.h"


typedef struct
{
    int ligne;
    int colonne;
}t_pos;

typedef struct t_ship
{
    int* pos;
    int* destroyedPos;
    PLAYERTYPE p_type;
    int shipLength;
    SHIPTYPE type;
    DIRECTION direction;
    bool hasSunk;
}t_ship;


t_ship* initShip(SHIPTYPE type,PLAYERTYPE p_type);
void freeShip(t_ship* ship);

bool moveShip(t_ship* shipArray[2*nbBateaux],int shipPos,MOUVEMENT mouv);
void hitShip(t_ship* ship,int cellPos);
void saveShip(t_ship* ship,FILE* file);
void chargeShip(t_ship* ship,FILE* file);
char displayShipState(t_ship* ship,int cellPos);

//int shootShip(t_ship* ship, *saisieUtilisateur);
//int detectShip();
//void choicePlayer();
#endif //BATAILLE_NAVALE_2022_2023_SHIP_H
