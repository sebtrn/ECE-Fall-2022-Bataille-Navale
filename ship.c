#include "ship.h"
#include "array.h"
#include "saisie.h"

//Inialise un bateau en fonction du type de bateau et du joueur
t_ship* initShip(SHIPTYPE type,PLAYERTYPE p_type)
{
    t_ship* ship = (t_ship*)malloc(sizeof(t_ship));
    ship->p_type = p_type;
    ship->hasSunk = false;
    switch (type) {
        case PORTEAVION:
            ship->pos = (int*)malloc(sizeof(int)*taillePorteAvion);
            ship->destroyedPos = calloc(taillePorteAvion,sizeof(int));
            ship->shipLength = taillePorteAvion;
            ship->type = PORTEAVION;
            break;
        case SOUSMARIN:
            ship->pos = (int*)malloc(sizeof(int)*tailleSousMarin);
            ship->destroyedPos = calloc(tailleSousMarin,sizeof(int));
            ship->shipLength = tailleSousMarin;
            ship->type = SOUSMARIN;
            break;
        case CROISEUR:
            ship->pos = (int*)malloc(sizeof(int)*tailleCroiseur);
            ship->destroyedPos = calloc(tailleCroiseur,sizeof(int));
            ship->shipLength = tailleCroiseur;
            ship->type = CROISEUR;
            break;
        case DESTROYER:
            ship->pos = (int*)malloc(sizeof(int)*tailleDestroyer);
            ship->destroyedPos = calloc(tailleDestroyer,sizeof(int));
            ship->shipLength = tailleDestroyer;
            ship->type = DESTROYER;
            break;
        default:
            break;
    }
    return ship;
}

//Libère la mémoire
void freeShip(t_ship* ship)
{
    free(ship->pos);
    free(ship->destroyedPos);
}

//Retourne un bateau des deux grilles en fonction de la position donnée en argument
t_ship* getShipFromArray(t_ship* shipArray[2*nbBateaux],int indice)
{
    for(int i = 0; i < 2*nbBateaux;i++)
    {
        if(isInIntArray(shipArray[i]->pos,indice,shipArray[i]->shipLength) == 1)
            return shipArray[i];
    }
    return NULL;
}


//Renvoie true si on peut déplacer un bateau en fontion de la direction(Nord,Sud,EST,Ouest),false sinon
bool canMoveShip(t_ship* shipArray[2*nbBateaux],int startPos,int nextPos,DIRECTION b_direction)
{
    t_pos s_pos;
    t_pos n_pos;
    getCoords(&s_pos.ligne,&s_pos.colonne,startPos);
    getCoords(&n_pos.ligne,&n_pos.colonne,nextPos);

    if(b_direction == HORIZONTAL)
    {
        if(s_pos.ligne != n_pos.ligne)
            return false;
    }
    else
    {
        if(s_pos.colonne != n_pos.colonne)
            return false;
    }

    if(!(nextPos >= 0 && nextPos <= NbCases-1) || getShipFromArray(shipArray,nextPos) != NULL)
        return false;
    else
        return true;
}


//Déplace un bateau en fonction de la direction (NORD,SUD,EST,OUEST)
bool moveShip(t_ship* shipArray[2*nbBateaux],int shipPos,MOUVEMENT mouv)
{
    t_ship* ship = getShipFromArray(shipArray,shipPos);
    int nextIndex;
    switch (mouv) {
        case NORD:
            nextIndex = ship->pos[0] - tailleGrille;
            if(!canMoveShip(shipArray,ship->pos[0],nextIndex,ship->direction))
                return false;
            for(int i = 0; i < ship->shipLength;i++)
            {
                ship->pos[i] -= tailleGrille;
            }
            break;
        case SUD:
            nextIndex = ship->pos[ship->shipLength-1] + tailleGrille;
            if(!canMoveShip(shipArray,ship->pos[ship->shipLength-1],nextIndex,ship->direction))
                return false;
            for(int i = 0; i < ship->shipLength;i++)
            {
                ship->pos[i] += tailleGrille;
            }
            break;
        case OUEST:
            nextIndex = ship->pos[0] - 1;
            if(!canMoveShip(shipArray,ship->pos[0],nextIndex,ship->direction))
                return false;
            for(int i = 0; i < ship->shipLength;i++)
            {
                ship->pos[i] -= 1;
            }
            break;
        case EST:
            nextIndex = ship->pos[ship->shipLength-1] + 1;
            if(!canMoveShip(shipArray,ship->pos[ship->shipLength-1],nextIndex,ship->direction))
                return false;
            for(int i = 0; i < ship->shipLength;i++)
            {
                ship->pos[i] += 1;
            }
            break;
        default:
            return false;
    }
    return true;
}

void hitShip(t_ship* ship,int cellPos)
{
    int count = 0;
    int dPos = getArrayIndex(ship->pos,cellPos,ship->shipLength);
    ship->destroyedPos[dPos] = defaultValue;
    for(int i = 0; i < ship->shipLength;i++)
    {
        if(ship->destroyedPos[i] == defaultValue)
            count++;
    }
    if(count == ship->shipLength){
        ship->hasSunk = true;
        for(int i = 0;i < ship->shipLength;i++)
        {
            ship->pos[i] = defaultValue;
        }
    }

}

char displayShipState(t_ship* ship,int cellPos)
{
    int dPos = getArrayIndex(ship->pos,cellPos,ship->shipLength);
    if(ship->destroyedPos[dPos] == defaultValue)
        return HIT_BOAT;
    else
        return ship->type;
}

//On sauvegarde les attributs des bateaux
void saveShip(t_ship* ship,FILE* file)
{
    fwrite(ship->pos,sizeof(int)*ship->shipLength,1,file);
    fwrite(ship->destroyedPos,sizeof(int)*ship->shipLength,1,file);
    fwrite(&ship->hasSunk,sizeof(bool),1,file);
    fwrite(&ship->p_type,sizeof(int),1,file);
}

//On charge les attributs des bateaux
void chargeShip(t_ship* ship,FILE* file)
{
    fread(ship->pos,sizeof(int)*ship->shipLength,1,file);
    fread(ship->destroyedPos,sizeof(int)*ship->shipLength,1,file);
    fread(&ship->hasSunk,sizeof(bool),1,file);
    fread(&ship->p_type,sizeof(int),1,file);
}