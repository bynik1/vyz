#include <biblio/biblio.h>
#include <blocks/blocks.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BASIC "\033[0m"

void logo()
{
    printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''"
           "\n");
    printf("##    #  ###  ##   ##        #####      ##     ##   ##  ######   "
           "\n");
    printf("# #   #   #   # # # #      ##          #  #    # # # #  #        "
           "\n");
    printf("#  #  #   #   #  #  #      #  ####     ####    #  #  #  #####    "
           "\n");
    printf("#   # #   #   #     #      #     #    #    #   #     #  #        "
           "\n");
    printf("#    ##  ###  #     #       #####    #      #  #     #  ######   "
           "\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
           "\n");
}
void developers()
{
    printf("\t%s--Developers: %s\n", YELLOW, BASIC);
    printf("\tStudents of SIBSUTIS (1 course):\n");
    printf("\t1. Pavel Borinskyy\n");
    printf("\t2. Yaroslav Vorotnikov\n");
    printf("\t3. Ruslan Pirakov\n");
    printf("\tAll rights received.\n");
}

short set_game(char mode, char players)
{
    short win = 0;
    char* name1 = malloc(16 * sizeof(char));
    char* name2 = malloc(16 * sizeof(char));
    if (players == 'b' && (mode == 'a' || mode == 'b')) {
        printf("\t%s--What is your name?: %s\n", YELLOW, BASIC);
        printf("\tPlayer1 name: ");
        scanf("%s%*c", name1);
        if (strlen(name1) > 15)
            return -1;
        printf("\t%s--What is your friend name?: %s\n", YELLOW, BASIC);
        printf("\tPlayer2 name: ");
        scanf("%s%*c", name2);
        if (strlen(name2) > 15) {
            free(name1);
            free(name2);
            return -1;
        }
    }
    if (players == 'a' && (mode == 'a' || mode == 'b')) {
        printf("\t%s--What is your name?: %s\n", YELLOW, BASIC);
        printf("\tPlayer name: ");
        scanf("%s%*c", name1);
        if (strlen(name1) > 15) {
            free(name1);
            free(name2);
            return -1;
        }
    }

    if (mode == 'a') {
        if (players == 'a') {
            game_title(mode);
            win = bot_mode(name1, 'a');
            if (win != 0)
                score_write(score, "Classic", name1, "Robot", win);
        }
        if (players == 'b') {
            game_title(mode);
            win = player_mode(name1, name2, 'a');
            if (win != 0)
                score_write(score, "Classic", name1, name2, win);
        }
        if (players == 'c') {
            game_title(mode);
            bot_mode("Guest", 'c');
        }
    }

    else if (mode == 'b') {
        if (players == 'a') {
            game_title(mode);
            win = bot_mode(name1, 'b');
            if (win != 0)
                score_write(score, "Custom", name1, "Robot", win);
        }
        if (players == 'b') {
            game_title(mode);
            win = player_mode(name1, name2, 'b');
            if (win != 0)
                score_write(score, "Custom", name1, name2, win);
        }
        if (players == 'c') {
            game_title(mode);
            bot_mode("Guest", 'd');
        }
    } else {
        free(name1);
        free(name2);
        return 1;
    }

    return 0;
}

char set_gamemode()
{
    char mode;
    printf("\t%s--Set the gamemode: %s\n", YELLOW, BASIC);
    printf("\ta) Classic mode \n");
    printf("\tb) Custom mode \n");
    printf("\t   Choose: ");
    scanf("%c%*c", &mode);
    return mode;
}
char set_players()
{
    char players;
    printf("\t%s--Set type of game: %s\n", YELLOW, BASIC);
    printf("\ta) Play with bot \n");
    printf("\tb) Play with friend \n");
    printf("\t   Choose: ");
    scanf("%c%*c", &players);
    return players;
}

void scores(struct Scoreboard* score)
{
    printf("\t%s--Scoreboard for current session: %s\n", YELLOW, BASIC);
    printf("\tN\t    Mode                  P1        P1Wins                P2  "
           "     P2Wins\n");
    for (short i = 0; i < 16; i++) {
        printf("\t%d\t%8s   \t%16s     \t%d|\t%16s     \t%d\n",
               score[i].count,
               score[i].gamemode,
               score[i].names1,
               score[i].wins1,
               score[i].names2,
               score[i].wins2);
    }
    if (score[0].count != 0) {
        char save;
        printf("If you want to save this session in text file, press +\n");
        scanf("%c%*c", &save);
        if (save == '+') {
            file_save(score);
        }
    }
}
