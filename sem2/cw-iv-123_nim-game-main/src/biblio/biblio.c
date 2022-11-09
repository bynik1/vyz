#include <biblio/biblio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BASIC "\033[0m"
#define NIMBYTE 5
#define MAXHEAPS 9

int bot_mode(char* name1, char type)
{
    /*HEAD*/
    if (type == 'a') {
        printf("\n\t%s--CLASSIC MODE (1 player) %s\n", YELLOW, BASIC);
        printf("\tName1: %s \n", name1);
    }
    if (type == 'b') {
        printf("\n\t%s--CUSTOM MODE (1 player) %s\n", YELLOW, BASIC);
        printf("\tName1: %s \n", name1);
    }
    if (type == 'c') {
        printf("\n\t%s--CLASSIC MODE (guest) %s\n", YELLOW, BASIC);
    }
    if (type == 'd') {
        printf("\n\t%s--CUSTOM MODE (guest) %s\n", YELLOW, BASIC);
    }
    /*BODY*/
    short size;
    short heap, delete;
    char h, d, s;
    short del;
    int* oddcheck = malloc(MAXHEAPS * sizeof(int));
    int* board = malloc(MAXHEAPS * sizeof(int));
    int* bin = malloc(MAXHEAPS * NIMBYTE * sizeof(int));
    short* status;

    if (type == 'a' || type == 'c') {
        size = 5;
        board = set_board('a', size);
    }

    if (type == 'b' || type == 'd') {
        do {
            printf("\nSet size for board (from 2 to 9): ");
            scanf("%c%*c", &s);
        } while (s < '2' || s > '9');

        size = s - 48;
        board = set_board('b', size);
    }

    short empty;
    while (1) {
        /*PLAYER TURN*/
        print_board(board, size);
        while (1) {
            printf("\n%sPlayer %s %s:\n", GREEN, name1, BASIC);

            printf("Choose the heap:");
            scanf("%c%*c", &h);

            if (h == 'q')
                return exiting(0);

            heap = h - 48;
            if (heap < 1 || heap > size)
                continue;

            printf("Delete the chips:");
            scanf("%c%*c", &d);
            delete = d - 48;
            del = delete_chips(board[heap - 1], delete);
            if (del == -1)
                continue;
            board[heap - 1] = del;
            /*CHECK THE GAMEEND*/
            empty = zeros(board, size);
            if (empty == size) {
                printf("Player %s wins!", name1);
                free(board);
                free(bin);
                return exiting(1);
            }
            break;
        }
        /*ROBOT TURN*/

        print_board(board, size);
        printf("\n%sRobot: %s:\n", GREEN, BASIC);
        bin = binary(board, size);
        oddcheck = checking(bin, size);
        status = deleting_process(bin, board, oddcheck, size);
        printf("Heap: %d\n", status[0]);
        printf("Deleted: %d\n", status[1]);
        /*CHECK THE GAMEEND*/
        empty = zeros(board, size);
        if (empty == size) {
            printf("Robot wins!");
            free(board);
            free(bin);
            return exiting(2);
        }
    }
}

