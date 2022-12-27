#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <animal.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

#define open_file(strm, path)                                                     \
    {                                                                             \
        strm.exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit); \
        try {                                                                     \
            strm.open(path);                                                      \
        } catch (const std::exception& e) {                                       \
            std::cerr << e.what() << '\n';                                        \
            exit(EXIT_FAILURE);                                                   \
        }                                                                         \
    }

class Model {
public:
    Model();
    Model(size_t n, size_t m);
    Model(std::ifstream& i);
    ~Model();
    void changeAgeAnimals();
    void moveAnimals();
    void birthAnimals();
    void eatAnimals();
    void outField(std::ostream& os);
    void nextStep();
    size_t getsteps();

    friend void Fox::move(Model& mod);
    friend void Fox::birth(Model& mod);
    friend void Fox::eat(Model& mod);
    friend void Rabbit::move(Model& mod);
    friend void Rabbit::birth(Model& mod);

private:
    std::list<Fox*> F;
    std::list<Rabbit*> R;
    std::vector<std::vector<int>> field;
    size_t N, M;
    size_t steps;

    void createField(size_t n, size_t m);
    void setAnimalPos(size_t x, size_t y, int a);
};

int startGame(char* path_in, char* path_out);

#endif // __MODEL_HPP__
