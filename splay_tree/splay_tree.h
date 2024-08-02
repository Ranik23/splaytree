#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include "../concepts/concept.tpp"




template<Comparable T>
class SplayTree {

private:

    struct Node {
        T data;
        Node* left;
        Node* right;
        Node* parent;
        Node(T value) : data(value),
                        left(nullptr),
                        right(nullptr),
                        parent(nullptr) {}
    };

    void zig(Node* x);
    void zig_zag(Node* x);
    void zig_zig(Node* x);
    void splay(Node* x);
    void clear(Node* vertex);

    Node* root;

public:

    SplayTree();
    ~SplayTree();
    void insert(const T& value);
    bool find(const T& value);
};

#include "splay_tree.tpp"

#endif // SPLAYTREE_H
