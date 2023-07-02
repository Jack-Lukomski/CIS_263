#include "Node.hpp"

Node::Node(int data, Node *right, Node *left)
{
    _data = data;
    _right = right;
    _left = left;
}

int Node::getData()
{
    return _data;
}

Node *Node::getRight()
{
    return _right;
}

Node *Node::getLeft()
{
    return _left;
}