#include "function.h"
#include <stdio.h>
#include <stdlib.h>


int aponent()
{
	char variant = '1';
	do
	{
		printf("Выберите режим игры\n"
		"1: Игрок против игрока\n"
		"2: Игрок против компьютера\n"
		"3: Компьютер против игрока\n");
		scanf("%c%*c", &variant);
		{
			if (variant == '1') {
				printf("вы выбрали режим: Игрок против игрока\n");
				printf("Да победит сильнейший!\n");
				return 1;
			}
			if (variant == '2') {
				printf("вы выбрали режим: Игрок против компьютера. Человек ходит первым компьтер вторым\n");
				printf("Да победит умнейший!\n");
				return 2;
			}
			if (variant == '3') {
				printf("вы выбрали режим: Компьютер против игрока. Компьютер ходит первым, человек ходит вторым.\n");
				printf("Да победит хитрейший!\n");
				return 3;
			} else {
				printf("!НЕПРАВИЛЬНЫЙ ВВОД!\n");
			}
		}
	}while (variant != '1' || variant != '2' || variant != '3' || variant != 'q');
	return 0;
}

int correct_move(int Num, int Count)
{
	printf("Num = %d", Num);
	if (Num < 1 || Num > 10 || Num > Count) {
		//printf("\n!!!ОШИБКА!!!\n!БЕРИТЕ НЕ БОЛЬШЕ, ЧЕМ УКАЗАНО!\n");
		return 0;
	}
	return 1;
}

void input_move(int gamemod, int Player)
{
	if(gamemod == 1)
		printf("\nХОД ИГРОКА %d\nВведите количество спичек от 1 до 10: \n", Player);
	else
		printf("\nХОД ЧЕЛОВЕКА\nВведите количество спичек от 1 до 10: \n");
}

int player_move(int Num, int Count, int correct)
{
	if (correct == 1) {
		Count -= Num;
	}
	return Count;
}

int comp_move(int* Num, int Count)
{
	printf("\nХОД КОМПЬЮТЕРА\n");
	if (*Num > Count) {
		*Num = Count;
	}
	Count -= *Num;
	return Count;
}

void clean()
{
	system("clear");
}

void rules(char variant)
{
	do {
		printf("Если хотите узнать правила, то нажмите Y\nЕсли хотите начать "
		"игру, то нажмите N\n");
		scanf("%c%*c", &variant);
		{
			if (variant == 'y' || variant == 'Y') {
				printf("Приветсвую в игре '100 Спичек'\nПРАВИЛА: На столе 100 "
				"спичек, нужно брать НЕ МЕНЬШЕ 1 и НЕ БОЛЬШЕ 10\n");
				printf("Запрещается ввод символов, которые не являются "
				"числами\nПроигрывает тот, кто забирает последнюю "
				"спичку\n");
				printf("!ХОРОШЕЙ ИГРЫ!\n");
				break;
			}
			if (variant == 'n' || variant == 'N') {
				printf("!ХОРОШЕЙ ИГРЫ!\n");
				break;
			} else {
				printf("!НЕПРАВИЛЬНЫЙ ВВОД!\n");
			}
		}
	} while (variant != 'y' || variant != 'n');
}