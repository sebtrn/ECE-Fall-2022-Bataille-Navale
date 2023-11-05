#include "saisie.h"
#include "windows.h"


//Convertie les coordonées visuelles(a0 à o14) en indice(0 à 224)
int CoordsToIndex(const char* coords)
{
    char start = 'a';
    int ligne = coords[0] - start;
    int colonne = atoi(&coords[1]);
    int indice = colonne + tailleGrille*ligne;
    return indice;
}

//Convertie un indice entre 0 et 224 en coordonnée en visuelle(a0 à o14)
void IndexToCoords(char* buffer,int indice)
{
    char coords[4];
    int ligne = (int)indice/tailleGrille;
    int colonne = indice%tailleGrille;
    char lettre = 'a' + ligne;
    sprintf(coords,"%c%d",lettre,colonne);
    strcpy(buffer,coords);
}

void getCoords(int* ligne , int* colonne,int indice)
{
    *ligne = (int)indice/tailleGrille;
    *colonne = indice%tailleGrille;
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

//Blindage des entrées utilisateurs
//Source: openclassroom
int lire(char *chaine, int longueur) {
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            *positionEntree = '\0';
            for (int i = 0; i < strlen(chaine); i++)
                chaine[i] = (char) tolower(chaine[i]);
        } else {
            viderBuffer();
        }
        return 1;
    } else {
        viderBuffer();
        return 0;
    }
}

int choixCardinal(t_ship* ship)
{
    char p_cardinal[maxStr];
    if(ship->direction == VERTICAL)
    {
        printf("Nord ou Sud ?");
    }
    else if(ship->direction == HORIZONTAL){
        printf("Ouest ou Est ?");
    }
    lire(p_cardinal,maxStr);

    if(strcmp(p_cardinal,"nord") == 0)
        return NORD;
    else if(strcmp(p_cardinal,"sud") == 0)
        return SUD;
    else if(strcmp(p_cardinal,"ouest") == 0)
        return OUEST;
    else if(strcmp(p_cardinal,"est") == 0)
        return EST;
    else
        return  0;
}

void ActionFromUserCoords(t_game* game,const char* str,ACTION choixAction)
{
    int cellPos = CoordsToIndex(str);
    t_ship* ship = getShipFromPlayer(game->playerArray[PLAYER],cellPos);
    switch (choixAction) {
        case DEPLACER:
            if(ship == NULL){
                printf("Erreur bateau non trouvee!\n");
                return;
            }
            if(!moveShip(game->shipArray,cellPos, choixCardinal(ship)))
                printf("Mouvement impossible\n");
            break;
        default:
            updateGridOnAction(game,cellPos,choixAction);
            return;
    }
    updateGrid(game);
}

int ActionTypeF(t_game* game,char* str)
{
    ACTION choixAction = 0;
    if(strcmp(str,"tirer") == 0)
    {
        printf("Coordonnee du tir:");
        choixAction = TIRER;
    }
    else if(strcmp(str,"eclairer") == 0)
    {
        printf("Coordonnee de la fusee eclairante:");
        choixAction = ECLAIRER;
    }
    else if(strcmp(str,"deplacer") == 0)
    {
        printf("Coordonnee du bateau:");
        choixAction = DEPLACER;
    }
    else
        return 0;
    lire(str,maxStr);
    ActionFromUserCoords(game,str,choixAction);
    game->tour = !game->tour;
    return 1;
}

void saisieUtilisateur(t_game* game)
{
    char str[maxStr];
    printf("quitter,continuer,menu,mode visible,sauvegarder ou charger ?");
    lire(str,maxStr);
    if(strcmp(str,"sauvegarder") == 0)
    {
        FILE* f = fopen("navale","w+");
        saveGame(game,f);
        fclose(f);
    }
    else if(strcmp(str,"charger") == 0)
    {
        FILE* f = fopen("navale","r");
        chargeGame(game,f);
        fclose(f);
    }
    else if(strcmp(str,"quitter") == 0)
    {
        game->isExit = true;
    }
    else if(strcmp(str,"visible")==0)
        game->isModeVisible = !(game->isModeVisible);
    else if(strcmp(str,"menu") == 0)
    {
        game->leaveMenu = false;
    }
    else{
        do {
            printf("Type d'action (deplacer,eclairer ou tirer) ?");
            lire(str,maxStr);
        }while(ActionTypeF(game,str) == 0);
    }
}
