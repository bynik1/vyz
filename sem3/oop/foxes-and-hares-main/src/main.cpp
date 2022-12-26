#include <animal.hpp>
#include <model.hpp>

int main(int argc, char** argv)
{
    return argc > 2 ? startGame(argv[1], argv[2]) : -1;//
}