#ifndef SIMPLECOMPUTER_H
#define SIMPLECOMPUTER_H

#define MEMORY_SIZE 100
#define REG_SIZE 32 // размер регистра флагов


#define FLAG_OVERFLOW 0x1 // маска флага переполнения
#define FLAG_DIVISION_BY_ZERO 0x2 // маска флага нуля
#define FLAG_MEMORY_ACCESS_ERROR 0x3 // маска флага выхода за границы памяти
#define FLAG_WRONG_COMMAND 0x8 //Wrong command flag is set

#define MASK_COMMAND 0x7F00
#define MASK_OPERAND 0x00FF
#define COMMAND_SHIFT 7

// #define ERROR_OUT_OF_MEMORY 1
// #define ERROR_OUT_OF_BOUNDS 2
// #define ERROR_INVALID_REGISTER 3
// #define ERROR_INVALID_VALUE 4
// #define ERROR_INVALID_COMMAND 5

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);
int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);

int comp(const void *n1, const void *n2);

#endif