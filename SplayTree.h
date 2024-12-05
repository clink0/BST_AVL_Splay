#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "BinarySearchTree.h"

template <typename T>
class SplayTree : public BinarySearchTree<T> {
private:
    using typename BinarySearchTree<T>::Node;

    // Utility functions specific to splay tree
    Node* splay(Node* root, const T& value);
    Node* rightRotate(Node* x);
    Node* leftRotate(Node* x);

public:
    SplayTree();
    virtual ~SplayTree();

    // Overridden insert, remove, and search functions
    virtual void insert(const T& value) override;
    virtual bool remove(const T& value) override;
    virtual bool search(const T& value) override;
};

// Constructor
template <typename T>
SplayTree<T>::SplayTree() : BinarySearchTree<T>() {}

// Destructor
template <typename T>
SplayTree<T>::~SplayTree() {}

// Right rotation
template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotation
template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation
template <typename T>
typename SplayTree<T>::Node* SplayTree<T>::splay(Node* root, const T& value) {
    if (!root || root->data == value) return root;

    // Left subtree
    if (value < root->data) {
        if (!root->left) return root;

        // Zig-Zig (Left Left)
        if (value < root->left->data) {
            root->left->left = splay(root->left->left, value);
            root = rightRotate(root);
        }
        // Zig-Zag (Left Right)
        else if (value > root->left->data) {
            root->left->right = splay(root->left->right, value);
            if (root->left->right) root->left = leftRotate(root->left);
        }

        return root->left ? rightRotate(root) : root;
    }

    // Right subtree
    else {
        if (!root->right) return root;

        // Zag-Zig (Right Left)
        if (value < root->right->data) {
            root->right->left = splay(root->right->left, value);
            if (root->right->left) root->right = rightRotate(root->right);
        }
        // Zag-Zag (Right Right)
        else if (value > root->right->data) {
            root->right->right = splay(root->right->right, value);
            root = leftRotate(root);
        }

        return root->right ? leftRotate(root) : root;
    }
}

// Overridden insert
template <typename T>
void SplayTree<T>::insert(const T& value) {
    if (!this->root) {
        this->root = new Node(value);
        return;
    }

    this->root = splay(this->root, value);

    if (this->root->data == value) return; // Value already exists

    Node* newNode = new Node(value);
    if (value < this->root->data) {
        newNode->right = this->root;
        newNode->left = this->root->left;
        this->root->left = nullptr;
    } else {
        newNode->left = this->root;
        newNode->right = this->root->right;
        this->root->right = nullptr;
    }

    this->root = newNode;
}

// Overridden remove
template <typename T>
bool SplayTree<T>::remove(const T& value) {
    if (!this->search(value)) return false;

    this->root = splay(this->root, value);

    Node* temp;
    if (!this->root->left) {
        temp = this->root->right;
    } else {
        temp = splay(this->root->left, value);
        temp->right = this->root->right;
    }

    delete this->root;
    this->root = temp;
    return true;
}

// Overridden search
template <typename T>
bool SplayTree<T>::search(const T& value) {
    if (!this->root) return false;

    this->root = splay(this->root, value);
    return this->root && this->root->data == value;
}

#endif