#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
int* genRandArray(int size, int maxValue)
{
	int* arr = (int*)malloc((size + 1) * sizeof(int));
	arr[0] = size;
	for(int n = 1; n <= size; n++)
	{
		arr[n] = rand() % maxValue;
	}
	return arr;
}

void print(int* arr)
{
	std::cout << arr[0] << ": ";
	for(int n = 1; n <= arr[0]; n++)
		std::cout << arr[n] << " ";
	std::cout << endl;
}

int main()
{
	srand(time(NULL));
	int size = rand() % 10;
	int maxValue = 100;
	int* arr = genRandArray(size, maxValue);
	print(arr);
	free(arr);
	return 0;
}
