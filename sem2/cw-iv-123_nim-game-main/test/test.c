#include "../thirdparty/ctest.h"
#include <biblio/biblio.h>
#include <blocks/blocks.h>

CTEST(ctest, exit_check)
{
    int check = 0;
    int flag_exp = 0;
    int flag = exiting(check);
    ASSERT_EQUAL(flag_exp, flag);
}

CTEST(ctest, game_set_board)
{
    const int size = 5;
    int arr_exp[] = {1, 3, 5, 7, 9};
    int* arr = set_board('a', size);
    for (int i = 0; i < size; i++)
        ASSERT_EQUAL(arr_exp[i], arr[i]);
}

CTEST(ctest, check_empty_heap)
{
    const int size = 5;
    int arr[] = {0, 0, 0, 0, 0};
    const int nzero_exp = size;
    const int nzero = zeros(arr, size);
    ASSERT_EQUAL(nzero_exp, nzero);
}

CTEST(ctest, player_del_chips)
{
    const int wrongbegin = -4;
    const int begin = 8;
    const int minus = 3;
    const int exp_end = 5;
    const int error_end = -1;
    int end = delete_chips(begin, minus);
    ASSERT_EQUAL(exp_end, end);
    end = delete_chips(wrongbegin, minus);
    ASSERT_EQUAL(error_end, end);
}

CTEST(ctest, score_struct_write)
{
    int win = 2;
    char expmode[] = "Custom";
    char expname1[] = "VFulman";
    char expname2[] = "KleineLi";
    int victory = 1, defeat = 0;

    score_write(score, expmode, expname1, expname2, win);

    ASSERT_STR(expmode, score[0].gamemode);
    ASSERT_STR(expname1, score[0].names1);
    ASSERT_STR(expname2, score[0].names2);
    ASSERT_EQUAL(defeat, score[0].wins1);
    ASSERT_EQUAL(victory, score[0].wins2);
}

CTEST(ctest, odd_nimcheck)
{
    int size = 5;
    int nimcheck_exp[] = {0, 0, 1, 0, 1};

    int binboard[] = {/*0*/ 0, 0, 0, 0, 0,
                      /*1*/ 0, 0, 0, 0, 0,
                      /*2*/ 1, 0, 1, 1, 0,
                      /*3*/ 0, 0, 1, 0, 1,
                      /*4*/ 0, 1, 0, 0, 0};

    int* nimcheck = checking(binboard, size);

    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(nimcheck_exp[i], nimcheck[i]);
    }
}

CTEST(ctest, convert_board_in_binary)
{
    int board[] = {4, 1, 6, 4, 2};
    int size = 5;
    int bboard_exp[] = {/*0*/ 0, 0, 0, 0, 0,
                        /*1*/ 0, 0, 0, 0, 0,
                        /*2*/ 1, 0, 1, 1, 0,
                        /*3*/ 0, 0, 1, 0, 1,
                        /*4*/ 0, 1, 0, 0, 0};

    int* bboard = binary(board, size);
    for (int i = 0; i < size; i++) {
        ASSERT_EQUAL(bboard_exp[i], bboard[i]);
    }
}

CTEST(ctest, convert_binhheap_in_decimal)
{
    int chips_exp = 6;
    int heap = 2;
    int size = 5;
    int bboard[] = {/*0*/ 0, 0, 0, 0, 0,
                    /*1*/ 0, 0, 0, 0, 0,
                    /*2*/ 1, 0, 1, 1, 0,
                    /*3*/ 0, 0, 1, 0, 1,
                    /*4*/ 0, 1, 0, 0, 0};

    int chips = decimal(bboard, heap, size);

    ASSERT_EQUAL(chips_exp, chips);
}

CTEST(ctest, robot_algorithm)
{
    short h_a_d_exp[2] = {4, 3};
    short* heap_and_del;
    int nimcheck[] = {0, 0, 1, 0, 1};
    int board[] = {4, 1, 6, 4, 2};
    int size = 5;
    int bboard[] = {/*0*/ 0, 0, 0, 0, 0,
                    /*1*/ 0, 0, 0, 0, 0,
                    /*2*/ 1, 0, 1, 1, 0,
                    /*3*/ 0, 0, 1, 0, 1,
                    /*4*/ 0, 1, 0, 0, 0};

    heap_and_del = deleting_process(bboard, board, nimcheck, size);
    ASSERT_EQUAL(h_a_d_exp[0], heap_and_del[0]);
    ASSERT_EQUAL(h_a_d_exp[1], heap_and_del[1]);
}
