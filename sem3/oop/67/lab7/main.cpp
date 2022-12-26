#include "list.hpp"

unsigned long list::count = 0;

int main(void)
{
    list l1 = { 1, 2, 3 };

    list l2(3, 1);

    l1.merge(l2);
    l1.print();

    // l.push_front(5);
    // l.push_back(1);
    // l.push_back(2);
    // l.push_back(3);
    // l.push_front(4);
    // l.print();

    // list m;
    // m.push_back(33);
    // m.push_front(14);

    // l = l + m;

    // l.unique();
    // l.print();

    // !

    // queue s(5, 1);

    // s.push(1);
    // s.push(2);
    // s.push(3);
    
    // while (!s.empty()) {
    //     std::cout << s.pop() << std::endl;
    // }

    // std::cout << list::getcount() << std::endl;

    return 0;
}