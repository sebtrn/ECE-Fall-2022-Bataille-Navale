#include "player.h"

//Génère une direction et une position aléatoire en fonction du type de bateau(taille)
void randomPlacement(int buffer[],DIRECTION* shipDirection,int taille)
{
    int direction = rand()%NbDirections;
    *shipDirection = direction;
    int ligne;
    int colonne;
    int indice;
    if(direction == HORIZONTAL)
    {
        colonne = rand()%(tailleGrille - taille + 1);
        ligne = rand()%tailleGrille;
        indice = tailleGrille*ligne + colonne;
        for(int i = 0; i < taille;i++)
        {
            buffer[i] = indice;
            indice++;
        }
    }
    else if(direction == VERTICAL)
    {
        colonne = rand()%tailleGrille;
        ligne = rand()%(tailleGrille - taille + 1);
        indice = tailleGrille*ligne  + colonne;
        for(int i = 0; i < taille;i++)
        {
            buffer[i] = indice+tailleGrille*i;
        }
    }
}

//Renvoie vraie si un bateau ne peut être à la position donnée en paramètre
bool findCase(t_DintArray* array,const int src[],int taille)
{
    for(int i = 0;i < array->taille; i++)
    {
        if(isInIntArray(src,array->array[i],taille))
            return true;
    }
    return false;
}

//Place les bateaux sur la grille en prenant compte de la position des bateaux déjà placés
void findPlace(t_DintArray* array,t_ship* ship)
{
    int taille = ship->shipLength;
    int* randomCoords = malloc(sizeof(int)*taille);
    do
    {
        randomPlacement(randomCoords,&ship->direction,taille);
    }while(findCase(array,randomCoords,taille) == true);
    DintArrayCat(array,randomCoords,taille);
    copyIntArray(ship->pos,randomCoords,taille);
}

//On place tous les bateaux du joueur aléatoirement
void initShipPlayer(t_player* joueur,t_DintArray* array)
{
    for(int i = 0; i < nbBateaux;i++)
    {
        findPlace(array,joueur->playerShips[i]);
    }
}

//Retourne l'adresse du bateau d'un joueur donnée en paramètre situé à la position donnée en paramètre
t_ship* getShipFromPlayer(t_player* player,int pos)
{
    for(int i = 0;i<nbBateaux;i++)
    {
        t_ship* ship = player->playerShips[i];
        if(isInIntArray(ship->pos,pos,ship->shipLength) == true)
            return ship;
    }
    return NULL;
}

//On initialise tous les bateaux du joueur
t_player* initPlayer(PLAYERTYPE type,t_DintArray* array)
{
    t_player* joueur = (t_player*)malloc(sizeof(t_player));
    joueur->p_type = type;
    joueur->flashRocket = lightRange;
    for(int i = 0; i < nbBateaux;i++)
    {
        if(i < nbPorteAvion)
            joueur->playerShips[i] = initShip(PORTEAVION,type);
        else if (i-(nbPorteAvion) < nbCroiseur)
            joueur->playerShips[i] = initShip(CROISEUR,type);
        else if (i-(nbPorteAvion+nbCroiseur) < nbDestroyer)
            joueur->playerShips[i] = initShip(DESTROYER,type);
        else
            joueur->playerShips[i] = initShip(SOUSMARIN,type);
    }
    //srand(time(NULL));
    initShipPlayer(joueur,array);
    return joueur;
}

//On sauvegarde les attributs du joueur
void savePlayer(t_player* player,FILE* file)
{
    //fwrite(&player->p_type,sizeof(int),1,file);
    for(int i = 0; i < nbBateaux;i++)
    {
        saveShip(player->playerShips[i],file);
    }
    fwrite(&player->flashRocket,sizeof(int),1,file);
}

//On charge les attributs du joueur
void chargePlayer(t_player* player,FILE* file)
{
    for(int i = 0; i < nbBateaux;i++)
    {
        chargeShip(player->playerShips[i],file);
    }
    fread(&player->flashRocket,sizeof(int),1,file);
}


//Libère la mémoire allouée dynamiquement de tous les bateaux du joueur
void freePlayer(t_player* player)
{
    for(int i = 0; i < nbBateaux;i++)
    {
        freeShip(player->playerShips[i]);
    }
    free(player);
}
