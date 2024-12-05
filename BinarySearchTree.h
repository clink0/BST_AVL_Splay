#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>

using namespace std;

template <typename T>
class BinarySearchTree {
protected:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Utility functions
    void inOrderTraversal(Node* node, void (*visit)(T&)) const;
    void deleteTree(Node* node);

    // Recursive helper for printing tree structure
    void printTree(Node* node, int depth) const;

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    virtual void insert(const T& value);
    virtual bool remove(const T& value);
    virtual bool search(const T& value);

    void inOrder(void (*visit)(T&)) const;

    // Public method to print the tree structure
    void printTree() const;
};

// Constructor
template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {}

// Destructor
template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    deleteTree(root);
}

// Delete all nodes in the tree
template <typename T>
void BinarySearchTree<T>::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Insert a value into the tree
template <typename T>
void BinarySearchTree<T>::insert(const T& value) {
    Node** current = &root;

    while (*current) {
        if (value < (*current)->data)
            current = &(*current)->left;
        else if (value > (*current)->data)
            current = &(*current)->right;
        else
            return; // Value already exists, do nothing
    }

    *current = new Node(value);
}

// Remove a value from the tree
template <typename T>
bool BinarySearchTree<T>::remove(const T& value) {
    Node** current = &root;
    Node* target = nullptr;

    while (*current) {
        if (value < (*current)->data) {
            current = &(*current)->left;
        } else if (value > (*current)->data) {
            current = &(*current)->right;
        } else {
            target = *current;
            break;
        }
    }

    if (!target) return false; // Value not found

    // Case 1: Node has no children
    if (!target->left && !target->right) {
        delete target;
        *current = nullptr;
    }
    // Case 2: Node has one child
    else if (!target->left || !target->right) {
        Node* child = target->left ? target->left : target->right;
        delete target;
        *current = child;
    }
    // Case 3: Node has two children
    else {
        Node** successor = &target->right;
        while ((*successor)->left) {
            successor = &(*successor)->left;
        }
        target->data = (*successor)->data;
        Node* toDelete = *successor;
        *successor = (*successor)->right;
        delete toDelete;
    }

    return true;
}

// Search for a value in the tree
template <typename T>
bool BinarySearchTree<T>::search(const T& value) {
    Node* current = root;

    while (current) {
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
            return true; // Value found
    }

    return false; // Value not found
}

// In-order traversal utility
template <typename T>
void BinarySearchTree<T>::inOrderTraversal(Node* node, void (*visit)(T&)) const {
    if (node) {
        inOrderTraversal(node->left, visit);
        visit(node->data);
        inOrderTraversal(node->right, visit);
    }
}

// Public in-order traversal method
template <typename T>
void BinarySearchTree<T>::inOrder(void (*visit)(T&)) const {
    inOrderTraversal(root, visit);
}

// Recursive helper for printing tree structure
template <typename T>
void BinarySearchTree<T>::printTree(Node* node, int depth) const {
    if (node) {
        printTree(node->right, depth + 1); // Print right subtree
        for (int i = 0; i < depth; ++i) std::cout << "    "; // Indentation
        std::cout << node->data << std::endl; // Print current node
        printTree(node->left, depth + 1); // Print left subtree
    }
}

// Public method to print the tree structure
template <typename T>
void BinarySearchTree<T>::printTree() const {
    if (!root) {
        std::cout << "(empty tree)" << std::endl;
    } else {
        printTree(root, 0);
    }
}

#endif // BINARY_SEARCH_TREE_H
