#include <stdio.h>
#include <string.h>
#include <search.h>
#include <stdlib.h>
#include "comp.h"

int reg_flags[REG_SIZE]; // массив для хранения значений флагов

int col = 0;

int memory[MEMORY_SIZE];
int reg_flags[REG_SIZE];
int ar[MEMORY_SIZE];
int flags = 0;

int commands[] = {
    10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43, 51, 52, 53, 54, 55, 56, 57,
    58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
};

// инициализирует оперативную память Simple
// Computer, задавая всем её ячейкам нулевые значения. В качестве
// «оперативной памяти» используется массив целых чисел, определенный
// статически в рамках библиотеки. Размер массива равен 100 элементам.

int sc_memoryInit (){
    memset(memory, 0, MEMORY_SIZE * sizeof(int));
    // memset(ar, 0, MEMORY_SIZE * MEMORY_SIZEof(int));
    // for (int i = 0; i < MEMORY_SIZE; i++) {
    //     printf("%d ", memory[i]);
    // }

    return 0;
}

// задает значение
// указанной ячейки памяти как value. Если адрес выходит за допустимые
// границы, то устанавливается флаг «выход за границы памяти» и работа
// функции прекращается с ошибкой;


int sc_memorySet (int address, int value){
    if (address <= 0 || address < 99) {
        memory[address] = value;
        //printf("%d\n", memory[address]);
    }

    else{
        sc_regSet(FLAG_MEMORY_ACCESS_ERROR, 1);
        printf("Error: Out of memory bounds\n");
        return -1;
    }
    
    return 0;
}

// возвращает значение
// указанной ячейки памяти в value. Если адрес выходит за допустимые
// границы, то устанавливается флаг «выход за границы памяти» и работа
// функции прекращается с ошибкой. Значение value в этом случае не
// изменяется.

int sc_memoryGet(int address, int * value){

    if (address < 0 || address > 99 || value == NULL) {
        sc_regSet(FLAG_MEMORY_ACCESS_ERROR, 1);
        printf("Error: Out of memory bounds\n");
        return -1;
    }

    *value = memory[address];

    return 0;
}


// – сохраняет содержимое памяти
// в файл в бинарном виде (используя функцию write или fwrite);


int sc_memorySave(char* filename) {
    int memoryMEMORY_SIZE = sizeof(memory); // размер данных в байтах
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Не удалось открыть файл для записи\n");
        return -1;
    }

    if (fwrite(memory, memoryMEMORY_SIZE, 1, fp) != 1) {
        printf("Не удалось записать данные в файл\n");
        return -1;
    }

    fclose(fp);
    printf("Данные успешно записаны в файл\n");

    return 0;
}

// загружает из указанного файла
// содержимое оперативной памяти (используя функцию read или fread);

int sc_memoryLoad (char * filename){
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Не удалось открыть файл для чтения\n");
        return -1;
    }

    size_t n = fread(memory, sizeof(int), MEMORY_SIZE, fp);
    if (n == 0) {
        printf("Не удалось прочитать данные из файла\n");
        return -1;
    }

    // for(int i = 0;i<MEMORY_SIZE;i++){
    //     printf("%d", memory[i]);
    // }

    fclose(fp);
    printf("Данные успешно загружены из файла\n");
    return 0;
}

// инициализирует регистр флагов нулевым
// значением;
int sc_regInit() {
  flags = 0;
  return 0;
}


// устанавливает значение
// указанного регистра флагов. Для номеров регистров флагов должны
// использоваться маски, задаваемые макросами (#define). Если указан
// недопустимый номер регистра или некорректное значение, то функция
// завершается с ошибкой.

int sc_regSet(int reg, int value) {
    if (reg < 0 || reg > 4) {
        return -1;
    }
    if (value != 0 && value != 1) {
        return -1;
    }
    if (value == 1) {
        switch (reg) {
            case 0:
                printf("Cannot set flag\n");
                break;
            case 1:
                printf("Overflow flag is set\n");
                break;
            case 2:
                printf("Division by zero flag is set\n");
                break;
            case 3:
                printf("Memory access error flag is set\n");
                break;
            case 4:
                printf("Wrong command flag is set\n");
                break;
        }
    }


    (value == 1) ? (flags |= (1 << (reg - 1)))
                       : (flags &= (~(1 << (reg - 1))));


    return 0;
}

// – возвращает значение
// указанного флага. Если указан недопустимый номер регистра, то функция
// завершается с ошибкой.



//int reg_flags = 0;  // регистр флагов

int sc_regGet(int reg, int *value) {
    if (reg < 0 || reg > 4 || value == NULL) {  // проверка допустимости номера регистра
        return -1;  // возврат кода ошибки
    }

    *value = (flags >> (reg - 1)) & 0x1;  // получение значения флага
    return 0;  // успешное завершение функции
}


// кодирует команду с указанным номером и операндом и помещает результат
// в value. Если указаны неправильные значения для команды или операнда, то
// функция завершается с ошибкой. В этом случае значение value не изменяется.
int comp(const void *n1, const void *n2) { return (*(int *)n1 - *(int *)n2); }

int sc_commandEncode(int command, int operand, int *value) {
    if (bsearch(&command, commands, sizeof(commands) / sizeof(commands[0]),
              sizeof(commands[0]), comp) == NULL || command < 0 || command > 127 || operand < 0 || operand > 127) {
        return -1; // неправильное значение для команды
    }

    *value = 0;
    *value = (command << COMMAND_SHIFT) | operand;

    return 0;
}


// декодирует значение как команду Simple Computer. Если декодирование
// невозможно, то устанавливается флаг «ошибочная команда» и функция
// завершается с ошибкой.
int sc_commandDecode(int value, int *command, int *operand) {
    if (command == NULL || operand == NULL) {
        sc_regSet(FLAG_MEMORY_ACCESS_ERROR, 1);
        return -1;
    }

    *operand = *command = 0;

    *operand = value & MASK_COMMAND;
    value >>= COMMAND_SHIFT;
    *command = value;

    return 0;
}





// int main(void) {

//     sc_memoryInit();
//     sc_memorySet(1, 333);
//     sc_memoryGet(10, &memory[3]);
//     sc_memorySave("2.txt");
//     sc_memoryLoad("2.txt");

//     sc_regInit();
//     sc_regSet(1, 1);  // Set overflow flag
//     //sc_regSet(5, 1);  // Invalid register number
//     sc_regSet(0, 1);  // Cannot set flag
//     //sc_regSet(1, 2);  // Invalid value

//     return 0;
// }