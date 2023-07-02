#include "BinaryTree.hpp"
#include <iostream>

int main ()
{
    BinaryTree tree(10);
    tree.insert(12);
    tree.insert(8);
    tree.insert(9);
    tree.print();
}