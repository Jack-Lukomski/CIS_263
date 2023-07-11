#include "RB_Node.hpp"
#include <iostream>

class RB_BinaryTree
{
private:
    RB_Node *_head;
    RB_Node *_nil;
    void inorderTreeWalkPrint(RB_Node *n);
public:
    RB_BinaryTree();
    RB_BinaryTree(int headVal);
    RB_Node *getHead();
    void RB_insert(int val);
    void RB_insertFixup(RB_Node *z);
    void RB_leftRotate(RB_Node *x);
    void RB_rightRotate(RB_Node *x);
    void print();
};