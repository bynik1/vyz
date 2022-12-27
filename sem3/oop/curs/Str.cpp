#include "Str.hpp"
#include <algorithm>
#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, String& s)
{
    os << s.s;
    return os;
}

bool operator<(const String& s1, const String& s2)
{
    if (strcmp(s1.s, s2.s) < 0)
        return 1;
    return 0;
}

bool operator>(const String& s1, const String& s2)
{
    if (!(s1 < s2) && strcmp(s1.s, s2.s) > 0)
        return 1;
    return 0;
}

bool operator==(const String& s1, const String& s2)
{
    if (!(s1 < s2) && !(s1 > s2))
        return 1;
    return 0;
}

bool operator<=(const String& s1, const String& s2)
{
    if (s1 < s2 || s1 == s2)
        return 1;
    return 0;
}

bool operator>=(const String& s1, const String& s2)
{
    if (!(s1 < s2))
        return 1;
    return 0;
}

bool operator!=(const String& s1, const String& s2)
{
    if (!(s1 == s2))
        return 1;
    return 0;
}

String& String::operator+=(const String& _s)
{
    // char* tmp = s;
    // s = new char[sizeof(s) + sizeof(_s.s)];
    // strcat(s, tmp);
    _size += _s._size;
    strcat(s, _s.s);
    return *this;
}

String String::operator+(const String& _s)
{
    _size += _s._size;
    strcat(s, _s.s);
    return *this;
}

const char& String::operator[](const size_t index) const noexcept
{
    return s[index];
}

size_t String::size() const noexcept
{
    return _size;
}

bool String::find(const char* _s) const
{
    if (strstr(s, _s))
    return 1;
    return 0;
}

void CharVector::add_back(char c)
{
    s.push_back(c);
}

void CharVector::add_front(char c)
{
    s.emplace(s.begin(), c);
}

void CharVector::remove_back()
{
    s.pop_back();
}

void CharVector::remove_front()
{
    s.erase(s.begin());
}

char CharVector::get_begin() const
{
    return *(s.begin());
}

char CharVector::get_end() const
{
    return *(s.end());
}

size_t CharVector::size() const noexcept
{
    return s.size();
}

size_t CharVector::capa() const noexcept
{
    return s.capacity();
}

bool CharVector::find(const char* _s) const
{
    if (std::find(s.begin(), s.end(), *_s) != s.end())
        return 1;
    return 0;
}

bool CharVector::find_c(const char _s) const
{
    if (std::find(s.begin(), s.end(), _s) != s.end())
        return 1;
    return 0;
}

std::ostream& operator<<(std::ostream& os, const CharVector& cv)
{
    for (const auto& c : cv.s) {
        os << c;
    }
    return os;
}

std::string CharVector::get_prefix(const size_t prefix_size)
{
    std::string buf;
    std::copy_n(s.begin(), prefix_size, std::back_inserter(buf));
    return buf;
}

