#include "RB_Node.hpp"
#include <iostream>

class RB_BinaryTree
{
private:
    RB_Node *_head;
    void inorderTreeWalkPrint(RB_Node *n);
public:
    RB_BinaryTree();
    RB_BinaryTree(int headVal);
    RB_Node *getHead();
    void insert(int val);
    void print();
};