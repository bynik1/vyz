#include "function.h"
#include <stdio.h>
#include <stdlib.h>

int correct_turn(int Num, int Count)
{
	printf("Num = %d", Num);
	if (Num < 1 || Num > 10 || Num > Count) {
		//printf("\n!!!ОШИБКА!!!\n!БЕРИТЕ НЕ БОЛЬШЕ, ЧЕМ УКАЗАНО!\n");
		return 0;
	}
	return 1;
}

int input_turn(int Num)
{
	printf("\nХОД ЧЕЛОВЕКА\nВведите количество спичек от 1 до 10: \n");
	return Num;
}

int player_turn(int Num, int Count, int correct)
{
	if (correct == 1) {
		Count -= Num;
	}
	return Count;
}

int comp_turn(int* Num, int Count)
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