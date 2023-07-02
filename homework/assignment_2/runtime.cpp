#include <iostream>
#include <time.h>

void q1 (int n);
void q2 (int n);
void q3 (int n);
void q4 (int n);

void testFunction (void (*testFunctionPtr)(int n));

int main() 
{
    testFunction(q3);

    return 0;
}

void q1 (int n)
{
    int total = 0;

    for (int i = 0; i < n; i++) {
        total++;
    }
}

void q2 (int n)
{
    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { 
            total++; 
        }
    }
}

void q3 (int n)
{
    int total = 0;

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < i; j++) { 
            total++; 
        }
    }
}

void q4 (int n)
{
    int total = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (j % 2 == 0) {
                total++;
            }
        }
    }
}

void testFunction (void (*testFunctionPtr)(int n))
{
    for (int i = 1; i < 1000000; i*=2) {
        clock_t startTime = clock();
        testFunctionPtr(i);
        clock_t endTime = clock();
        std::cout << i << "\t" << endTime-startTime << std::endl;
    }
}