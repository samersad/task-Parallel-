#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N = 8;

    int data[N];
    int localData;

    double start, finish;

    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
            data[i] = i + 1;

        start = MPI_Wtime();
    }

    int arraySize = N;
    MPI_Bcast(&arraySize, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(data, 1, MPI_INT, &localData, 1, MPI_INT, 0, MPI_COMM_WORLD);

    cout << "Process" << rank << " received" << localData << endl;
    int localSquare = localData * localData;

    int globalSum = 0;

    MPI_Reduce(&localSquare, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    int allSum;

    MPI_Allreduce(&localSquare, &allSum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    int gathered[8];

    MPI_Gather(&localSquare, 1, MPI_INT, gathered, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0)
    {
        finish = MPI_Wtime();
        cout << "\nSquares:\n";
        for (int i = 0; i < size; i++)
            cout << gathered[i] << " ";
        cout << "\n\nSum using Reduce = " << globalSum << endl;

        cout << "Sum using AllReduce = " << allSum << endl;

        cout << "Execution Time = " << finish - start << " sec" << endl;
    }

    MPI_Finalize();

    return 0;
}