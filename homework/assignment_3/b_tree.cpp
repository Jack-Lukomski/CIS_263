#include "../../data_structures/binary_tree/BinaryTree.hpp"
#include <stdbool.h>
#include <iostream>

bool isValidTree(Node *n);
bool checkOrderProperty(Node *curr, int min, int max);
void inorderTreeWalkPrint(Node *n);

int main (void) 
{
    BinaryTree validTree(12); // making the head of the valid tree 12
    validTree.insert(10);
    validTree.insert(14);
    validTree.insert(13);
    validTree.insert(8);
    validTree.insert(11);

    // Creating an invalid b-tree that is the oppisite of a binary tree - >
    // values less than the parent are on the right and values greater than
    // are on the left. So when printing the values using the inordertreewalk
    // method, they should be in reverse.
    // IVBT -> invalid binary tree
    Node IVBT_Head(12, nullptr, nullptr, nullptr);
    Node IVBT_N1(8, &IVBT_Head, nullptr, nullptr);
    Node IVBT_N2(14, &IVBT_Head, nullptr, nullptr);
    Node IVBT_N3(4, &IVBT_N1, nullptr, nullptr);
    Node IVBT_N4(13, &IVBT_N2, nullptr, nullptr);

    IVBT_Head.setLeft(&IVBT_N2);
    IVBT_Head.setRight(&IVBT_N1);
    IVBT_N2.setRight(&IVBT_N4);
    IVBT_N1.setRight(&IVBT_N3);

    std::cout << "Testing the Valid Binary Tree:\n\tPrinting the values using the inorder tree walk\n\t";
    validTree.print();
    std::cout << "\n\n\tTesting to see if it follows the order property:\n";
    if (isValidTree(validTree.getHead()) == true) {
        std::cout << "\tOrder Property Status: True\n\n";
    } else {
        std::cout << "\tOrder Property Status: False\n\n";
    }

    std::cout << "Testing the invalid Binary Tree:\n\tPrinting the values using the inorder tree walk\n\t";
    inorderTreeWalkPrint(&IVBT_Head);
    std::cout << "\n\n\tTesting to see if it follows the order property:\n";
    if (isValidTree(&IVBT_Head) == true) {
        std::cout << "\tOrder Property Status: True\n\n";
    } else {
        std::cout << "\tOrder Property Status: False\n\n";
    }


    return 0;
}

void inorderTreeWalkPrint(Node *n)
{
    if (n != nullptr) {
        inorderTreeWalkPrint(n->getLeft());
        std::cout << n->getData() << " ";
        inorderTreeWalkPrint(n->getRight());
    }
}

bool isValidTree(Node *n) 
{
    return checkOrderProperty(n, INT_MIN, INT_MAX);
}

bool checkOrderProperty(Node *curr, int min, int max)
{
    if (curr == nullptr) {
        return true;
    }

    if (curr->getData() < min || curr->getData() >= max) {
        return false;
    }

    return (checkOrderProperty(curr->getLeft(), min, curr->getData()) && checkOrderProperty(curr->getRight(), curr->getData(), max));
}