#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int** genMatrix(int N,int maxValue)
{
	int** matrix = new int*[N];
	for(int i = 0; i < N; i++)
	{
		matrix[i] = new int[N];
		for(int j = 0; j < N; j++)
			matrix[i][j] = rand() % maxValue + 1;
	}
	return matrix;
}

int* initmasive(int N)
{
	int *D = new int[N * N];
	for(int j = 0; j < N * N; j++)
		D[j] = 0;
	return D;
}

void spiral(int** matrix, int* D, int N)
{
	int a = 0, b = N - 1, c = 0, d = N - 1;
	int i, j, s = 0;
	cout << "spiral" << endl;
	for(j = a; j <= b; j++)
	{ 
		D[s] = matrix[c][j];
//		cout << D[s] << " ";
		s++; 
	}
//	cout << endl;
	c++;
	while(1)
	{
		if(s >= N * N)
			break; 
		for(i = c; i <= d; i++)
		{
			D[s] = matrix[i][b];
//			cout << D[s] << " ";
			s++;
		}
//		cout << endl;
		b--;
		for(j = b; j >= a; j--)
		{
			D[s + b - j] = matrix[d][j];
//			cout << D[s + b - j] << " ";
		}
//		cout << endl;
		s += b - a + 1;
		d--;
		if(s >= N * N)
			break;

		for(i = d; i >= c; i--)
		{
			D[s + d - i] = matrix[i][a];
//			cout << D[s + d - i] << " ";
		}
//		cout << endl;
		s += d - c + 1;
		a++;
		for(j = a; j <= b; j++)
		{
			D[s] = matrix[c][j];
//			cout << D[s] << " ";
			s++;
		}
//		cout << endl;
		c++;
		if(s >= N * N)
			break;

	}
}

void vint(int** matrix, int* D, int N)
{
	int a = 0, b = N - 1, c = 0, d = N - 1;
	int i, j, s = N * N;
	cout << "vint" << endl;
	for(j = a; j <= b; j++)
	{ 
		s--;
		D[s] = matrix[c][j];
//		cout << D[s] << " ";
	}
//	cout << endl;
	c++;
	while(1)
	{
		if(s <= 0)
			break; 
		for(i = c; i <= d; i++)
		{
			s--;
			D[s] = matrix[i][b];
//			cout << D[s] << " ";
		}
//		cout << endl;
		b--;
		for(j = b; j >= a; j--)
		{
		s--;
			D[s] = matrix[d][j];
//			cout << D[s] << " ";
		}
//		cout << endl;

		d--;

		if(s <= 0)
			break; 
		for(i = d; i >= c; i--)
		{
		s--;
			D[s] = matrix[i][a];
//			cout << D[s] << " ";
		}
//		cout << endl;
		a++;
		for(j = a; j <= b; j++)
		{
			s--;
			D[s] = matrix[c][j];
//			cout << D[s] << " ";
		}
//		cout << endl;
	c++;
		if(s <= 0)
			break;

	}
}

void rightdiag(int** matrix, int* D, int N)
{
	int i, j, a, b = 1, s = 0;
	cout << "right diagonal" << endl;
	for(j = N - 1; j >= 0; j--)
	{
		a = j;
		for(i = 0; i <= N - j - 1; i++)
		{
			D[s] = matrix[i][a];
//			cout << D[s] << " ";
			a++;
			s++;
		}
//		cout << endl;
	}
	for(j = N - 2; j >= 0; j--)
	{
		a = 0;
		for(i = b; i <= N - 1; i++)
		{
			D[s] = matrix[i][a];
//			cout << D[s] << " ";
			a++;
			s++;
		}
//		cout << endl;
		b++;
	}
}

void leftdiag(int** matrix, int* D, int N)
{
	int i, j, a, s = 0;
	cout << "left diagonal" << endl;
	for(j = 0; j <= N - 1; j++)
	{
		a = j;
		for(i = 0; i <= j; i++)
		{
			D[s] = matrix[i][a];
//			cout << D[s] << " ";
			a--;
			s++;
		}
//		cout << endl;
	}
	for(j = 1; j <= N - 1; j++)
	{
		a = N - 1;
		for(i = j; i <= N - 1; i++)
		{
			D[s] = matrix[i][a];
//			cout << D[s] << " ";
			a--;
			s++;
		}
//		cout << endl;
	}
}

void printMatrix(int** matrix, int N)
{
	cout << "matrix " << N << "*" << N << endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
		   	cout << matrix[i][j] << " ";
		}
   cout << endl;
	}
}

void printMasive(int *D, int N)
{
//	cout << "masive" << endl;
	for(int j = 0; j < N*N ; j++)
		cout << D[j] << " ";
	cout << endl;
}

int main()
{
	srand(time(NULL));
	int N = rand() % 10;
	int maxValue = 9;
	int** matrix = genMatrix(N, maxValue);
	printMatrix(matrix, N);
	int *D = initmasive(N);  
	spiral(matrix, D, N);
	printMasive(D, N);
	delete(D);
	D = initmasive(N);
	vint(matrix, D, N);
	printMasive(D, N);
	delete(D);
	D = initmasive(N);
	rightdiag(matrix, D, N);
	printMasive(D, N);
	delete(D);
	D = initmasive(N);
	leftdiag(matrix, D, N);
	printMasive(D, N);
	for(int i = 0; i < N; i++)
	{
		delete(matrix[i]);
	}
	delete(matrix);
	delete(D);
	return 0;
}
