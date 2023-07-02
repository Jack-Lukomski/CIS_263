#include "BinaryTree.hpp"

BinaryTree::BinaryTree()
{
    Node head(0, nullptr, nullptr);
    _head = &head;
}

BinaryTree::BinaryTree(int headVal)
{
    Node head(headVal, nullptr, nullptr);
    _head = &head;
}

void BinaryTree::insert(int val)
{
    Node *temp = _head;
    Node newNode(val, nullptr, nullptr);

    while (temp != nullptr) {
        if (val >= temp->getData()) {
            temp = temp->getRight();
        } else if (val <= temp->getData()) {
            temp = temp->getLeft();
        }
    }

    temp = &newNode;
}

void BinaryTree::print()
{
    //std::cout << "Head = " << _head->getData() << "\n" << "Right = " << _head->getRight()->getData() << std::endl;
}