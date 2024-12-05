#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BinarySearchTree.h"

template <typename T>
class AVLTree : public BinarySearchTree<T> {
private:
    using typename BinarySearchTree<T>::Node;

    // Utility functions specific to AVL tree
    int height(Node* node) const;
    int getBalanceFactor(Node* node) const;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);

    // Overridden recursive insert
    Node* insert(Node* node, const T& value);
    Node* remove(Node* node, const T& value);

public:
    AVLTree();
    virtual ~AVLTree();

    // Overridden insert and remove functions
    virtual void insert(const T& value) override;
    virtual bool remove(const T& value) override;
};

// Constructor
template <typename T>
AVLTree<T>::AVLTree() : BinarySearchTree<T>() {}

// Destructor
template <typename T>
AVLTree<T>::~AVLTree() {}

// Calculate the height of a node
template <typename T>
int AVLTree<T>::height(Node* node) const {
    if (!node) return 0;
    return std::max(height(node->left), height(node->right)) + 1;
}

// Calculate the balance factor of a node
template <typename T>
int AVLTree<T>::getBalanceFactor(Node* node) const {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

// Right rotation
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

// Left rotation
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

// Balance a node
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);

    // Left-heavy
    if (balanceFactor > 1) {
        // Left-Right Case: Perform left rotation on left child first
        if (getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        // Left-Left Case: Perform right rotation
        return rotateRight(node);
    }

    // Right-heavy
    if (balanceFactor < -1) {
        // Right-Left Case: Perform right rotation on right child first
        if (getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        // Right-Right Case: Perform left rotation
        return rotateLeft(node);
    }

    return node; // Node is already balanced
}


// Recursive insert with balancing
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::insert(Node* node, const T& value) {
    if (!node) return new Node(value);

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    } else {
        return node; // Duplicates are not allowed
    }

    return balance(node);
}

// Recursive remove with balancing
template <typename T>
typename AVLTree<T>::Node* AVLTree<T>::remove(Node* node, const T& value) {
    if (!node) return nullptr;

    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        // Node with one or no child
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }

        // Node with two children: Get the inorder successor
        Node* successor = node->right;
        while (successor->left) successor = successor->left;

        node->data = successor->data;
        node->right = remove(node->right, successor->data);
    }

    return balance(node);
}

// Public insert
template <typename T>
void AVLTree<T>::insert(const T& value) {
    this->root = insert(this->root, value);
}

// Public remove
template <typename T>
bool AVLTree<T>::remove(const T& value) {
    if (this->search(value)) {
        this->root = remove(this->root, value);
        return true;
    }
    return false;
}

#endif