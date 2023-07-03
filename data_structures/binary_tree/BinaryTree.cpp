#include "BinaryTree.hpp"

BinaryTree::BinaryTree()
{
    _head = new Node(0, nullptr, nullptr, nullptr);
}

BinaryTree::BinaryTree(int headVal)
{
    _head = new Node(headVal, nullptr, nullptr, nullptr);
}

void BinaryTree::insert(int val)
{
    Node *insertNode = new Node(val, nullptr, nullptr, nullptr);
    Node *temp = _head;

    while (temp != nullptr) {
        if (val < temp->getData()) {
            if (temp->getLeft() == nullptr) {
                temp->setLeft(insertNode);
                insertNode->setParent(temp);
                break;
            }
            temp = temp->getLeft();
        } else if (val >= temp->getData()) {
            if (temp->getRight() == nullptr) {
                temp->setRight(insertNode);
                insertNode->setParent(temp);
                break;
            }
            temp = temp->getRight();
        }
    }
}

void BinaryTree::print()
{
    inorderTreeWalkPrint(_head);
}

void BinaryTree::inorderTreeWalkPrint(Node *n)
{
    if (n != nullptr) {
        inorderTreeWalkPrint(n->getLeft());
        std::cout << n->getData() << std::endl;
        inorderTreeWalkPrint(n->getRight());
    }
}