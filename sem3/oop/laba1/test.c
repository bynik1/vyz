#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void hangman(int n){ //функция выводящая на экран изображение виселицы
    switch (n) {
    case 9: printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_ / \\|  "); break;
    case 8: printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_ /  |  "); break;
    case 7: printf("  ____ |\n |   | |\n |   O |\n |  /|\\|\n_|_    |  "); break;
    case 6: printf("  ____ |\n |   | |\n |   O |\n |  /| |\n_|_    |  "); break;
    case 5: printf("  ____ |\n |   | |\n |   O |\n |   | |\n_|_    |  "); break;
    case 4: printf("  ____ |\n |   | |\n |   O |\n |     |\n_|_    |  "); break;
    case 3: printf("  ____ |\n |     |\n |     |\n |     |\n_|_    |  "); break;
    case 2: printf("       |\n |     |\n |     |\n |     |\n_|_    |  "); break;
    case 1: printf("       |\n       |\n       |\n       |\n___    |  "); break;
    case 0: printf("       |\n       |\n       |\n       |\n       |  "); break;
    }
}
int main()
{
    FILE* txt;
    char word[80], enterLetter[33] = {0}, scanChar;
    double buffer;
    int i, flag = 0, sizeFile = 0, rndStr, sizeWord, guessChar, guessErr = 0, countLetter = 0;
    srand(time(NULL));
    if (!(txt = fopen("slova.txt", "r+"))){ // проверяем открыт ли файл со словами
        printf("Ошибка открытия файла!");
        return 1;
    }
    while (fscanf(txt, "%s", &buffer) != EOF) // получаем количество строк к файле со словами
        sizeFile++;
    rndStr = rand() % sizeFile; // получаем случайный номер строки из файла
    printf("word =%d\n", rndStr);
    fseek(txt, 0, SEEK_SET); // переводим курсор на начало файла
    //for (i = 0; i < rndStr; i++) // получаем случайную строку с номером rndStr (это будет загаданное слово)
    fscanf(txt, "%s", word);
    fclose(txt);
    printf("word =%d\n", word);
    sizeWord = strlen(word); // получаем количество букв в строке
    char *secretWord = (char*)calloc(sizeWord, sizeof(char)); // динамически задаём второй массив, в котором будут показываться отгаданные буквы
    memset(secretWord, '_', sizeWord); // заполняем его нижними подчёркиваниями
    guessChar = sizeWord;
    while (guessChar >= 0 && guessErr <= 9) {
        if (flag == 1){guessErr++;} // флаг равен 1 при не отгаданной букве
        hangman(guessErr);
        if (guessChar == 0){ // если количество не отгаданных букв = 0, то победа
            printf("%s", word);
            printf("\nВы победили!");
            free(secretWord);
            getchar();
            return 0;
        }
        if (guessErr == 9){ // если количество ошибочно отгаданных букв = 9, то поражение
            printf("%s", word);
            printf("\nВы проиграли(");
            free(secretWord);
            getchar();
            return 0;
        }
        printf("%s", secretWord);
        printf("\nВведённые буквы:\n");
        printf("%s", enterLetter);
        printf("\nВведите букву: ");
        scanChar = getchar();
        getchar();
        if (!((((int)scanChar >= -64 && (int)scanChar <= -33) || (int)scanChar == -88) || (((int)scanChar >= -32 && (int)scanChar <= -1) || (int)scanChar == -72))){ // символы не русского алфавита не учитываются
            continue;
        } else if ((int)scanChar >= -32 && (int)scanChar <= -1) { // строчные буквы преобразуются в прописные
            scanChar = (char)((int)scanChar - 32);
        } else if ((int)scanChar == -72) { // для буквы ё
            scanChar = (char)(-88);
        }
        flag = 1;
        for (i = 0; i < sizeWord; i++){ // цикл проверяет каждую букву на соответствие введённой
            if (word[i] == scanChar) {
                if (!(strchr(secretWord + i, scanChar))) { // если такая буква ещё не была отгадана, то выполняется
                    flag = 0;
                    guessChar--;
                    secretWord[i] = word[i];
                }
            } else if (strchr(enterLetter, scanChar)) { // если буква уже была введена
                flag = 0;
            }
        }
        if (!(strchr(enterLetter, scanChar))) // запись в массив введённых букв
            enterLetter[countLetter++] = scanChar;
    }
    free(secretWord);
    return 0;
}