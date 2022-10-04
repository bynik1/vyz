// Задание 2. Создать двумерный динамический массив с произвольным количеством 
// элементов в каждой сроке. Заполнить его и распечатать построчно.

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
int** genMatrix(int N, int maxValue)
{
	int** matrix = new int*[N];
	for(int i = 0; i < N; i++)
    {
        int S = rand()% 99 + 1;
        matrix[i] = new int[S];
        matrix[i][0] = S;
        for(int j = 1; j < S; j++)
            matrix[i][j] = rand() % maxValue + 1;
    }
    return matrix;
}


void printMatrix(int** matrix, int N)
{
    cout << "matrix" << endl;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < matrix[i][0]; j++)
        {
            cout.width(2);
           	cout << matrix[i][j] << " ";
        }
   cout << endl;
	}
}

// void printMasive(int *D, int N)
// {
//     cout << "masive" << endl;
//     for(int j = 0; j < N*N ; j++)
//         cout << D[j] << " ";
// }

int main()
{
    srand(time(NULL));
    int N = rand() % 9 + 1;
    int S = rand() % 99 + 1;
    cout << N << endl;
    int maxValue = 9;
    int** matrix = genMatrix(N, maxValue);
    printMatrix(matrix, N);
    for(int i = 0; i <= N; i++)
    {
        delete(matrix[i]);
    }
    delete(matrix);
    return 0;
}
