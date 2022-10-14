#include <biblio/biblio.h>
#include <blocks/blocks.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BASIC "\033[0m"

int main(int argc, char* argv[])
{
    char mode, players;
    char* menu = malloc(sizeof(char));
    short flag = 0;

    if (argc == 1) {
        logo();
        printf("%s Welcome to the Nim Game!\n %s", YELLOW, BASIC);
        do {
            printf("%s---------------MAIN MENU---------------%s\n",
                   YELLOW,
                   BASIC);
            printf("________1) Set the gamemode \n");
            printf("________2) Set type of the game \n");
            printf("________3) Start \n");
            printf("________4) Developers \n");
            printf("________5) Recently games\n");
            printf("________6) Exit\n");
            printf("\t%sChoose:%s ", GREEN, BASIC);
            scanf("%c%*c", menu);

            if (*menu == '1') {
                mode = set_gamemode();
            } else if (*menu == '2') {
                players = set_players();
            } else if (*menu == '3') {
                flag = set_game(mode, players);
                if (flag == 1)
                    printf("\n%sSet gamemode and players!%s\n", RED, BASIC);
                if (flag == -1)
                    printf("\n%sName max length 15!%s\n", RED, BASIC);
                printf("\n");
            } else if (*menu == '4') {
                developers();
                printf("\n");
            } else if (*menu == '5') {
                scores(score);
                printf("\n");
            } else if (*menu == '6') {
                free(menu);
                return exiting(0);
            } else {
                printf("\t%sWrong data or program is not exist%s\n",
                       RED,
                       BASIC);
            }
        } while (*menu != '6');
    } else if (argc == 2 && (!strcmp(argv[1], "--no-score"))) {
        logo();
        printf("%s Welcome to the Nim Game!\n %s", YELLOW, BASIC);
        do {
            printf("%s---------------MAIN MENU---------------%s\n",
                   YELLOW,
                   BASIC);
            printf("________1) Set the gamemode \n");
            printf("________2) Start \n");
            printf("________3) Developers \n");
            printf("________4) Exit\n");
            printf("\t%sChoose:%s ", GREEN, BASIC);
            scanf("%c%*c", menu);

            if (*menu == '1') {
                mode = set_gamemode();
            } else if (*menu == '2') {
                flag = set_game(mode, 'c');
                if (flag == 1)
                    printf("\n%sSet gamemode!%s\n", RED, BASIC);
                printf("\n");
            } else if (*menu == '3') {
                developers();
                printf("\n");
            } else if (*menu == '4') {
                free(menu);
                return exiting(0);
            } else {
                printf("\t%sWrong data or program is not exist%s\n",
                       RED,
                       BASIC);
            }
        } while (*menu != '4');
    } else {
        printf("%sLaunch the program: %s\n", RED, BASIC);
        printf("%s./main %s\n", RED, BASIC);
        printf("%s./main --no-score %s\n", RED, BASIC);
    }
}
