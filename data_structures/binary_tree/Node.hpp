#include <iostream>

class Node
{
private:
    int _data;
    Node *_right;
    Node *_left;
public:
    Node(int data, Node *right, Node *left);
    int getData();
    Node *getRight();
    Node *getLeft();
};