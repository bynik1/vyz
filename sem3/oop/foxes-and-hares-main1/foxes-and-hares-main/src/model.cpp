#include <model.hpp>

Model::Model(std::ifstream& i)
{
    int f, r;
    f = r = 0;
    try {
        i >> this->M;
        i >> this->N;
        this->createField(this->N, this->M);
        i >> this->steps;
        i >> r;
        i >> f;
        while (r > 0) {
            int x, y, d, s;
            i >> x;
            i >> y;
            i >> d;
            i >> s;
            this->R.push_back(new Rabbit(x, y, d, s));
            this->setAnimalPos(x, y, 1);
            --r;
        }
        while (f > 0) {
            int x, y, d, s;
            i >> x;
            i >> y;
            i >> d;
            i >> s;
            this->F.push_back(new Fox(x, y, d, s));
            this->setAnimalPos(x, y, -1);
            --f;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }//отлов ошибок
}

void Model::createField(size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i) {
        this->field.push_back({});
        for (size_t j = 0; j < m; ++j) {
            this->field[i].push_back(0);
        }
    }
}

void Model::setAnimalPos(size_t x, size_t y, int a)
{
    try {
        if (x >= this->M) {
            throw std::string("x :: Array index out of bounds");
        } else if (y >= this->N) {
            throw std::string("y :: Array index out of bounds");
        } else {
            if (a < 0 && this->field[y][x] > 0)
                this->field[y][x] = 0;
            this->field[y][x] += a;
        }
    } catch (const std::string& e) {
        std::cerr << e << '\n';
    }
}

void Model::outField(std::ostream& os)
{
    for (size_t i = 0; i < this->N; ++i) {
        for (size_t j = 0; j < this->M; ++j) {
            os << this->field[i][j] << ' ';
        }
        os << '\n';
    }
}

size_t Model::getsteps()
{
    return this->steps;
}

void Model::changeAgeAnimals()
{
    for (auto& i : this->R) {
        i->changeAge();
        std::cout << "Rabbit live = " << i->getage() << '\n';
    }
    for (auto& i : this->F) {
        i->changeAge();
        std::cout << "Fox live = " << i->getage() << '\n';
    }
    for (auto i = this->R.begin(); i != this->R.end();) {
        if ((*i)->getage() >= MAX_RABBIT_AGE) {
            auto j = this->R.erase(i);
            i = j;
        } else {
            ++i;
        }
    }
    for (auto i = this->F.begin(); i != this->F.end();) {
        if ((*i)->getage() >= MAX_FOX_AGE) {
            auto j = this->F.erase(i);
            i = j;
        } else {
            ++i;
        }
    }
}

void Model::moveAnimals()
{
    for (auto& i : this->R) {
        i->move(*this);
    }
    for (auto& i : this->F) {
        i->move(*this);
    }
}

void Model::birthAnimals()
{
    for (auto& i : this->R) {
        i->birth(*this);
    }
    for (auto& i : this->F) {
        i->birth(*this);
    }
}

void Model::nextStep()
{
    for (auto& i : this->field) {
        for (auto& j : i) {
            j = 0;
        }
    }
    for (auto& i : this->R) {
        this->field[i->gety()][i->getx()] += 1;
    }
    for (auto& i : this->F) {
        if (this->field[i->gety()][i->getx()] > 0)
            this->field[i->gety()][i->getx()] = 0;
        this->field[i->gety()][i->getx()] -= 1;
    }
}

void Model::eatAnimals()
{
    this->F.sort([](Fox* f1, Fox* f2) { return f1->getage() > f2->getage(); });//сортировку по возрасту лис
    for (auto& i : this->F) {
        i->eat(*this);
    }
}