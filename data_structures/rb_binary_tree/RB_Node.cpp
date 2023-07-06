#include "RB_Node.hpp"

RB_Node::RB_Node(int data, RB_Node *parent, RB_Node *right, RB_Node *left, RB_Color color)
{
    _data = data;
    _parent = parent;
    _right = right;
    _left = left;
    _color = color;
}

int RB_Node::getData()
{
    return _data;
}

RB_Color RB_Node::getColor()
{
    return _color;
}

RB_Node *RB_Node::getParent()
{
    return _parent;
}

RB_Node *RB_Node::getRight()
{
    return _right;
}

RB_Node *RB_Node::getLeft()
{
    return _left;
}

void RB_Node::setData(int newVal)
{
    _data = newVal;
}

void RB_Node::setColor(RB_Color newColor)
{
    _color = newColor;
}

void RB_Node::setParent(RB_Node *parent)
{
    _parent = parent;
}

void RB_Node::setRight(RB_Node *newRight)
{
    _right = newRight;
}

void RB_Node::setLeft(RB_Node *newLeft)
{
    _left = newLeft;
}