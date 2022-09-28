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

void spiral(int** matrix, int* D, int N)
{
    int a = 0, b = N - 1, c = 0, d = N - 1;
    int i, j, n = N + 1, s = 0;
    cout << "spiral" << endl;
    for(j = a; j <= b; j++)
    { 
        D[s] = matrix[c][j];
        cout << D[s] << " ";
        s++; 
    }
    cout << endl;
    n--;
    c++;
    while(1)
    {
        if((s >= N * N) || n <= 0)
            break; 
        for(i = c; i <= d; i++)
        {
            D[s] = matrix[i][b];
            cout << D[s] << " ";
            s++;
        }
        cout << endl;
        b--;
        for(j = b; j >= a; j--)
        {
            D[s + b - j] = matrix[d][j];
            cout << D[s + b - j] << " ";
        }
        cout << endl;
        s += b  - a + 1;
        d--;
        n--;
 //       cout << "s " << s <<endl;
        if((s >= N * N) || n <= 0)
            break;

        for(i = d; i >= c; i--)
        {
            D[s + d - i] = matrix[i][a];
            cout << D[s + d - i] << " ";
        }
        cout << endl;
        s += d  - c + 1;
        a++;
        for(j = a; j <= b; j++)
        {
            D[s] = matrix[c][j];
            cout << D[s] << " ";
            s++;
        }
        cout << endl;
        c++;
        n--;
  //      cout << "s " << s <<endl;
        if((s >= N * N) || n <= 0)
            break;


    }
}

void printMatrix(int** matrix, int N)
{
    cout << "matrix" << endl;
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
    cout << "masive" << endl;
    for(int j = 0; j < N*N ; j++)
        cout << D[j] << " ";
}

int main()
{
    srand(time(NULL));
    int N = rand() % 9 + 1;
//    N = 4;
    cout << N << endl;
    int maxValue = 9;
    int** matrix = genMatrix(N, maxValue);
    int *D = new int[N * N];  
    printMatrix(matrix, N);
    spiral(matrix, D, N);
    printMasive(D, N);
    for(int i = 0; i <= N; i++)
    {
        delete(matrix[i]);
    }
    delete(matrix);
    delete(D);
    return 0;
}
