#ifndef BATAILLE_NAVALE_2022_2023_SAISIE_H
#define BATAILLE_NAVALE_2022_2023_SAISIE_H
#include "header.h"
#include "game.h"

int CoordsToIndex(const char* coords);
void IndexToCoords(char* buffer,int indice);
void getCoords(int* ligne,int* colonne,int indice);

char getInput();

void saisieUtilisateur(t_game* game);

#endif //BATAILLE_NAVALE_2022_2023_SAISIE_H
