#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
int main()
{
	int Count, Num, Player, correct, check_letter;
	char variant;
	clean();
	rules(variant);
	srand(time(NULL));
	//printf("Num = %d\n", Num);
	Player = 1;
	while (1) {
		Count = 100;
		do {
			printf("\nКОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
			if (Player == 1) {
				while (1) {
					Num = input_turn(Num);// ?
					//printf("Num = %d\n", Num);
					do {
						check_letter = scanf("%d", &Num);//если Введена цифра то 1 иначе 0
						//printf("check_letter = %d\n", check_letter);//проверка
						while (getchar() != '\n');//пока не нажмёшь энтер програмаа не пойдёт впереёд
						if (check_letter == 1) {//для падежей
							if (Num == 1)
								printf("Человек взял %d спичку\n", Num);
							if (Num >= 2 && Num <= 4)
								printf("Человек взял %d спички\n", Num);
							if (Num >= 5 && Num <= 10)
								printf("Человек взял %d спичек\n", Num);
							//continue;//?
						} else
							printf("%s","\n!!!ОШИБКА!!!\nВводите только цифры\n");
						printf("КОЛИЧЕСТВО СПИЧЕК: %d\n", Count);
					} while (check_letter != 1);//пока check_letter не будет равно 1 будет выполняться do
					correct = correct_turn(Num, Count);
					if (correct == 1) {
						break;
					}
				}
				Count = player_turn(Num, Count, correct);
				Player = 2;
			} else if (Player == 2) {
				Num = rand() % 10 + 1;
				Count = comp_turn(&Num, Count);
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
		do {
			printf("\nВаши действия?\nQ - ВЫХОД\nR - НАЧАТЬ ЗАНОВО\n");
			scanf("%c", &variant);//убрал %*с
			{
				if (tolower(variant) == 'q') {//сделал Tolower
					exit(0);
				}
				if (tolower(variant) == 'r') {//сделал Tolower
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