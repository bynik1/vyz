#include <string.h>
#include "point.h"
#include <iostream>

using namespace std;


int Point::get_id()
{
    return id;
}
int Point::get_x()
{
    return x;
}
int Point::get_y()
{
    return y;
}
char* Point::get_color()
{
    return color;
}

void Point::set_ball(int variant, int nomer)
{
    color = new char[11];
    strcpy(color, "\033[0;39m");
    color[5] = variant + '0';

    // cout << color << "sdfsdf" << endl; 
    id = nomer;
}

void Point::set_coords(int setx, int sety)
{
    x = setx;
    y = sety;

}

void Point::set_movemode(int mode)
{
    movemode = mode;
    switch (movemode)
    {
    case 1:
        trajectory = 'e';
        break;
    case 2:
        trajectory = 'w';
        break;
    case 3:
        trajectory = 'n';
        break;
    case 4:
        trajectory = 's';
        break;
    case 5:
        trajectory = 'r'; // ne
        break;
    case 6:
        trajectory = 'g'; // se
        break;
    case 7:
        trajectory = 'k'; // nw
        break;
    case 8:
        trajectory = 'f'; // sw
        break;
    default:
        break;
    }
}


void Point::moving(int size)
{
    if (movemode == 1 || movemode == 2) // right left
    {
        moving90lr(size);
    }
    else if (movemode == 3 || movemode == 4) // up down
    {
        moving90ud(size);
    }
    else if (movemode > 4 || movemode < 9) // up-right down-right etc
    {
        moving45(size);
    }
}


void Point::moving90lr(int size)
{
            if (trajectory == 'e')
        {
            if (y < size - 1) // если нет стены
                y++;
            else {
                y--;
                trajectory = 'w'; // меняем трраеторию движения
            }
                
        }
        else
        {
            if (y > 0) // если нет стены
                y--;
            else {
                y++;
                trajectory = 'e'; // возвращаем траекторию
            }
        }
}

void Point::moving90ud(int size)
{
        if (trajectory == 's')
        {
            if (x < size - 1) // если нет стены
                x++;
            else {
                x--;
                trajectory = 'n'; // меняем трраеторию движения
            }
                
        }
        else
        {
            if (x > 0) // если нет стены
                x--;
            else {
                x++;
                trajectory = 's'; // возвращаем траекторию
            }
        }
}

void Point::moving45(int size)
{
    if (trajectory == 'r') // ne
    {
        if (x > 0 || y < size - 1) 
        {
            if (x == 0) // граница
            {
                x++;
                y++;
                trajectory = 'g';
            }
            else if (y == size - 1) // граница
            {
                x--;
                y--;
                trajectory = 'k';
            }
            else // само перемещение
            {
                x--;
                y++;
            }
        }
        else // ne -угол
        {
            x++;
            y--;
            trajectory = 'f'; // sw
        }
    }
    else if (trajectory == 'f') // sw
    {
        if (y > 0 || x < size - 1) 
        {
            if (y == 0) // граница
            {
                x++;
                y++;
                trajectory = 'g';
            }
            else if (x == size - 1) // граница
            {
                x--;
                y--;
                trajectory = 'k';
            }
            else // само перемещение
            {
                x++;
                y--;
            }
        }
        else // sw -угол
        {
            y++;
            x--;
            trajectory = 'r'; // ne
        }
    }
    else if (trajectory == 'k') // nw
    {
        if (x > 0 || y > 0) 
        {
            if (x == 0) // граница
            {
                x++;
                y--;
                trajectory = 'f';
            }
            else if (y == 0) // граница
            {
                x--;
                y++;
                trajectory = 'r';
            }
            else // само перемещение
            {
                x--;
                y--;
            }
            
        }
        else // nw -угол
        {
            x++;
            y++;
            trajectory = 'g'; //se
        }
    }
    else if (trajectory == 'g') // se
    {
        if (x < size - 1 || y < size - 1) 
        {
            if (x == size - 1) // граница
            {
                x--;
                y++;
                trajectory = 'r';
            }
            else if (y == size - 1) // граница
            {
                x++;
                y--;
                trajectory = 'f';
            }
            else // само перемещение
            {
                x++;
                y++;
            }
            
        }
        else // se -угол
        {
            x--;
            y--;
            trajectory = 'k'; //nw
        }
    }
}