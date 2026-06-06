#include <iostream>
#include <omp.h>

using namespace std;

const long long NUM_STEPS = 100000000;
double stepSize;

#define PAD 8
#define MAX_THREADS 4
int main()
{
    stepSize = 1.0 / (double)NUM_STEPS;
    cout << "Threads\tPI\t\tTime(sec)" << endl;
    for (int threads = 1; threads <= MAX_THREADS; threads++)
    {
        double partialSum[MAX_THREADS][PAD] = { 0.0 };
        double piValue = 0.0;
        int totalThreads = 0;

        omp_set_num_threads(threads);

        double startTime = omp_get_wtime();

#pragma omp parallel
        {
            int threadId = omp_get_thread_num();
            int currentThreads = omp_get_num_threads();

            if (threadId == 0)
                totalThreads = currentThreads;

            partialSum[threadId][0] = 0.0;

            for (long long index = threadId;
                index < NUM_STEPS;
                index += currentThreads)
            {
                double x = (index + 0.5) * stepSize;
                partialSum[threadId][0] +=
                    4.0 / (1.0 + x * x);
            }
        }
        for (int i = 0; i < totalThreads; i++)
        {
            piValue += partialSum[i][0];
        }

        piValue *= stepSize;

        double finishTime = omp_get_wtime();

        cout << threads << "\t"
            << piValue << "\t\t"
            << (finishTime - startTime)
            << endl;
    }

    return 0;
}
