#ifndef __STRING_H__
#define __STRING_H__

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <wchar.h>

class StrType {//абстрактный 1 класс
    virtual size_t size() const noexcept = 0;
    virtual bool find(const char* _s) const = 0;
};

class String : public StrType {//2 класс
    friend std::ostream& operator<<(std::ostream& os, const String& s);

    friend bool operator<(const String& s1, const String& s2);
    friend bool operator>(const String& s1, const String& s2);
    friend bool operator==(const String& s1, const String& s2);
    friend bool operator<=(const String& s1, const String& s2);
    friend bool operator>=(const String& s1, const String& s2);
    friend bool operator!=(const String& s1, const String& s2);
    friend String operator+(const String& s1, const String& s2);

public:
    String() : s(nullptr), _size(0)//Списки инициализации

    {
    }

    String(const char* _s) : s(new char[strlen(_s) + 1]), _size(strlen(_s))//Списки инициализации

    {
        strcpy(s, _s);
    }

    String(const String& _s)
    {
        if (s == _s.s)
            return;
        s = new char[strlen(_s.s) + 1];
        strcpy(s, _s.s);
        _size = _s._size;
    }

    String& operator=(const String& _s)
    {
        if (_s.s == s)
            return *this;
        s = new char[strlen(_s.s) + 1];
        strcpy(s, _s.s);
        _size = _s._size;
        return *this;
    }

    String(String&& _s)
        : s(new char[strlen(_s.s) + 1]), _size(std::move(_s._size))//Списки инициализации
    {
        s = std::move(_s.s);
    }

    virtual ~String()
    {
        if (s != nullptr)
            delete[] s;
        _size = 0;
    }

    String& operator+=(const String& _s);
    const char& operator[](const size_t index) const noexcept;

    virtual size_t size() const noexcept override;// полиморфизм
    virtual bool find(const char* _s) const override;

private:
    char* s = nullptr;
    size_t _size = 0;
};

class CharVector : public StrType {// 3 класс наследование
    friend std::ostream& operator<<(std::ostream& os, const CharVector& cv);

public:
    CharVector() = default;

    CharVector(const char* _s)
    {
        std::copy(_s, _s + static_cast<int>(strlen(_s)), std::back_inserter(s));
    }

    void add_back(char c);
    void add_front(char c);

    void remove_back();
    void remove_front();

    char get_begin() const;
    char get_end() const;

    size_t size() const noexcept override;
    size_t capa() const noexcept;

    bool find_c(const char _s) const;
    bool find(const char* _s) const override;

    std::string get_prefix(const size_t prefix_size);

private:
    std::vector<char> s;
};

#endif // __STRING_H__