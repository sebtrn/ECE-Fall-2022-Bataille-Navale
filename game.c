#include "game.h"

//Retourne un bateau en fonction de la position (indice)
t_ship* getShip(t_game* game, int indice)
{
    for(int i = 0; i < 2*nbBateaux;i++)
    {
        if(isInIntArray(game->shipArray[i]->pos,indice,game->shipArray[i]->shipLength) == 1)
            return game->shipArray[i];
    }
    return NULL;
}

//Initialise le jeu (Grille/Joueur/Bateaux)
t_game* initGame()
{

    t_game* game = malloc(sizeof(t_game)) ;
    makeDintArray(&game->array,defaultValue);
    t_player* p_array[nbJoueurs];

    //On initialise et place les bateaux des joueurs
    p_array[PLAYER] = initPlayer(PLAYER,&game->array);
    p_array[COMPUTER] = initPlayer(COMPUTER,&game->array);

    //
    game->isExit = false;
    game->isModeVisible = false;
    game->tour = PLAYER;
    game->leaveMenu = false;

    for(int i = 0; i < tailleGrille*tailleGrille;i++)
    {
        game->cellGrid[i].isVisible = false;
        game->cellGrid[i].moveType = NOTHING;
        game->cellGrid[i].ship = NULL;
    }

    setGameInfo(game,p_array);

    return game;
}

void setGameInfo(t_game* game,t_player* player[nbJoueurs])
{
    for(int i = 0; i < nbJoueurs;i++)
    {
        game->playerArray[i] = player[i];
    }
    for(int i = 0; i < 2*nbBateaux;i++)
    {
        if(i < nbBateaux)
        {
            game->shipArray[i] = game->playerArray[PLAYER]->playerShips[i];
        }
        else
        {
            game->shipArray[i] = game->playerArray[COMPUTER]->playerShips[i-nbBateaux];
        }
    }
    updateGrid(game);
}

//Mets à jour notre grille
void updateGrid(t_game* game)
{
    for(int i = 0; i < NbCases;i++)
    {
        game->cellGrid[i].ship = getShip(game,i);
    }
}

//Détermine si un joueur à gagner
void gagne(t_game* game)
{
    int count = 0;
    if(game->tour == PLAYER)
    {
        for(int i = 0 ; i < nbBateaux;i++)
        {
            if(game->playerArray[COMPUTER]->playerShips[i]->hasSunk == true)
                count++;
        }
        if(count == nbBateaux){
            printf("Vous avez gagne BRAVO !\n");
            game->isExit = true;
        }
    }
    else
    {
        for(int i = 0 ; i < nbBateaux;i++)
        {
            if(game->playerArray[PLAYER]->playerShips[i]->hasSunk == true)
                count++;
        }
        if(count == nbBateaux){
            printf("Vous avez perdu contre l'ordinateur !\n");
            game->isExit = true;
        }
    }
}

//Mets à jour la grille dans le cas d'une action
void updateGridOnAction(t_game* game,int cellPos,ACTION actionType)
{
    t_cell* cell = &game->cellGrid[cellPos];
    int startPos = (cellPos - (tailleGrille+1))%NbCases;
    int nbRockets = game->playerArray[PLAYER]->flashRocket;

    switch (actionType) {
        case TIRER:
            if(cell->ship != NULL)
            {
                if(cell->ship->p_type == game->tour){
                    printf("Vous ne pouvez pas tirer sur votre propre navire !\n");
                    return;
                }
                hitShip(cell->ship,cellPos);
                cell->moveType = HIT_BOAT;
            }
            else
            {
                cell->moveType = FALL_IN_WATER;
            }
            break;
        case ECLAIRER:
            if(nbRockets <= 0)
            {
                printf("Vous n'avez plus de fusee eclairante !\n");
                return;
            }
            for(int i = 0; i < lightRange;i++)
            {
                for(int j = 0; j < lightRange;j++)
                {
                    game->cellGrid[j+startPos].isVisible = true;
                }
                startPos = (startPos + tailleGrille)%NbCases;
            }
            game->playerArray[PLAYER]->flashRocket = nbRockets - 1;
            printf("Il vous reste %d fusee eclairante !\n",(nbRockets-1));
            break;
        default:
            break;
    }
    gagne(game);
    updateGrid(game);
}

//Affiche les informations d'une cellule (coup jouée,bateau ...)
char displayCellState(t_cell* cell,int cellPos)
{
    if(cell->isVisible && cell->ship != NULL && cell->ship->p_type != PLAYER)
        return displayShipState(cell->ship,cellPos);
    else
    {
        return cell->moveType;
    }
}

//Libère la mémoire (Grille,Bateaux,Joueurs)
void freeGame(t_game* game)
{
    for(int i = 0; i < nbJoueurs;i++)
    {
        freePlayer(game->playerArray[i]);
    }
    deleteDintArray(&game->array);
}


//Sauvegarde toutes les données(Bateaux,Joueurs)
void saveGame(t_game* game,FILE* file)
{
    savePlayer(game->playerArray[PLAYER],file);
    savePlayer(game->playerArray[COMPUTER],file);
    for(int i = 0; i < NbCases;i++)
    {
        t_cell* cell = &game->cellGrid[i];
        saveCell(cell,file);
    }
    fwrite(&game->tour,sizeof(int),1,file);
}

//Charge toutes les données(Bateaux,Joueurs)
void chargeGame(t_game* game,FILE* file)
{
    chargePlayer(game->playerArray[PLAYER],file);
    chargePlayer(game->playerArray[COMPUTER],file);

    for(int i = 0; i < NbCases;i++)
    {
        chargeCell(&game->cellGrid[i],file);
    }
    fread(&game->tour,sizeof(int),1,file);
    updateGrid(game);
}

//Sauvegarde les coups joués dans les cases
void saveCell(t_cell* cell,FILE* file)
{
    fwrite(&cell->moveType,sizeof(int),1,file);
    fwrite(&cell->isVisible,sizeof(bool),1,file);
}

//Charge les coups joués dans les cases
void chargeCell(t_cell* cell,FILE* file)
{
    fread(&cell->moveType,sizeof(int),1,file);
    fread(&cell->isVisible,sizeof(bool),1,file);
}


//Choisis une coordonée au hasard pour tirer (IA)
void computerMove(t_game* game,t_player* computer)
{
    int c_pos;
    do {
        c_pos = rand()%NbCases;
        updateGridOnAction(game,c_pos,TIRER);
    }while(getShipFromPlayer(computer,c_pos) != NULL);
}
