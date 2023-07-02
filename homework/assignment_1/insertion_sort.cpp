#include <iostream>
#include <vector>

#define NUM_INPUT_INTS 5

void intsertSort (std::vector<int> &);
void printVec (const std::vector<int> &);

int main ()
{
    int inputNum;
    std::vector<int> intList;

    std::cout << "Please enter 5 integers";

    for (int i = 0; i < NUM_INPUT_INTS; ++i) { 
        std::cout << "\nnumber " << i << " = ";
        std::cin >> inputNum;
        intList.push_back(inputNum);
        std::cout << "The sorted list is: ";
        intsertSort(intList);
        printVec(intList);
    }
}

void intsertSort (std::vector<int> & list)
{
    int key;
    int j = 0;

    for (int i = 1; i < list.size(); ++i) {
        key = list[i];
        j = i - 1;

        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j--;
            list[j + 1] = key;
        }
    }
}

void printVec (const std::vector<int> & list)
{
    std::cout << "[";
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list[i];

        if (i != list.size()-1) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}