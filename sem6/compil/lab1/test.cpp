#include <iomanip> 
#include <iostream> 
#include <limits> 
#include <typeinfo>
 
#define OUT(x) '\n' << std::setw(16) << #x << x
 
int main ( ) 
{ 
    std:: cout
        <<  "Литерал"  " \t "  "Напечатанное значение"  <<  std::left << OUT(58.             )  // double 
        << OUT(4e2             )  // double 
        << OUT(  123.456e-67     )  // double 
        << OUT( 123.456e-67f    )  // число с плавающей запятой, усеченное до нуля 
        << OUT( .1E4f           )  // float 
        << OUT( 0x10.1p0        )  // double 
        << OUT( 0x1p5           )  // двойной 
        << OUT(  0x1e5           )  // целочисленный литерал, а не с плавающей запятой 
        << OUT(  3.14'15'92      )  // двойные одинарные кавычки игнорируются (C++14) 
        << OUT( 1.18e-4932l     )  // long double 
        <<  std::setprecision ( 39 ) 
        << OUT(3.4028234e38f   )  // float 
        << OUT(3.4028234e38    )  // double 
        << OUT(3.4028234e38l   )  // long double 
        <<  '\n' ;
 
    static_assert ( 3.4028234e38f ==  std:: numeric_limits < float > :: max ( ) ) ;
 
    static_assert ( 3.4028234e38f ==   // заканчивается на 4 
                  3.4028235e38f );    // заканчивается на 5
 
    static_assert ( 3.4028234e38  !=    // заканчивается на 4 
                  3.4028235e38 );     // заканчивается на 5
 
    // Обе константы с плавающей запятой ниже — 3.4028234e38 
    static_assert ( 3.4028234e38f !=   // число с плавающей запятой (затем повышается до double) 
                  3.4028234e38 );     // двойной 
}