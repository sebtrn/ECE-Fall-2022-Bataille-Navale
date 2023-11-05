#include "grille.h"

//Affiche une cellule/case en fonction du mode (visible\Non-visible) et de la grille(joueur 1 /adversaire 2)
char displayCell(t_game* game,DISPLAYMODE mode,PLAYERTYPE p_type,int cellPos)
{
    switch (p_type) {
        case PLAYER:
            if(game->cellGrid[cellPos].ship != NULL && game->cellGrid[cellPos].ship->p_type == p_type)
                return displayShipState(game->cellGrid[cellPos].ship,cellPos);
            else
                return NOTHING;
        case COMPUTER:
            switch (mode) {
                case NONVISIBLE:
                    return displayCellState(&game->cellGrid[cellPos],cellPos);
                case VISIBLE:
                    if(game->cellGrid[cellPos].ship != NULL && game->cellGrid[cellPos].ship->p_type == p_type)
                        return displayShipState(game->cellGrid[cellPos].ship,cellPos);
                    else
                        return NOTHING;
                default:
                    return NOTHING;
            }
        default:
            break;
    }
}

//Affiche la deuxième grille
void displayGrid2(t_game* game,DISPLAYMODE mode,int i,char lettre,int ligne)
{
    int numero = 0;
    int indice = 0;
    for(int j = 0; j < 3*tailleGrille + 2;j++) {
        if (i % 2 == 0) {
            if (j == 0)
                printf(" ");
            else
                printf("-");
        } else if (i == 1) {
            if (j == 0)
                printf(" ");
            else if (j % 3 == 1)
                printf("|");
            else {
                if (j % 3 == 0 && numero < 10) {
                    printf(" %d", numero);
                    numero++;
                } else if (j % 3 == 2 && numero >= 10) {
                    printf("%d", numero);
                    numero++;
                }
            }
        } else {
            if (j == 0) {
                printf("%c", lettre);
            } else if (j % 3 == 1) {
                printf("|");
            } else if (j % 3 == 0) {
                printf(" %c", displayCell(game,mode,COMPUTER,indice+tailleGrille*ligne));
                //printf("%d\n",idx);
                indice++;
            }
        }
    }

}


//Affichage de la première grille
void displayGrid(t_game* game,DISPLAYMODE mode)
{
    char lettre = 'a';//Caratère pour les lignes
    int numero = 0;//Numéro pour les colonnes
    int indice = 0;//Position dans la grille

    for(int i = 0; i < 2*(tailleGrille + 1)+1;i++)
    {
        for(int j = 0; j < 3*tailleGrille + 2;j++)
        {
            if(i%2 == 0)
            {
                if(j == 0)
                    printf(" ");
                else
                    printf("-");
            }
            else if(i == 1)
            {
                if(j == 0)
                    printf(" ");
                else if(j%3 == 1)
                    printf("|");
                else{
                    if(j%3 == 0 && numero < 10)
                    {
                        printf(" %d",numero);
                        numero++;
                    }
                    else if(j%3 == 2 && numero >=10)
                    {
                        printf("%d",numero);
                        numero++;
                    }
                }
            }
            else
            {
                if(j == 0)
                {
                    printf("%c",lettre);
                    lettre += 1;
                }
                else if(j%3 == 1)
                {
                    printf("|");
                }
                else if(j%3 == 0)
                {
                    printf(" %c",displayCell(game,mode,PLAYER,indice));
                    //printf("%d\n",idx);
                    indice++;
                }
            }
        }
        printf("      ");
        displayGrid2(game,mode,i,lettre-1,(int)(indice-1)/tailleGrille);
        printf("\n");
    }

}



