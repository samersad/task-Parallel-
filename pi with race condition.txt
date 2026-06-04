#include <iostream>
#include <omp.h>

using namespace std;

static long long num_steps = 100000000;
double step;
double pi = 0.0;

int main()
{
    step = 1.0 / (double)num_steps;

    omp_set_num_threads(4);

    double start = omp_get_wtime();

#pragma omp parallel for
    for (long long i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * step;

        // Race Condition
        pi += 4.0 / (1.0 + x * x);
    }

    pi *= step;

    double end = omp_get_wtime();

    cout << "PI = " << pi << endl;
    cout << "Execution Time = " << end - start << " seconds" << endl;

    return 0;
}