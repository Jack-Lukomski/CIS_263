#include "Node.hpp"
#include <iostream>

class BinaryTree
{
private:
    Node *_head;
    void inorderTreeWalkPrint(Node *n);
public:
    BinaryTree();
    BinaryTree(int headVal);
    Node *getHead();
    void insert(int val);
    void print();
};