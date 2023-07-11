#include "RB_BinaryTree.hpp"

RB_BinaryTree::RB_BinaryTree()
{
    _nil = new RB_Node(nullptr, nullptr, nullptr, RB_Color::BLACK);
    _head = new RB_Node(0, nullptr, nullptr, nullptr, RB_Color::BLACK);
}

RB_BinaryTree::RB_BinaryTree(int headVal)
{
    _head = new RB_Node(headVal, nullptr, nullptr, nullptr, RB_Color::BLACK);
    _nil = new RB_Node(nullptr, nullptr, nullptr, RB_Color::BLACK);
}

RB_Node *RB_BinaryTree::getHead() 
{
    return _head;
}

void RB_BinaryTree::RB_insert(int val)
{
    RB_Node *z = new RB_Node(val, nullptr, nullptr, nullptr, RB_Color::NO_COLOR);
    
    RB_Node *y = _nil;
    RB_Node *x = _head;

    while (x != _nil) {
        y = x;

        if (z->getData() < z->getData()) {
            x = x->getLeft();
        } else {
            x = x->getRight();
        }
    }

    z->setParent(y);

    if (y == _nil) {
        _head = z;
    } else if (z->getData() < y->getData()) {
        y->setLeft(z);
    } else {
        y->setRight(z);
    }

    z->setLeft(_nil);
    z->setRight(_nil);
    z->setColor(RB_Color::RED);
    RB_insertFixup(z);
}

void RB_BinaryTree::RB_insertFixup(RB_Node *z)
{
    while (z->getParent()->getColor() == RB_Color::RED) {
        if (z->getParent() == z->getParent()->getParent()->getLeft()) {
            RB_Node *y = z->getParent()->getParent()->getRight();

            if (y->getColor() == RB_Color::RED) {
                z->getParent()->setColor(RB_Color::BLACK);
                y->setColor(RB_Color::BLACK);
                z->getParent()->getParent()->setColor(RB_Color::RED);
                z = z->getParent()->getParent();
            } else if (z == z->getParent()->getRight()) {
                z = z->getParent();
                RB_leftRotate(z);
            }
            z->getParent()->setColor(RB_Color::BLACK);
            z->getParent()->getParent()->setColor(RB_Color::RED);
            RB_rightRotate(z->getParent()->getParent());
        }
    }
    _head->setColor(RB_Color::BLACK);
}

void RB_BinaryTree::RB_leftRotate(RB_Node *x)
{
    RB_Node *y = x->getRight();
    x->setRight(y->getLeft());

    if (y->getLeft() != _nil) {
        y->getLeft()->setParent(x);
    }

    y->setParent(x->getParent());

    if (x->getParent() == _nil) {
        _head = y;
    } else if (x == x->getParent()->getLeft()) {
        x->getParent()->setLeft(y);
    } else {
        x->getParent()->setRight(y);
    }
    y->setLeft(x);
    x->setParent(y);
}

void RB_BinaryTree::RB_rightRotate(RB_Node *x)
{
    RB_Node *y = x->getRight();
    x->setRight(y->getLeft());

    if (y->getRight() != _nil) {
        y->getRight()->setParent(x);
    }

    y->setParent(x->getParent());

    if (x->getParent() == _nil) {
        _head = y;
    } else if (x == x->getParent()->getRight()) {
        x->getParent()->setRight(y);
    } else {
        x->getParent()->setLeft(y);
    }
    y->setRight(x);
    x->setParent(y);
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