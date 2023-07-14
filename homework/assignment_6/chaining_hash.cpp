/*
* This hash_table class contains suppot for linear probing, 
* quadratic probing, and dubbleHash methods.
*/

#include <iostream>
#include <list>

class hash_table
{
private:
    int                      _tblSize; // length of the table
    std::vector<std::list<int> > _tbl; // vector of lists that contain numbers
    int                        _tblCt; // how many elemnts are in the table

    int hash_function(int x)
    {
        return (x % 10);
    }

public:
    hash_table(int tblSize)
    {
        _tblCt = 0;
        _tblSize = tblSize;
        _tbl.resize(tblSize);
    }

    void insert(int k)
    {
        if (_tblCt < _tblSize) {
            _tbl[hash_function(k)].push_front(k);
        } else {
            throw std::runtime_error("Table has exceeded max elemnts");
        }
        _tblCt++;
    }

    int search(int k)
    {
        int j = hash_function(k);

        for (const auto & element: _tbl[j]) {
            if (element == k) {
                return j;
            }
        }
        return -1;
    }

    void print_tbl()
    {
        for (int i = 0; i < _tblSize; ++i) {
            std::cout << "Index " << i << ": ";
            for (const auto & element: _tbl[i]) {
                std::cout << element << " -> ";
            }
            std::cout << "\n";
        }
    }

};

static const int input[] = {4371, 1323, 6173, 4199, 4344, 9679, 1989};

int main (void)
{
    hash_table htbl(10);

    for (const auto & num: input) {
        htbl.insert(num);
    }

    htbl.print_tbl();

    return 0;
}