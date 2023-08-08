#include <iostream>
#include <map>
#include <vector>

class Knapsack
{
private:
    int             _knapsackCap; // size of the knapsack
    int                       _n; // num items
    std::map<int, int> _knapsack; // map that stores all values and weights

public:
    Knapsack(std::vector<int> values, std::vector<int> weights, int knapsackSize)
    {
        if (values.size() != weights.size()) {
            throw new std::runtime_error("weights and values size does not match\n");
        }

        _n = values.size();
        _knapsackCap = knapsackSize;

        for (int i = 0; i < _n; i++) {
            _knapsack[values[i]] = weights[i];
        }
    }

    int knapsack()
    {
        std::vector<std::vector<int> > K(_n + 1, std::vector<int>(_knapsackCap + 1));

        for (int i = 0; i <= _n; i++)
        {
            for (int w = 0; w <= _knapsackCap; w++)
            {
                if (i == 0 || w == 0)
                    K[i][w] = 0;
                else
                {
                    auto it = std::next(_knapsack.begin(), i - 1);
                    int value = it->first;
                    int weight = it->second;

                    if (weight <= w)
                        K[i][w] = std::max(value + K[i - 1][w - weight], K[i - 1][w]);
                    else
                        K[i][w] = K[i - 1][w];
                }
            }
        }

        return K[_n][_knapsackCap];
    }

    void print()
    {
        std::cout << "Knapsack Capacity: " << _knapsackCap << "\n";
        std::cout << "Number of Items: " << _n << "\n";
        std::cout << "Values and Weights:\n";
        for(const auto& item: _knapsack) {
            std::cout << "Value: " << item.first << ", Weight: " << item.second << "\n";
        }
    }
};

int knap1Sz = 11;
int values1[] = {1, 6, 18, 22, 28};
int weights1[] = {1, 2, 5, 6, 7};

int knap2Sz = 10000;
int values2[] = {16808, 50074, 8931, 27545, 77924, 64441, 84493, 7988, 82328, 78841, 44304, 17710, 29561, 93100, 51817, 99098, 13513, 23811, 80980, 36580, 11968, 1394, 25486, 25229, 40195, 35002, 16709, 15669, 88125, 9531, 27723, 28550};
int weights2[] = {250, 659, 273, 879, 710, 166, 43, 504, 730, 613, 170, 158, 934, 279, 336, 827, 268, 634, 150, 822, 673, 337, 746, 92, 358, 154, 945, 491, 197, 904, 667, 25};

int main(void)
{
    std::vector<int> v1(values1, values1 + sizeof(values1) / sizeof(int));
    std::vector<int> w1(weights1, weights1 + sizeof(weights1) / sizeof(int));

    Knapsack k1(v1, w1, knap1Sz);
    std::cout << "Question 1: " << k1.knapsack() << std::endl;

    std::vector<int> v2(values2, values2 + sizeof(values2) / sizeof(int));
    std::vector<int> w2(weights2, weights2 + sizeof(weights2) / sizeof(int));

    Knapsack k2(v2, w2, knap2Sz);
    std::cout << "Question 2: " << k2.knapsack() << std::endl;

    return 0;
}