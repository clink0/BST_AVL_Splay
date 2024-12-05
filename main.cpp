#include <iostream>
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "SplayTree.h"

void printValue(int& value) {
    std::cout << value << " ";
}

int main() {
    std::cout << "Stress Testing BinarySearchTree" << std::endl;
    BinarySearchTree<int> bst;

    // Test empty tree
    std::cout << "Search in empty BST (expect 0): " << bst.search(10) << std::endl;

    // Insert values
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(15);
    bst.insert(25);
    std::cout << "In-order traversal of BST: ";
    bst.inOrder(printValue);
    std::cout << std::endl;

    // Edge cases
    std::cout << "Insert duplicate (10): ";
    bst.insert(10); // No effect
    bst.inOrder(printValue);
    std::cout << std::endl;

    // Search for existing and non-existing values
    std::cout << "Search for 15 (expect 1): " << bst.search(15) << std::endl;
    std::cout << "Search for 30 (expect 0): " << bst.search(30) << std::endl;

    // Remove nodes
    std::cout << "Remove leaf node (25): ";
    bst.remove(25);
    bst.inOrder(printValue);
    std::cout << std::endl;

    std::cout << "Remove node with one child (20): ";
    bst.remove(20);
    bst.inOrder(printValue);
    std::cout << std::endl;

    std::cout << "Remove node with two children (10): ";
    bst.remove(10);
    bst.inOrder(printValue);
    std::cout << std::endl;

    std::cout << "Remove all nodes (5, 15): ";
    bst.remove(5);
    bst.remove(15);
    bst.inOrder(printValue);
    std::cout << std::endl;

    std::cout << "Stress Testing AVLTree" << std::endl;
    AVLTree<int> avl;

    // Insert values
    for (int i : {10, 20, 30,15, 25, 5, 35, 40, 50, 45, 55}) {
        avl.insert(i);
        std::cout << "Tree structure after inserting " << i << ": " << std::endl;
        avl.printTree();
        std::cout << std::endl;
    }

    // Remove nodes
    for (int i : {25, 40, 50}) {
        avl.remove(i);
        std::cout << "Tree structure after removing " << i << ": " << std::endl;
        avl.printTree();
        std::cout << std::endl;
    }

    // Check tree balancing
    std::cout << "Final AVL tree structure: " << std::endl;
    avl.printTree();
    std::cout << std::endl;

    std::cout << "Stress Testing SplayTree" << std::endl;
    SplayTree<int> splay;

    // Insert values
    for (int i : {10, 20, 30,15, 25, 5, 35, 40, 50, 45, 55, 2, 15}) {
        splay.insert(i);
        std::cout << "Tree structure after inserting " << i << ": " << std::endl;
        splay.printTree();
        std::cout << std::endl;
    }

    // Search values (causing splay operations)
    for (int i : {20, 45, 2, 15, 55}) {
        std::cout << "Search for " << i << ": ";
        std::cout << (splay.search(i) ? "Found" : "Not Found") << std::endl;
        std::cout << "Tree structure after splaying " << i << ": " << std::endl;
        splay.printTree();
        std::cout << std::endl;
    }

    // Remove nodes
    for (int i : {25, 40, 50}) {
        splay.remove(i);
        std::cout << "Tree structure after removing " << i << ": " << std::endl;
        splay.printTree();
        std::cout << std::endl;
    }

    // Final tree state
    std::cout << "Final SplayTree structure: " << std::endl;
    splay.printTree();
    std::cout << std::endl;

    return 0;
}