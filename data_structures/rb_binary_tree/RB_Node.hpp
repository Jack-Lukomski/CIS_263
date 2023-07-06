#include <iostream>

enum class RB_Color {
    BLACK,
    RED,
    NO_COLOR,
};

class RB_Node
{
private:
    int _data;
    RB_Node *_parent;
    RB_Node *_right;
    RB_Node *_left;
    RB_Color _color;
public:
    RB_Node(int data, RB_Node *parent, RB_Node *right, RB_Node *left, RB_Color color);

    int getData();
    RB_Color getColor();
    RB_Node *getParent();
    RB_Node *getRight();
    RB_Node *getLeft();

    void setData(int newVal);
    void setColor(RB_Color newColor);
    void setParent(RB_Node *newParent);
    void setRight(RB_Node *newRight);
    void setLeft(RB_Node *newLeft);
};