#include <iostream>
#include <random>
#include <time.h>

class MaxHeap 
{
private:
    int     *_arr; // all elements in the heap
    int  _maxSize; // max size of the heap
    int _currSize; // current size of the heap

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    void maxHeapify(int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < _currSize && _arr[left] > _arr[largest]) {
            largest = left;
        }

        if (right < _currSize && _arr[right] > _arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            std::swap(_arr[i], _arr[largest]);
            maxHeapify(largest);
        }
    }

public:

    MaxHeap(int size)
    {
        _maxSize = size;
        _currSize = 0;
        _arr = new int[size];
    }

    MaxHeap(int *arr, int size)
    {
        _maxSize = size;
        _currSize = _maxSize;
        _arr = new int[size];
        memcpy(_arr, arr, sizeof(int) * _maxSize);
        for (int i = _maxSize / 2 - 1; i >= 0; i--) {
            maxHeapify(i);   
        }
    }

    void insert(int x)
    {
        if (_maxSize == _currSize) {
            throw new std::runtime_error("\nOverflow\n");
        }

        // new key is tempary at the end of the array
        _currSize++;
        int i = _currSize - 1;
        _arr[i] = x;

        while (i != 0 && _arr[parent(i)] < _arr[i]) {
            std::swap(_arr[i], _arr[parent(i)]);
            i = parent(i);
        }
    }

    void print()
    {
        std::cout << "[ ";
        for (int i = 0; i < _maxSize; i++) {
            if (i == _maxSize-1) {
                std::cout << _arr[i];
            } else {
                std::cout << _arr[i] << ", ";
            }
        }
        std::cout << " ]" << std::endl;
    }
};

int elements1[] = {1, 2, 3, 4, 5, 6, 7, 8};
int elements2[] = {8, 7, 6, 5, 4, 3, 2, 1};
int N = 8;

int *generateRandomInts(int num, int low, int high);

int main(void)
{

    std::cout << "Elements inserted into the heap data structure one at a time\n";

    std::cout << "\tinserting sorted\n";
    MaxHeap h1(N);
    clock_t start = clock();
    for (const auto & i: elements1) {
        h1.insert(i);
    }
    clock_t end = clock();
    std::cout << "\tThat took: " << end - start << " clock ticks.\n\n";

    std::cout << "\tinserting reverse order\n";
    MaxHeap h2(N);
    start = clock();
    for (const auto & i: elements2) {
        h2.insert(i);
    }
    end = clock();
    std::cout << "\tThat took: " << end - start << " clock ticks.\n\n";

    std::cout << "\tinserting random order\n";
    MaxHeap h3(N);
    int *elements3 = generateRandomInts(8, 0, 100);
    start = clock();
    for (int i = 0; i < N; i++) {
        h3.insert(elements3[i]);
    }
    end = clock();
    std::cout << "\tThat took: " << end - start << " clock ticks.\n\n\n";

    std::cout << "Elements inserted into the heap data structure all at once\n";
    std::cout << "\tinserting sorted\n";
    start = clock();
    MaxHeap h4(elements1, N);
    end = clock();
    std::cout << "\tThat took: " << end - start << " clock ticks.\n\n";

    std::cout << "\tinserting reverse order\n";
    start = clock();
    MaxHeap h5(elements2, N);
    end = clock();
    std::cout << "\tThat took: " << end - start << " clock ticks.\n\n";

    std::cout << "\tinserting random order\n";
    start = clock();
    MaxHeap h6(elements3, N);
    end = clock();
    std::cout << "\tThat took: " << end - start << " clock ticks.\n\n";

    return 0;
}

int *generateRandomInts(int num, int low, int high)
{
    int *result = new int[num];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(low, high);

    for(int n=0; n<num; ++n){
        result[n] = dis(gen);
    }

    return result;
}