#include <animal.hpp>
#include <conio.h>
#include <model.hpp>

int startGame(char* path_in, char* path_out)
{
    std::ifstream inputFile;
    open_file(inputFile, path_in);
    std::ofstream outputFile(path_out);
    Model mod(inputFile);

    for (size_t steps = 0; steps <= mod.getsteps(); ++steps) {
        mod.outField(std::cout);
        std::cout << '\n';
        mod.changeAgeAnimals();
        mod.moveAnimals();
        if (steps)
            mod.eatAnimals();
        mod.birthAnimals();
        mod.nextStep();

        while (getch() != ' ') {
        }
        system("clear");
    }
    mod.outField(std::cout);
    mod.outField(outputFile);
    return 0;
}
