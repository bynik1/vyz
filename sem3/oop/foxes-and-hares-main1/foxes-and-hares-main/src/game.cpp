#include <animal.hpp>
//#include <conio.h>
#include <model.hpp>

int startGame(char* path_in, char* path_out)
{
    std::ifstream inputFile;//считывание
    open_file(inputFile, path_in);//открывание файла
    std::ofstream outputFile(path_out);//открытия файла куда будет записывать результат
    Model mod(inputFile);

    for (size_t steps = 0; steps <= mod.getsteps(); ++steps) {
        mod.outField(std::cout);// поле
        std::cout << '\n'; 
        mod.changeAgeAnimals();// возраст
        mod.moveAnimals();// ожидания
        if (steps) // при первом ходе никто никого не ест
            mod.eatAnimals();
        mod.birthAnimals();// 
        mod.nextStep();// смена данных на поле

        // while (getch() != ' ') {
        // }
        //system("clear");
    }
    mod.outField(std::cout);// вывод поля
    mod.outField(outputFile);//
    return 0;
}
