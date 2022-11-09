#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int** genRandMatrix(int size, int maxValue)
{
	int random;
	int** matrix = (int**)malloc((size + 1) * sizeof(int*));
	matrix[0] = (int*)malloc(sizeof(int));
	matrix[0][0] = size;
	printf("size =%d\n", size);
	for(int i = 1; i <= size; i++)
	{
		//printf("dsdsdsd/n");
		random = rand() % 9 + 1;
		printf("random= %d\n", random);
		matrix[i] = (int*)malloc((random + 1) * sizeof(int));
		matrix[i][0] = random;
		for(int j = 1; j < size; j++)
		{
			matrix[i][j] = rand() % maxValue;
			
		}
	}
	return matrix;
}

void printMatrix(int** matrix)
{
	std::cout << matrix[0][0] << endl;
	for(int i = 1; i < matrix[0][0]; i++)
	{
		std::cout << matrix[i][0] << ": ";
		for(int j = 1; j < matrix[i][0]; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << endl;
	}
}

int main()
{
	srand(time(NULL));
	int size = rand() % 10 + 1;
	int maxValue = 100;
	int** matrix = genRandMatrix(size, maxValue);
	//printMatrix(matrix);
	for(int i = 0; i < size; i++) {
    	free(matrix[i]);
	}
    free(matrix);
	return 0;
}
