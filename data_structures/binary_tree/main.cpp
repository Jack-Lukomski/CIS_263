#include "BinaryTree.hpp"
#include <iostream>

int main ()
{
    BinaryTree tree(10);
    tree.insert(12);
    tree.insert(8);
    tree.insert(9);
    tree.insert(1);
    tree.insert(2);
    tree.insert(15);
    tree.insert(10);
    tree.print();
}