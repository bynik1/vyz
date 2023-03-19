#include <stdio.h>

#include <stdlib.h>

#include <libcomputer/comp.h>


int main(void) {

    //int *value = malloc(sizeof(int));
    //sc_commandEncode(0x33, 0x59, value);

    //int *command = malloc(sizeof(int));
    //int *operand = malloc(sizeof(int));

    //sc_commandDecode(*value, command, operand);

    sc_memoryInit();
    // sc_memorySet(1, 333);
    // sc_memorySave("2.txt");
    // sc_memoryLoad("2.txt");

    //sc_regInit();
    //sc_regSet(1, 1);  // Set overflow flag
    //sc_regSet(5, 1);  // Invalid register number
    //sc_regSet(0, 1);  // Cannot set flag
    //sc_regSet(1, 2);  // Invalid value

    return 0;
}