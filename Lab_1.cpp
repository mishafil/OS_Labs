//
//code to finding Taylor expansion in threads
//
#include <iostream>
#include <windows.h>
#include <process.h>
#include <ctime>
#include <cmath>
#include <chrono>


#define eps 2E-7
#define L 10000000

int THREADS_NUMBER;

unsigned int __stdcall Taylor(void* data)
{

    double x = -0.999;
    double res;

    for (int i = (int) data; i < (int) data + (L/THREADS_NUMBER); i++)
    {
        if (x >= 1.0)
        {
            break;
        }
        else
        {
            res = (pow((1 - abs(x)), (1.0 / 3)));
            x += eps;
            //for one thread next line will make output
            //std::cout << x << " " << res << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    std::cout << "Enter num of threads: " << std::endl;
    std::cin >> THREADS_NUMBER;

    HANDLE myhandle[THREADS_NUMBER];

    clock_t tStart = clock();

    for (int i = 0; i < THREADS_NUMBER; i++)
    {
        myhandle[i] = (HANDLE)_beginthreadex(0, 0, &Taylor, (void*)((L*(i+1)/THREADS_NUMBER)), 0, 0);
    }

    WaitForMultipleObjects(THREADS_NUMBER, myhandle,TRUE, INFINITE);

    std::cout << "Threads: " << THREADS_NUMBER << std::endl ;
    std::cout << "Time taken: " << (double)(clock() - tStart)/CLOCKS_PER_SEC << std::endl;

    return 0;
}
