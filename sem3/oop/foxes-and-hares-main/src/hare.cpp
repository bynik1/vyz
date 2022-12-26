#include <animal.hpp>
#include <model.hpp>

Rabbit::Rabbit()
{
    this->wait = this->age = 0;
}

Rabbit::Rabbit(int _x, int _y, int _d, int _s)
    : Rabbit()
{
    this->x = _x;
    this->y = _y;
    this->d = _d;
    this->s = _s;
}

void Rabbit::move(Model& mod)
{
    if (this->wait >= this->s) {
        this->wait = 0;
        if (this->d > 3)
            d = 0;
        switch (this->d) {
        case 0:
            this->y -= RABBIT_STEP;
            break;
        case 1:
            this->x += RABBIT_STEP;
            break;
        case 2:
            this->y += RABBIT_STEP;
            break;
        case 3:
            this->x -= RABBIT_STEP;
            break;
        default:
            std::cerr << "Unacceptable direction of movement :: " << this->x << '.' << this->y << '\n';
            break;
        }
        if (this->x < 0) {
            this->x = mod.M - 1;
        }
        if (this->x > static_cast<int>(mod.M - 1)) {
            this->x = 0;
        }
        if (this->y < 0) {
            this->y = mod.N - 1;
        }
        if (this->y > static_cast<int>(mod.N - 1)) {
            this->y = 0;
        }
        this->d += 1;
    }
}

void Rabbit::change()
{
}

void Rabbit::changeAge()
{
    this->age += 1;
    this->wait += 1;
}

std::list<Rabbit*>::iterator Rabbit::death(std::list<Rabbit*>& l, std::list<Rabbit*>::iterator i)
{
    return l.erase(i);
}

int Rabbit::getage()
{
    return this->age;
}

size_t Rabbit::getx()
{
    return this->x;
}

size_t Rabbit::gety()
{
    return this->y;
}

void Rabbit::birth(Model& mod)
{
    if (this->age == 5 || this->age == 10) {
        mod.R.push_back(new Rabbit(this->x, this->y, this->d, this->s));
    }
}