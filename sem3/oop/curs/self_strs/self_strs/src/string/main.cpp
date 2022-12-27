#include "../libstring/Str.hpp"
#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;

int main()
{
    String s1("helloworld");
    String s2("hello");
    String s3;

    // cout << std::setw(10);

    cout << "s1 - " << s1 << '\n' << "s2 - " << s2 << '\n';

    cout << "less - " << (s1 < s2) << '\n'
         << "more - " << (s1 > s2) << '\n'
         << "not equal - " << (s1 != s2) << '\n'
         << "equal - " << (s1 == s2) << '\n'
         << "less | equal - " << (s1 <= s2) << '\n'
         << "more | equal - " << (s1 >= s2) << '\n'
         << "sum - " << (s1 + s2) << '\n'
         << "s1[2] - " << (s1[2]) << '\n'
         << "size - " << (s1.size()) << '\n'
         << "is 'hello' in s1? - " << (s1.find("hello")) << '\n';

    s1 += s2;
    cout << "s1 += s2 " << s1 << '\n';

    return 0;
}
