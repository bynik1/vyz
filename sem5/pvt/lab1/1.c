#include <mpi.h>
#include <stdio.h>

int main(int argc, char**argv){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    return 0;
}