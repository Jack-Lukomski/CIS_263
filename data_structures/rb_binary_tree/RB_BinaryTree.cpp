#include "RB_BinaryTree.hpp"

RB_BinaryTree::RB_BinaryTree()
{
    _head = new RB_Node(0, nullptr, nullptr, nullptr, RB_Color::BLACK);
}

RB_BinaryTree::RB_BinaryTree(int headVal)
{
    _head = new RB_Node(headVal, nullptr, nullptr, nullptr, RB_Color::BLACK);
}

RB_Node *RB_BinaryTree::getHead() 
{
    return _head;
}

void RB_BinaryTree::insert(int val)
{
    
}

void RB_BinaryTree::print()
{
    inorderTreeWalkPrint(_head);
}

void RB_BinaryTree::inorderTreeWalkPrint(RB_Node *n)
{
    if (n != nullptr) {
        inorderTreeWalkPrint(n->getLeft());
        std::cout << n->getData() << " ";
        inorderTreeWalkPrint(n->getRight());
    }
}