int player_mode(char* name1, char* name2, char type)
{
    /*HEAD*/
    if (type == 'a')
        printf("\n\t%s--CLASSIC MODE (2 players) %s\n", YELLOW, BASIC);
    if (type == 'b')
        printf("\n\t%s--CUSTOM MODE (2 players) %s\n", YELLOW, BASIC);

    printf("\tName1: %s \n", name1);
    printf("\tName2: %s \n", name2);
    /*BODY*/
    short size;
    short heap, delete;
    char h, d, s;
    short del;
    short empty;
    int* board = malloc(MAXHEAPS * sizeof(int));

    if (type == 'a') {
        size = 5;
        board = set_board('a', size);
    }

    if (type == 'b') {
        do {
            printf("\nSet size for board (from 2 to 9): ");
            scanf("%c%*c", &s);
        } while (s < '2' || s > '9');

        size = s - 48;
        board = set_board('b', size);
    }
    while (1) {
        /*PLAYER1 TURN*/
        print_board(board, size);
        while (1) {
            printf("\n%sPlayer %s %s:\n", GREEN, name1, BASIC);

            printf("Choose the heap:");
            scanf("%c%*c", &h);

            if (h == 'q')
                return exiting(0);

            heap = h - 48;
            if (heap < 1 || heap > size)
                continue;

            printf("Delete the chips:");
            scanf("%c%*c", &d);
            delete = d - 48;
            del = delete_chips(board[heap - 1], delete);
            if (del == -1)
                continue;
            board[heap - 1] = del;

            empty = zeros(board, size);
            if (empty == size) {
                printf("Player %s wins!", name1);
                return exiting(1);
            }
            break;
        }

        /*PLAYER2 TURN*/
        print_board(board, size);
        while (1) {
            printf("\n%sPlayer %s %s:\n", GREEN, name2, BASIC);

            printf("Choose the heap:");
            scanf("%c%*c", &h);

            if (h == 'q')
                return exiting(0);

            heap = h - 48;
            if (heap < 1 || heap > size)
                continue;

            printf("Delete the chips:");
            scanf("%c%*c", &d);
            delete = d - 48;
            del = delete_chips(board[heap - 1], delete);
            if (del == -1)
                continue;
            board[heap - 1] = del;

            empty = zeros(board, size);
            if (empty == size) {
                printf("Player %s wins!", name2);
                return exiting(2);
            }
            break;
        }
    }
}

void game_title(char mode)
{
    if (mode == 'a') {
        printf("\n\t%s--CLASSIC MODE RULES %s\n", YELLOW, BASIC);
        printf("\tIn this mode, the chips will be laid out in a certain order. "
               "\n");
        printf("\tBelow is a board with 5 piles and chips in them. \n");
        printf("\tThe winner is the one who took the last chip from the last "
               "pile. \n");
        printf("\tThe game can be played with both a robot and a player. Have "
               "a good game! \n");
    }

    if (mode == 'b') {
        printf("\n\t%s--CUSTOM MODE RULES %s\n", YELLOW, BASIC);
        printf("\tIn this mode, the chips will be laid out in any order. \n");
        printf("\tBelow is a board with 2-9 piles and chips in them. \n");
        printf("\tMoreover, the chips are laid out randomly, which makes the "
               "game very diverse. \n");
        printf("\tThe winner is the one who took the last chip from the last "
               "pile. \n");
        printf("\tThe game can be played with both a robot and a player. Have "
               "a good game! \n");
    }
}

int exiting(int exit_status)
{
    printf("\n\t%sExiting...%s\n", GREEN, BASIC);
    return exit_status;
}

int* set_board(char key, short size)
{
    short i, chips = 1;
    int* example = malloc(size * sizeof(int));
    if (key == 'a') {
        for (i = 0; i < size; i++) {
            example[i] = chips;
            chips += 2;
        }
    }

    if (key == 'b') {
        srand(time(NULL));
        for (i = 0; i < size; i++) {
            example[i] = (rand() % 8) + 1;
        }
    }
    return example;
}

void print_board(int* example, short size)
{
    short i, j;
    printf("\n%s--BOARD %s\n", YELLOW, BASIC);
    for (i = 0; i < size; i++) {
        for (j = 0; j < example[i]; j++)
            printf("* ");
        printf(" (%d) \n", example[i]);
    }
}

short zeros(int* example, short size)
{
    short i, zeronum;
    for (i = 0; i < size; i++)
        if (example[i] == 0)
            zeronum++;
    return zeronum;
}

short delete_chips(int all, int bring)
{
    if (bring > 0 && bring <= all)
        return all - bring;
    else
        return -1;
}

void score_write(
        struct Scoreboard* score, char* mode, char* p1, char* p2, short win)
{
    short game;
    for (game = 0; game < 16; game++) {
        if (score[game].count == 0) {
            score[game].count = game + 1;
            score[game].gamemode = mode;
            score[game].names1 = p1;
            score[game].names2 = p2;
            if (win == 1) {
                score[game].wins1 = 1;
                score[game].wins2 = 0;
            }
            if (win == 2) {
                score[game].wins1 = 0;
                score[game].wins2 = 1;
            }
            break;
        }
    }
}

