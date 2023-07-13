#include <iostream>

#include <iostream>

class Bnode
{
    char *_keys; // arr of keys in the curr node
    int      _n; // number of keys in curr node
    int      _t; // min degree of the Btree
    bool  _leaf; // true -> node is a leaf
    Bnode  **_c; // array of children pointers

public:
    Bnode(int temp, bool leaf);
    void insertNonFull(char k);
    void splitChild(Bnode *x, int i);
    void traverse(int level = 0);

    friend class Btree; // letting the Btree class access all private vars of Bnode class
};

class Btree
{
    Bnode  *_root; // head node of the tree
    int        _t; // minimum degree

public:
    Btree(int degree)
    {
        _root = nullptr;
        _t = degree;
    }

    void traverse() {
        if (_root != nullptr) {
            _root->traverse();
        }
    }

    void insert(char k);
};

void Bnode::traverse(int level) {
    int i;
    for (i = 0; i < _n; ++i) {
        if (!_leaf) {
            _c[i]->traverse(level + 1);
        }
        std::cout << "Level: " << level << ", Key: " << _keys[i] << std::endl;
    }
    if (!_leaf) {
        _c[i]->traverse(level + 1);
    }
}

Bnode::Bnode(int t, bool leaf)
{
    _t = t;
    _leaf = leaf;

    _keys = new char[2*t-1];
    _c = new Bnode*[2*t];

    _n = 0;
}

void Bnode::splitChild(Bnode *x, int i)
{
    Bnode *z = new Bnode(x->_t, x->_leaf);
    z->_n = _t - 1;

    for (int j = 0; j < _t-1; ++j) {
        z->_keys[j] = x->_keys[j + _t];
    }

    if (!x->_leaf) {
        for (int j = 0; j < _t; ++j) {
            z->_c[j] = x->_c[j+_t];
        }        
    }

    x->_n = _t - 1;

    for (int j = _n; j >= i + 1; j--) {
        _c[j+1] = _c[j];
    }

    _c[i + 1] = z;

    for (int j = _n - 1; j >= i; j--) {
        _keys[j + 1] = _keys[j];
    }

    _keys[i] = x->_keys[_t-1];
    _n++;
}

void Bnode::insertNonFull(char k)
{
    int i = _n - 1;

    if (_leaf) {
        while (i >= 0 && _keys[i] > k) {
            _keys[i+1] = _keys[i];
            i--;
        }
        _keys[i+1] = k;
        _n++;
    } else {
        while (i >= 0 && _keys[i] > k) {
            i--;
        }

        if (_c[i+1]->_n == 2*_t-1) {
            splitChild(_c[i+1], i+1);
            if (_keys[i+1] < k) {
                i++;
            }
        }
        _c[i+1]->insertNonFull(k);
    }
}

void Btree::insert(char k)
{
    if (_root == nullptr) {
        _root = new Bnode(_t, true);
        _root->_keys[0] = k;
        _root->_n = 1;
    } else {
        if (_root->_n == 2*_t-1) {
            Bnode *s = new Bnode(_t, false);
            s->_c[0] = _root;
            s->splitChild(_root, 0);

            int i = 0;
            if (s->_keys[0] < k) {
                i++;
            }
            s->_c[i]->insertNonFull(k);
            _root = s;
        } else {
            _root->insertNonFull(k);
        }
    }
}

static const char letters[] = {
    'G', 'M', 'P', 'X', 'A', 'C', 'D', 'E', 'J', 'K',
    'N', 'O', 'R', 'S', 'T', 'U', 'V', 'Y', 'Z'
};

int main (void)
{
    Btree tree(6); // max degree is 6 so our nodes can hold m-1 values (5)

    for (const auto & letter: letters) {
        tree.insert(letter);
    }

    tree.traverse();

    std::cout << "Inserting B...\nResult is:" << std::endl;
    tree.insert('B');
    tree.traverse();

    std::cout << "Inserting Q...\nResult is:" << std::endl;
    tree.insert('Q');
    tree.traverse();

    std::cout << "Inserting L...\nResult is:" << std::endl;
    tree.insert('L');
    tree.traverse();

    std::cout << "Inserting F...\nResult is:" << std::endl;
    tree.insert('F');
    tree.traverse();


    return 0;
}