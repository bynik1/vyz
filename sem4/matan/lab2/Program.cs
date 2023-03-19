using System;
using System.IO;
using System.Xml.Linq;

double[,] matr = new double[,] { { 5, -3, 2, -8, 1 }, { 1, 1, 1, 1, 0 }, { 3, 5, 1, 4, 0 }, { 4, 2, 3, 1, 3 } };

double[] B = { 0, 0, 0, 0 };

double[] X = { 0, 0, 0, 0 };

double[] R = { 0, 0, 0, 0 };

double[] RR = { 0, 0, 0, 0 };

int N = 4;

int I = 3;

double max = -1000000;

void show()  //Вывод матрицы на экран
{
    int i, j;
    //string[] spis = { "x = " , "y = ", "z = ", "m = ", "n = ",  };
    Console.WriteLine("Заданная матрица:");
    Console.WriteLine();
    for (i = 0; i < N; i++)
    {
        for (j = 0; j <= N; j++)
            Console.WriteLine("  {0}", matr[i, j]);

        Console.WriteLine();
    }
}

void show1()  //Вывод матрицы на экран
{
    int i, j;
    //string[] spis = { "x = " , "y = ", "z = ", "m = ", "n = ",  };
    Console.WriteLine("Заданная матрица:");
    Console.WriteLine();
    for (i = 0; i < N; i++)
    {
            Console.WriteLine("  +++++ {0} ++++", X[i]);

        Console.WriteLine();
    }
}

void division()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            if (max <= matr[i, j])
            {
                max = matr[i, j];
            }
        }
        for (int j = 0; j <= N; j++)
        {
            matr[i, j] = matr[i, j] / max;
            B[i] = matr[i, j];
        }
        max = -1000000;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            if (i == j)
            {
                matr[i, j] = 0;
            }
        }
    }
}

void iterations()
{
    
    for (int i = 0; i < N; i++)
    {
        //Console.WriteLine("ssssssssssss");
        for (int j = 0; j < N; j++)
        {
            R[i] = R[i] + matr[i, j] * X[j];
            

        }
        //Console.WriteLine("  ==== {0} =====", R[i]);
        RR[i] = B[i] - R[i];
    }
    for (int i = 0; i < N; i++)
    {
        X[i] = RR[i];
    }
}

int main()
{
    int i;
    double[] out_of = new double[N];

    Console.WriteLine();

    show();
    division();


    //for (i = 0; i < I; i++)
    iterations();
    iterations();

    show1();
    //Console.WriteLine("------- Массив ответов -------:");
    for (i = 0; i < N; ++i)
       Console.WriteLine(" x{0} = {1}", i + 1, X[i]);
    return 0;
}

main();