void file_save(struct Scoreboard* score)
{
    FILE* f;
    f = fopen("stats.log", "r+");
    if (f == NULL) {
        f = fopen("stats.log", "a+");
        fprintf(f,
                "\tN\t    Mode                  P1    P1Wins                P2 "
                "  P2Wins\n");
        fclose(f);
    }
    f = fopen("stats.log", "a+");
    for (short i = 0; score[i].count != 0; i++)
        fprintf(f,
                "\t%d\t%8s   \t%16s     \t%d|\t%16s     \t%d\n",
                score[i].count,
                score[i].gamemode,
                score[i].names1,
                score[i].wins1,
                score[i].names2,
                score[i].wins2);
    fclose(f);
}

int* binary(int* example, short size)
{
    short i, h;
    int* binboard = malloc(8 * size * sizeof(int));
    int copyexample[MAXHEAPS];
    short v;
    for (i = 0; i < size; i++)
        copyexample[i] = example[i];

    for (h = 0; h < size; h++) {
        v = 16;
        for (i = 0; i < NIMBYTE; i++) {
            if (copyexample[h] >= v) {
                binboard[i * size + h] = 1;
                copyexample[h] -= v;
            } else
                binboard[i * size + h] = 0;
            v /= 2;
        }
    }
    return binboard;
}

int* checking(int* binboard, short size)
{
    int* nim = malloc(NIMBYTE * sizeof(int));
    short heap, count, i;
    for (heap = 0; heap < NIMBYTE; heap++) {
        count = 0;
        for (i = 0; i < size; i++)
            if (binboard[heap * size + i])
                count++;
        if (count % 2 == 1)
            nim[heap] = 1;
        else
            nim[heap] = 0;
    }
    return nim;
}

short* deleting_process(int* binboard, int* board, int* nimcheck, short size)
{
    short heapset = 0;
    short index = NIMBYTE - 1;
    short flag = 0;
    short max = 1;
    short nimcheckzeros = 0;
    short lastcheck = 0;
    short heap, i;
    short* info = malloc(2 * sizeof(short));
    short dels;

    for (i = 0; i < size; i++)
        if (!nimcheck[i])
            nimcheckzeros++;

    for (i = 0; i < size; i++) {
        if (!board[i])
            lastcheck++;
        else
            heap = i;
    }

    if (nimcheckzeros != size) {
        for (heapset = 0; heapset < size; heapset++) {
            for (i = 0; i < NIMBYTE; i++) {
                if (nimcheck[i] && binboard[i * size + heapset]) {
                    if (i <= index) {
                        index = i;
                        heap = heapset;
                    }

                    break;
                }
            }
        }
    } else {
        for (heapset = 0; heapset < size; heapset++) {
            if (board[heapset] > max) {
                max = board[heapset];
                heap = heapset;
            }
        }
    }
    info[0] = heap + 1;

    if (size - lastcheck == 1) {
        board[heap] = 0;
        info[1] = 1;
    }

    else if ((nimcheckzeros != size) && (size - lastcheck != 1)) {
        for (i = 0; i < NIMBYTE; i++) {
            if (!flag && nimcheck[i] && !binboard[i * size + heap]) {
                binboard[i * size + heap] = 1;
                continue;
            }
            if (!nimcheck[i] && binboard[i * size + heap])
                flag = 1;
            if (nimcheck[i] && binboard[i * size + heap]) {
                binboard[i * size + heap] = 0;
                flag = 0;
            }
        }

        dels = board[heap];
        board[heap] = decimal(binboard, heap, size);
        info[1] = dels - board[heap];
    } else {
        board[heap] -= 1;
        info[1] = 1;
    }
    return info;
}

int decimal(int* bin, short heap, short size)
{
    int temp[NIMBYTE];
    int i, k = 0, s = 1;
    int sum = 0;

    for (i = 0; i < NIMBYTE; i++) {
        temp[i] = bin[i * size + heap];
    }

    for (i = NIMBYTE - 1; i >= 0; i--) {
        if (temp[i])
            sum += s << k;
        k++;
    }

    return sum;
}
