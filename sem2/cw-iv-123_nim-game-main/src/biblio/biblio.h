struct Scoreboard
{
    short count;
    char* gamemode;
    char* names1;
    char* names2;
    short wins1;
    short wins2;

} score[16];

/*GAME PROCESS*/
int bot_mode(char* name1, char type);
int player_mode(char* name1, char* name2, char type);
/*GAME REQUIREMENT*/
int exiting(int exit_status);
void game_title(char mode);
void score_write(
        struct Scoreboard* score, char* mode, char* p1, char* p2, short win);
void file_save(struct Scoreboard* score);
/*GAME COMPONENTS*/
int* set_board(char key, short size);
void print_board(int* example, short size);
short zeros(int* example, short size);
short delete_chips(int all, int bring);
int* binary(int* example, short size);
int decimal(int* bin, short heap, short size);
int* checking(int* binboard, short size);
short* deleting_process(int* binboard, int* board, int* check, short size);
