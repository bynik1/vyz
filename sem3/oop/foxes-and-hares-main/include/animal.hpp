#ifndef __ANIMAL_HPP__
#define __ANIMAL_HPP__

#include <iostream>
#include <list>
#include <string>

#define MAX_RABBIT_AGE 10
#define MAX_FOX_AGE 15
#define RABBIT_STEP 1
#define FOX_STEP 2

class Model;

class Animal {
public:
    virtual void move(Model& mod) = 0;
    virtual void change() = 0;
    virtual void changeAge() = 0;
    virtual void birth(Model& mod) = 0;
    virtual ~Animal() {};

protected:
    int x, y;
    int d;
    int s;
    int age;
    int wait;
};

class Fox : public Animal {
public:
    Fox();
    Fox(int _x, int _y, int _d, int _s);
    ~Fox() override {}
    void move(Model& mod) override;
    void change() override;
    void changeAge() override;
    std::list<Fox*>::iterator death(std::list<Fox*>& l, std::list<Fox*>::iterator i);
    void birth(Model& mod) override;
    void eat(Model& mod);
    int getage();
    size_t getx();
    size_t gety();

private:
    int hunger;
};

class Rabbit : public Animal {
public:
    Rabbit();
    Rabbit(int _x, int _y, int _d, int _s);
    ~Rabbit() override {}
    void move(Model& mod) override;
    void change() override;
    void changeAge() override;
    std::list<Rabbit*>::iterator death(std::list<Rabbit*>& l, std::list<Rabbit*>::iterator i);
    void birth(Model& mod) override;
    int getage();
    size_t getx();
    size_t gety();

    friend void Fox::eat(Model& mod);
};

#endif // __ANIMAL_HPP__