#include <animal.hpp>
#include <model.hpp>

Fox::Fox()
{
    this->wait = 0;
    this->hunger = this->age = 0;
}

Fox::Fox(int _x, int _y, int _d, int _s)
    : Fox()
{
    this->x = _x;
    this->y = _y;
    this->d = _d;
    this->s = _s;
    this->wait = this->s;
}

void Fox::move(Model& mod)
{
    if (this->wait <= 0) {
        this->wait = this->s;
        this->d += 1;
    }
    if (this->d > 3)
        this->d = 0;
    switch (this->d) {
    case 0:
        this->y -= FOX_STEP;
        break;
    case 1:
        this->x += FOX_STEP;
        break;
    case 2:
        this->y += FOX_STEP;
        break;
    case 3:
        this->x -= FOX_STEP;
        break;
    default:
        std::cerr << "Unacceptable direction of movement :: " << this->x << '.' << this->y << '\n';
        break;
    }
    if (this->x < 0) {
        this->x = mod.M + this->x;
    }
    if (this->x > static_cast<int>(mod.M - 1)) {
        this->x -= static_cast<int>(mod.M);
    }
    if (this->y < 0) {
        this->y = mod.N + this->y;
    }
    if (this->y > static_cast<int>(mod.N - 1)) {
        this->y -= static_cast<int>(mod.N);
    }
}

void Fox::changeAge()
{
    this->age += 1;
    this->wait -= 1;
}

std::list<Fox*>::iterator Fox::death(std::list<Fox*>& l, std::list<Fox*>::iterator i)
{
    return l.erase(i);
}

int Fox::getage()
{
    return this->age;
}

size_t Fox::getx()
{
    return this->x;
}

size_t Fox::gety()
{
    return this->y;
}

void Fox::birth(Model& mod)
{
    if (this->hunger >= 2) {
        mod.F.push_back(new Fox(this->x, this->y, this->d, this->s));
        this->hunger -= 2;
    }
}

void Fox::eat(Model& mod)
{
    for (auto i = mod.F.begin(); i != mod.F.end(); ++i) {
        for (auto j = mod.R.begin(); j != mod.R.end(); ++j) {
            if ((*i)->x == (*j)->x && (*i)->y == (*j)->y) {
                auto k = (*j)->death(mod.R, j);
                j = k;
                (*i)->hunger += 1;
            }
        }
    }
}
