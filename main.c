#include "grille.h"
#include "ship.h"
#include "player.h"
#include "menu.h"
#include "game.h"
#include "saisie.h"
#include "array.h"
#include <windows.h>

int main() {

    //Initialisation de la fonction rand()
    srand(time(NULL));

    //On initialise le jeu (Joueurs/Bateaux/Grilles)
    t_game* game = initGame();

    //Boucle du jeu
    while(game->isExit == false)
    {
        //Affichage du menu
        Menu(game);

        if(game->isExit == true)
            break;

        //Affichage de la grille en fonction du mode (visible/Non visible)
        if(game->isModeVisible)
            displayGrid(game,VISIBLE);
        else
            displayGrid(game,NONVISIBLE);

        //Tour du joueur ou de l'ordinateur pour joueur un coup
        if(game->tour == PLAYER)
        {
            printf("Au tour du joueur de jouer !\n");
            saisieUtilisateur(game);
        }
        else
        {
            printf("L'ordinateur est en train de jouer !\n");
            computerMove(game,game->playerArray[COMPUTER]);
            game->tour = !game->tour;
        }
    }

    //On libère la mémoire qu'on quitte le jeu
    freeGame(game);

    system("PAUSE");
    return 0;
}
