#include "menu.h"
#include "windows.h"

void Menu(t_game* game)
{
    if(game->leaveMenu == true)
        return;
    printf("Cliquez sur les touches de clavier qui correspondent !\n");
    printf("1. Jouer une partie contre l'ordinateur\n");
    printf("2. Charger une partie\n");
    printf("3. Aide\n");
    printf("4. Quitter\n\n");

    while(game->leaveMenu == false && game->isExit == false)
    {
        if (GetAsyncKeyState(VK_NUMPAD1))
        {
            game->leaveMenu = true;
        }
        else if (GetAsyncKeyState(VK_NUMPAD2))
        {
            FILE* f = fopen("navale","r");
            chargeGame(game,f);
            printf("La partie a ete charge !\n");
            game->leaveMenu = true;
        }
        else if (GetAsyncKeyState(VK_NUMPAD3))
        {

                printf("********** Regles de la bataille navale **********\n\n"
                       "Chaque joueur dispose d'une flotte de 10 navires. L'objectif est de detruire l'integralite de la flotte ennemie.\n"
                       "Une fois la partie lancee, vous aurez le choix de tirer un missile, lancer une fusee eclairante ou bien deplacer \nun de vos navires en ecrivant une coordonnee precise.\n"
                       "Votre attaque sera visible sur la grille droite en affichant 'T' ou 'E' si un navire a ete touche ou non.\n"
                       "Il est possible d'activer le 'mode visible' qui vous permet d'afficher la position des navires ennemis.\n"
                       "Le joueur dont les navires sont encore debout a la fin de la partie l'emporte.\n\n"
                       "********** Regles de la bataille navale **********\n\n");

            {
                printf("********** Touches du clavier **********\n\n"
                       "Entrez 'deplacer' pour deplacer un de vos navires dans une des directions proposees.\n"
                       "Entrez 'eclairer' pour lancer une fusee eclairante sur la coordonnee choisie.\n"
                       "Entrez 'tirer' pour tirer sur la coordonnee choisie.\n"
                       "Entrez au clavier la coordonnee de la case visee. Exemple : 'A8'\n"
                       "Appuyez sur 'v' pour le mode visible. Vous pourrez ainsi voir la position exacte des navires ennemis.\n"
                       "Appuyez sur 'echap' pour quitter la partie en cours.\n\n"
                       "********** Touches du clavier **********\n\n");
            }
            system("PAUSE");
            system("CLS");
            Menu(game);
        }
        else if (GetAsyncKeyState(VK_NUMPAD4))
        {
            printf("Le jeu a ete quitte.\n");
            game->isExit = true;
        }
        else
        {
            //printf("Erreur. Veuillez choisir un chiffre entre 1 et 4.\n\n");
            //Menu();
            //return 1;
        }
    }
    system("CLS");
}