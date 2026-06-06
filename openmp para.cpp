#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    // طباعة رقم الـ Master Thread (الخيط الرئيسي)
    cout << "Master Thread ID : " << omp_get_thread_num() << endl;

    // طباعة أقصى عدد من الخيوط (Threads) المتاحة
    cout << "Maximum Available Threads : " << omp_get_max_threads() << endl;

    // عدد الخيوط الحالية قبل الدخول إلى المنطقة المتوازية
    cout << "Current Threads Before Parallel Region : "
        << omp_get_num_threads() << endl;

    // يمكن استخدام هذا السطر لتحديد عدد الخيوط افتراضياً
    // omp_set_num_threads(5);

    // ما زال التنفيذ تسلسلياً، لذلك سيكون عدد الخيوط = 1
    cout << "Current Threads After Configuration : "
        << omp_get_num_threads() << endl;

    // إنشاء منطقة متوازية تحتوي على 6 Threads
#pragma omp parallel num_threads(6)
    {
        // الحصول على معرف (ID) الخيط الحالي
        int threadID = omp_get_thread_num();

        // طباعة رقم الخيط
        cout << "Thread ID : " << threadID << endl;

        // طباعة عدد الخيوط داخل المنطقة المتوازية
        cout << "Number of Threads Inside Parallel Region : "
            << omp_get_num_threads() << endl;
    }

    return 0;
}