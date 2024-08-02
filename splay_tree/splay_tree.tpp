#ifndef SPLAYTREE_TPP
#define SPLAYTREE_TPP

template<typename T>
SplayTree<T>::SplayTree() : root(nullptr) {}

template<typename T>
SplayTree<T>::~SplayTree() {
    clear(root);
}

template<typename T>
void SplayTree<T>::insert(const T& value) {
    if (root == nullptr) {
        root = new Node(value);
    } else {
        Node* v = root;
        Node* p = nullptr;

        while (v != nullptr) {
            p = v;
            if (value < v->data) {
                v = v->left;
            } else {
                v = v->right;
            }
        }

        v = new Node(value);
        v->parent = p;

        if (value < p->data) {
            p->left = v;
        } else {
            p->right = v;
        }

        splay(v);
    }
}

template<typename T>
bool SplayTree<T>::find(const T& value) {
    Node* v = root;

    while (v != nullptr) {
        if (v->data < value) {
            v = v->right;
        } else if (v->data > value) {
            v = v->left;
        } else {
            splay(v);
            return true;
        }
    }

    return false;
}

template<typename T>
void SplayTree<T>::zig(Node* x) {
    if (x == x->parent->left) {
        Node* P = x->parent;
        Node* B = x->right;

        x->right = P;
        P->left = B;

        if (B != nullptr) B->parent = P;
        if (P->parent) {
            if (P == P->parent->left) {
                P->parent->left = x;
            } else {
                P->parent->right = x;
            }
        }
        x->parent = P->parent;
        P->parent = x;
    } else {
        Node* P = x->parent;
        Node* B = x->left;

        x->left = P;
        P->right = B;

        if (B != nullptr) B->parent = P;
        if (P->parent) {
            if (P == P->parent->left) {
                P->parent->left = x;
            } else {
                P->parent->right = x;
            }
        }
        x->parent = P->parent;
        P->parent = x;
    }

    if (x->parent == nullptr) {
        root = x;
    }
}

template<typename T>
void SplayTree<T>::zig_zag(Node* x) {
    Node* P = x->parent;
    Node* G = P->parent;

    if (x == P->right) {
        Node* B = x->left;

        x->left = P;
        P->right = B;
        if (B != nullptr) B->parent = P;

        P->parent = x;
        x->parent = G;

        if (G->left == P) {
            G->left = x;
        } else {
            G->right = x;
        }
    } else {
        Node* B = x->right;

        x->right = P;
        P->left = B;
        if (B != nullptr) B->parent = P;

        P->parent = x;
        x->parent = G;

        if (G->left == P) {
            G->left = x;
        } else {
            G->right = x;
        }
    }
}

template<typename T>
void SplayTree<T>::zig_zig(Node* x) {
    Node* P = x->parent;
    Node* G = P->parent;

    if (x == P->right && P == G->right) {
        Node* B = P->left;
        Node* C = x->left;

        x->left = P;
        P->left = G;
        P->right = C;
        G->right = B;

        if (B != nullptr) B->parent = G;
        if (C != nullptr) C->parent = P;

        if (G->parent) {
            if (G == G->parent->left) {
                G->parent->left = x;
            } else {
                G->parent->right = x;
            }
        }
        x->parent = G->parent;
        G->parent = P;
        P->parent = x;
    } else if (x == P->left && P == G->left) {
        Node* B = P->right;
        Node* C = x->right;

        x->right = P;
        P->right = G;
        P->left = C;
        G->left = B;

        if (B != nullptr) B->parent = G;
        if (C != nullptr) C->parent = P;

        if (G->parent) {
            if (G == G->parent->left) {
                G->parent->left = x;
            } else {
                G->parent->right = x;
            }
        }
        x->parent = G->parent;
        G->parent = P;
        P->parent = x;
    }
}

template<typename T>
void SplayTree<T>::splay(Node* x) {
    while (x->parent != nullptr) {
        Node* P = x->parent;
        Node* G = P->parent;

        if (G == nullptr) {
            zig(x);
        } else {
            if ((x == P->left && P == G->left) || (x == P->right && P == G->right)) {
                zig_zig(x);
            } else {
                zig_zag(x);
            }
        }
    }
}

template<typename T>
void SplayTree<T>::clear(Node* vertex) {
    if (vertex == nullptr) return;

    clear(vertex->left);
    clear(vertex->right);

    delete vertex;
}

#endif // SPLAYTREE_TPP
