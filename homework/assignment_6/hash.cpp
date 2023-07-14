/*
* This hash_table class contains suppot for linear probing, 
* quadratic probing, and dubbleHash methods.
*/
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>

#define PART_1 0
#define PART_2 1

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
    int               _numC; // The number of collisions

    int hash_function(int x)
    {
        return (x % _tblSize);
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
            _numC++;
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
            _numC++;
            i++;
        }
    }

    void dubbleHash(int k)
    {
        int newHash = 0;
        int i = 1;

        while (i < _tblSize) {
            newHash = hash_function(hash_function(k) + i*dubble_hash_function(k));
            if (_tbl[newHash] != EMPTY_ELEMENT) {
                i++;
                _numC++;
            } else {
                _tbl[newHash] = k;
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
        _numC = 0;
    }

    void insert(int k)
    {
        if (_tblCt < _tblSize) {
            if (_tbl[hash_function(k)] != EMPTY_ELEMENT) {
                _numC++;
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
        int i = 0;
        int j = hash_function(k);
        do {
            if (_tbl[j] == k) {
                return j;
            }
            i++;
            if(_cType == collision_option::linearProbing){
                j = hash_function(LINEAR_PROB_FORMULA);
            } else if(_cType == collision_option::quadraticProbing){
                j = hash_function(QUAD_PROB_FORMULA);
            } else if(_cType == collision_option::dubbleHash){
                j = hash_function(hash_function(k) + i*dubble_hash_function(k));
            }
        } while (i < _tblSize && _tbl[j] != EMPTY_ELEMENT);
        return -1;
    }

    void print_tbl()
    {
        for (int i = 0; i < _tblSize; ++i) {
            std::cout << _tbl[i] << std::endl;
        }
    }

    int get_collisions() 
    {
        return _numC;
    }

    void clear()
    {
        std::fill(_tbl.begin(), _tbl.end(), EMPTY_ELEMENT);
        _tblCt = 0;
        _numC = 0;
    }
};

#if PART_1

static const int input[] = {4371, 1323, 6173, 4199, 4344, 9679, 1989};

int main (void)
{
    hash_table htbl(10, collision_option::dubbleHash);

    for (const auto & num: input) {
        htbl.insert(num);
    }

    htbl.print_tbl();

    return 0;
}

#endif

#if PART_2

int main (void)
{
    srand(static_cast<unsigned>(time(0)));

    hash_table lpht(1001, collision_option::linearProbing);
    hash_table qpht(1001, collision_option::quadraticProbing);
    hash_table dhht(1001, collision_option::dubbleHash);

    int n = 10000;
    int lp_avg = 0;
    int qp_avg = 0;
    int dh_avg = 0;

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < 500; ++i) {
            int randNum = rand() % (10000 - 0 + 1) + 0;
            lpht.insert(randNum);
            qpht.insert(randNum);
            dhht.insert(randNum);
        }

        lp_avg += lpht.get_collisions();
        qp_avg += qpht.get_collisions();
        dh_avg += dhht.get_collisions();

        lpht.clear();
        qpht.clear();
        dhht.clear();
    }

    lp_avg /= n;
    qp_avg /= n;
    dh_avg /= n;

    std::cout << "Averege number of collisions where n = " << n << ":\n";
    std::cout << "Linear Probing: " << lp_avg << "\n";
    std::cout << "Quadratic Probing: " << qp_avg << "\n";
    std::cout << "Dubble Hash: " << dh_avg << std::endl;


    return 0;
}

#endif