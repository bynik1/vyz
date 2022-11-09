#include "point.h"
#include <iostream>
#include <unistd.h>
#include <cstring>

#define ALLPOINTS 100

using namespace std;

int** genMatrix(int size, int cell)
{
	int **matrix = new int *[size];

	for (int i = 0; i < size; i++) {
			matrix[i] = new int [size];
	}

	
	for (int i = 0; i < size; i++)	
		for (int j = 0; j < size; j++)
			matrix[i][j] = 0;
	
	return matrix;
}

void printMatrix(Point* points, int** matrix, int size)
{
	char* currentcolor;
	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			if (matrix[i][j] == 0)
				cout << "*" << " ";
			else
			{
				currentcolor = points[matrix[i][j]].get_color();
				cout << currentcolor << "O" << "\033[0;39m" << " ";
			}
				

		}
		cout << endl;
	}
}

int main()
{
	// srand(time(NULL));
	int size = 30;
	int** matrix;
	char cellValue = 0;
	int i = 0;
	int shows = 0;
	int colour;
	int coordx, coordy;
	int* pointpos;
	int each;
	int movemode;
	int useconds = 50;
	char* currentcolor;	
	
	matrix = genMatrix(size, cellValue);

	Point* points = new Point[ALLPOINTS];


	for (each = 0; each < ALLPOINTS; each++)
	{

		colour = 1 + rand() % 6;
		coordx = rand() % size;
		coordy = rand() % size;
		points[each].set_ball(colour, each);
		points[each].set_coords(coordx, coordy);
		movemode = 1 + rand() % 8;
		points[each].set_movemode(movemode);
	}

	do
	{
		if (useconds < 1)
			cout << "CRAZY SPEED doesnt work!" << endl;
		if (useconds > 100)
			cout << "Ne tormozi snickersni!" << endl;
		cout << "Time refresh!?" << endl;
		cin >> useconds;
	} while (useconds < 1 || useconds > 100);
	
	useconds *= 1000;



	do
	{

		for (each = 0; each < ALLPOINTS; each++) // зачистка прошлых следов
		{

			matrix[points[each].get_x()][points[each].get_y()] = 0;
		}
		for (each = 0; each < ALLPOINTS; each++) // движение и отображение в матрице
		{
			points[each].moving(size);

			matrix[points[each].get_x()][points[each].get_y()] = points[each].get_id();
		}
		
		printMatrix(points, matrix, size); // красивая обертка матрицы





		usleep(useconds);
		for (int up = 0; up < size; up++)
		{
			cout << "\033[F"; // затирает пред вывод		
		}
		
		shows++;

	}
	while (shows != 500);

	

	for (int up = 0; up < size; up++)
	{
		cout << "\n"; // возвращает курсор обратно	
	}



	
	delete[] points;

	for (i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;

}