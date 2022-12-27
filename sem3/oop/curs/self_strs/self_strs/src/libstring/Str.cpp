#include "Str.hpp"
#include <algorithm>
#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const String& s)//оператор вывода поток
{
    os << s.s;
    return os;
}

bool operator<(const String& s1, const String& s2)//оператор меньше строк
{
    if (strcmp(s1.s, s2.s) < 0)
        return 1;
    return 0;
}

bool operator>(const String& s1, const String& s2)//оператор больше строк
{
    if (!(s1 < s2) && strcmp(s1.s, s2.s) > 0)
        return 1;
    return 0;
}

bool operator==(const String& s1, const String& s2)// оператор равно
{
    if (!(s1 < s2) && !(s1 > s2))
        return 1;
    return 0;
}

bool operator<=(const String& s1, const String& s2)//меньше или равно
{
    if (s1 < s2 || s1 == s2)
        return 1;
    return 0;
}

bool operator>=(const String& s1, const String& s2)//больше или равно
{
    if (!(s1 < s2))
        return 1;
    return 0;
}

bool operator!=(const String& s1, const String& s2)// не равно
{
    if (!(s1 == s2))
        return 1;
    return 0;
}

String& String::operator+=(const String& _s)// +=
{
    // char* tmp = s;
    // s = new char[sizeof(s) + sizeof(_s.s)];
    // strcat(s, tmp);
    _size += _s._size;
    strcat(s, _s.s);
    return *this;
}

String operator+(const String& s1, const String& s2)//+
{
    String ret = s1;
    ret += s2;
    return ret;
}

const char& String::operator[](const size_t index) const noexcept//символ по данному индексу
{
    return s[index];
}

size_t String::size() const noexcept//размер 
{
    return _size;
}

bool String::find(const char* _s) const//поиск строки в подстроке
{
    if (strstr(s, _s))
        return 1;
    return 0;
}

void CharVector::add_back(char c)//добавление в конец
{
    s.push_back(c);
}

void CharVector::add_front(char c)//в начало
{
    s.emplace(s.begin(), c);
}

void CharVector::remove_back()//удаление с конца
{
    s.pop_back();
}

void CharVector::remove_front()//удалени с начала
{
    s.erase(s.begin());
}

char CharVector::get_begin() const//возращает символ лежащий в начале
{
    return *(s.begin());
}

char CharVector::get_end() const//возращает символ лежащий в конце
{
    return *(s.end());
}

size_t CharVector::size() const noexcept//возращает размер вектора
{
    return s.size();
}

size_t CharVector::capa() const noexcept//возращает вместимрость

{
    return s.capacity();
}

bool CharVector::find_c(const char _s) const//поиск символа в строке
{
    if (std::find(s.begin(), s.end(), _s) != s.end())
        return 1;
    return 0;
}

std::ostream& operator<<(std::ostream& os, const CharVector& cv)//оператор вывода в поток для вектора
{
    for (const auto& c : cv.s) {
        os << c;
    }
    return os;
}

std::string CharVector::get_prefix(const size_t prefix_size)//поиск префикса 
{
    std::string buf;
    std::copy_n(s.begin(), prefix_size, std::back_inserter(buf));
    return buf;
}
