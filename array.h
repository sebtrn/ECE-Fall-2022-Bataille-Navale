//
// Created by ti-yo on 23/11/2022.
//

#ifndef BATAILLE_NAVALE_2022_2023_ARRAY_H
#define BATAILLE_NAVALE_2022_2023_ARRAY_H
#include "header.h"

typedef struct
{
    int taille;
    int* array;
}t_DintArray;

void copyIntArray(int dest[],const int src[],int taille);
bool isInIntArray(const int src[],int val,int taille);
int getArrayIndex(const int tab[],int val,int taille);



void makeDintArray(t_DintArray* array,int valeur);
void setDintArray(t_DintArray* array, int valeur);
void appendDintArray(t_DintArray* array,int val);
void deleteDintArray(t_DintArray* array);
void DintArrayCat(t_DintArray* dst,int src[],int taille);

#endif //BATAILLE_NAVALE_2022_2023_ARRAY_H
