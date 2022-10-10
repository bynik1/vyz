#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int Count, Num, Player, correct, check_letter, var, Num1;
	char variant;
	int gamemod;
	clean();
	rules(variant);
	srand(time(NULL));
	Player = 1;
	while (1) {
		gamemod = aponent();
		if(gamemod == 1)
		{
			Player = 1;
			Count = 100;
			do {
				printf("\nКОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
				if (Player == 1) {
					while (1) {
						input_move(gamemod, Player);
						do {
							check_letter = scanf("%d", &Num);
							while (getchar() != '\n')
								;
							if (check_letter == 1) {
								if (Num == 1)
									printf("Человек 1 взял %d спичку\n", Num);
								if (Num >= 2 && Num <= 4)
									printf("Человек 1 взял %d спички\n", Num);
								if (Num >= 5 && Num <= 10)
									printf("Человек 1 взял %d спичек\n", Num);
								continue;
							} else
							printf("%s","\n!!!ОШИБКА!!!\nВводите только цифры\n");
							printf("КОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
						} while (check_letter != 1);
						correct = correct_move(Num, Count);
						if (correct == 1) {
							break;
						}
					}
					Count = player_move(Num, Count, correct);
					Player = 2;
				} else 	if (Player == 2) {
					while (1) {
						input_move(gamemod, Player);
						do {
							check_letter = scanf("%d", &Num);
							while (getchar() != '\n')
								;
							if (check_letter == 1) {
								if (Num == 1)
									printf("Человек 2 взял %d спичку\n", Num);
								if (Num >= 2 && Num <= 4)
									printf("Человек 2 взял %d спички\n", Num);
								if (Num >= 5 && Num <= 10)
									printf("Человек 2 взял %d спичек\n", Num);
								continue;
							} else
								printf("%s","\n!!!ОШИБКА!!!\nВводите только цифры\n");
							printf("КОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
						} while (check_letter != 1);
						correct = correct_move(Num, Count);
						if (correct == 1) {
							break;
						}
					}
					Count = player_move(Num, Count, correct);
					Player = 1;
				}
			} while (Count > 0);
			if (Player == 1) {
				printf("Победил игрок 1\n");
			} else {
				printf("Игрок 2 победил\n");
			}
		}
		else if(gamemod == 2)//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		{
			Player = 1;
			Count = 100;
			do {
				printf("\nКОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
				if (Player == 1) {
					while (1) {
						input_move(gamemod, Player);
						do {
							check_letter = scanf("%d", &Num);
							while (getchar() != '\n')
								;
							if (check_letter == 1) {
								if (Num == 1)
									printf("Человек взял %d спичку\n", Num);
								if (Num >= 2 && Num <= 4)
									printf("Человек взял %d спички\n", Num);
								if (Num >= 5 && Num <= 10)
									printf("Человек взял %d спичек\n", Num);
								continue;
							} else
								printf("%s","\n!!!ОШИБКА!!!\nВводите только цифры\n");
							printf("КОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
						} while (check_letter != 1);
						correct = correct_move(Num, Count);
						if (correct == 1) {
							break;
						}
					}
					Count = player_move(Num, Count, correct);
					Player = 2;
				} else if (Player == 2) {
					Num = 11 - Num;
					Count = comp_move(&Num, Count);
					if (Num == 1)
						printf("Компьютер взял %d спичку\n", Num);
					if (Num >= 2 && Num <= 4)
						printf("Компьютер взял %d спички\n", Num);
					if (Num >= 5 && Num <= 10)
						printf("Компьютер взял %d спичек\n", Num);
					Player = 1;
				}
			} while (Count > 0);
			if (Player == 1) {
				printf("!!!ЧЕЛОВЕК ВЫИГРАЛ!!!\n");
			} else {
				printf("!!!КОМПЬЮТЕР ПОБЕДИЛ!!!\n");
			}	
		}
		else//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		{
			Player = 2;
			Count = 100;
			var = 0;
			Num1 = 0;
			Num = 0;
			do {
				printf("\nКОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
				if (Player == 1) {
					while (1) {
						input_move(gamemod, Player);
						do {
							check_letter = scanf("%d", &Num);
							while (getchar() != '\n')
								;
							if (check_letter == 1) {
								if (Num == 1)
									printf("Человек взял %d спичку\n", Num);
								if (Num >= 2 && Num <= 4)
									printf("Человек взял %d спички\n", Num);
								if (Num >= 5 && Num <= 10)
									printf("Человек взял %d спичек\n", Num);
								continue;
							} else
								printf("%s","\n!!!ОШИБКА!!!\nВводите только цифры\n");
							printf("КОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
						} while (check_letter != 1);
						correct = correct_move(Num, Count);
						if (correct == 1) {
							break;
						}
					}
					Count = player_move(Num, Count, correct);
					Player = 2;
				} else if (Player == 2) {
					if(var == 0){
                        if(Num1 == 0 || Num+Num1 == 11){
								Num1 = 1;
						}else if(Num+Num1!=11){
							Num1=11-1-Num;
							var = 1;
						}
					}else if(var == 1){
						Num1 = 11 - Num;
					}
					Num = Num1;
					Count = comp_move(&Num, Count);
					if (Num == 1)
						printf("Компьютер взял %d спичку\n", Num);
					if (Num >= 2 && Num <= 4)
						printf("Компьютер взял %d спички\n", Num);
					if (Num >= 5 && Num <= 10)
						printf("Компьютер взял %d спичек\n", Num);
					Player = 1;
				}
			} while (Count > 0);
			if (Player == 1) {
				printf("!!!ЧЕЛОВЕК ВЫИГРАЛ!!!\n");
			} else {
				printf("!!!КОМПЬЮТЕР ПОБЕДИЛ!!!\n");
			}
		}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		do {
			printf("\nВаши действия?\nQ - ВЫХОД\nR - НАЧАТЬ ЗАНОВО\n");
			scanf("%c%*c", &variant);
			{
				if (variant == 'q' || variant == 'Q') {
					exit(0);
				}
				if (variant == 'r' || variant == 'R') {
					clean();
					{
						break;
					}
				} else {
					printf("\n!НЕПРАВИЛЬНЫЙ ВВОД!\n");
				}
			}
		} while (variant != 'r' || variant != 'q');
	}
	return 0;
}
