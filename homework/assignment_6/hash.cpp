/*
* This hash_table class contains suppot for linear probing, 
* quadratic probing, and dubbleHash methods.
*/

#include <iostream>
#include <list>

#define EMPTY_ELEMENT -1
#define C1 0
#define C2 1

#define LINEAR_PROB_FORMULA k+i
#define QUAD_PROB_FORMULA k+(C1*i)+(C2*(i*i))

enum collision_option {linearProbing, quadraticProbing, dubbleHash};

class hash_table
{
private:
    int            _tblSize; // length of the table
    std::vector<int>   _tbl; // vector of values
    collision_option _cType; // how collisions will be handled
    int              _tblCt; // how many elemnts are in the table

    int hash_function(int x)
    {
        return (x % 10);
    }

    int dubble_hash_function(int x)
    {
        return (7 - (x % 7));
    }

    void handle_collision(int k)
    {
        switch (_cType)
        {
        case collision_option::linearProbing:
            linear_probing(k);
            break;
        case collision_option::quadraticProbing:
            quadratic_probing(k);
            break;
        case collision_option::dubbleHash:
            dubbleHash(k);
            break;       
        default:
            break;
        }
    }

    void linear_probing(int k)
    {
        int i = 1;

        while (hash_function(LINEAR_PROB_FORMULA) < _tblSize) {
            if (_tbl[hash_function(LINEAR_PROB_FORMULA)] == EMPTY_ELEMENT) {
                _tbl[hash_function(LINEAR_PROB_FORMULA)] = k;
                break;
            }
            i++;
        }
    }

    void quadratic_probing(int k)
    {
        int i = 1;

        while (hash_function(QUAD_PROB_FORMULA) < _tblSize) {
            if (_tbl[hash_function(QUAD_PROB_FORMULA)] == EMPTY_ELEMENT) {
                _tbl[hash_function(QUAD_PROB_FORMULA)] = k;
                break;
            }
            i++;
        }
    }

    void dubbleHash(int k)
    {
        int newHash = 0;
        int i = 1;

        while (1) {
            newHash = hash_function(hash_function(k) + i*dubble_hash_function(k));
            if (_tbl[hash_function(newHash)] != EMPTY_ELEMENT) {
                i++;
            } else {
                _tbl[hash_function(newHash)] = k;
                break;
            }
        }
    }
public:
    hash_table(int tblSize, collision_option collisionOption)
    {
        _tblCt = 0;
        _tblSize = tblSize;
        _cType = collisionOption;
        _tbl.resize(tblSize, EMPTY_ELEMENT); // reserve the amount of data we would like to fit into the table
    }

    void insert(int k)
    {
        if (_tblCt < _tblSize) {
            if (_tbl[hash_function(k)] != EMPTY_ELEMENT) {
                handle_collision(k);
            } else {
                _tbl[hash_function(k)] = k;
            }
        } else {
            throw std::runtime_error("Table has exceeded max elemnts");
        }
        _tblCt++;
    }

    int search(int k)
    {
        int j = hash_function(k);

        if (_tbl[j] == k) {
            return j;
        } else {
            return -1;
        }
    }

    void print_tbl()
    {
        for (int i = 0; i < _tblSize; ++i) {
            std::cout << _tbl[i] << std::endl;
        }
    }

};

int main (void)
{
    hash_table htbl(10, collision_option::dubbleHash);

    htbl.insert(89);
    htbl.insert(18);
    htbl.insert(49);
    htbl.insert(58);
    htbl.insert(69);
    htbl.insert(69);
    htbl.print_tbl();

    return 0;
}