#include "array.h"

void makeDintArray(t_DintArray* array,int valeur)
{
    array->array = (int*)malloc(sizeof(int)*NbCases);
    array->taille = 0;
    setDintArray(array,valeur);
}

void setDintArray(t_DintArray* array, int valeur)
{
    for(int i = 0; i < array->taille;i++)
    {
        array->array[i] = valeur;
    }
}

void appendDintArray(t_DintArray* array,int val)
{
    array->array[array->taille] = val;
    array->taille++;
}

void deleteDintArray(t_DintArray* array)
{
    free(array->array);
    array->taille = 0;
}

void DintArrayCat(t_DintArray* dst,int src[],int taille)
{
    for(int i = 0; i < taille;i++)
    {
        appendDintArray(dst,src[i]);
    }
}

void copyIntArray(int dest[],const int src[],int taille)
{
    for(int i = 0;i < taille;i++)
    {
        dest[i] = src[i];
    }
}

bool isInIntArray(const int src[],int val,int taille)
{
    for(int i = 0; i < taille;i++)
    {
        if(src[i] == val)
            return true;
    }
    return false;
}

int getArrayIndex(const int tab[],int val,int taille)
{
    for(int i = 0; i < taille;i++)
    {
        if(tab[i] == val)
            return i;
    }
    return -1;
}


void printArray(int tab[],int taille)
{
    for(int i = 0;i<taille;i++)
        printf("%d: %d ",i,tab[i]);
    printf("\n");
}
