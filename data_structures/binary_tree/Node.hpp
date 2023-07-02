#include <iostream>

class Node
{
private:
    int _data;
    Node *_parent;
    Node *_right;
    Node *_left;
public:
    Node(int data, Node *parent, Node *right, Node *left);

    int getData();
    Node *getParent();
    Node *getRight();
    Node *getLeft();

    void setData(int newVal);
    void setParent(Node *newParent);
    void setRight(Node *newRight);
    void setLeft(Node *newLeft);
};