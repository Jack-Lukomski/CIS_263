#include "Node.hpp"

Node::Node(int data, Node *parent, Node *right, Node *left)
{
    _data = data;
    _parent = parent;
    _right = right;
    _left = left;
}

int Node::getData()
{
    return _data;
}

Node *Node::getParent()
{
    return _parent;
}

Node *Node::getRight()
{
    return _right;
}

Node *Node::getLeft()
{
    return _left;
}

void Node::setData(int newVal)
{
    _data = newVal;
}

void Node::setParent(Node *parent)
{
    _parent = parent;
}

void Node::setRight(Node *newRight)
{
    _right = newRight;
}

void Node::setLeft(Node *newLeft)
{
    _left = newLeft;
}