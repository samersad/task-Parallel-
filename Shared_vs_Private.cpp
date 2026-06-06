#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int imax = 10;
    int ifirst = 10;
    int i2;
    int j[10];

    // بدون private - race condition
#pragma omp parallel for
    for (int i = 0; i < imax; i++) {
        i2 = 2 * i;
        j[i] = ifirst + i2;
    }

    cout << "Without private (may be wrong):" << endl;
    for (int i = 0; i < imax; i++)
        cout << "j[" << i << "] = " << j[i] << endl;

    // مع private - صح
#pragma omp parallel for private(i2)
    for (int i = 0; i < imax; i++) {
        i2 = 2 * i;
        j[i] = ifirst + i2;
    }

    cout << "\nWith private(i2) (correct):" << endl;
    for (int i = 0; i < imax; i++)
        cout << "j[" << i << "] = " << j[i] << endl;

    return 0;
}