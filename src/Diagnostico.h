#ifndef DIAGNOSTICO_H
#define DIAGNOSTICO_H

#include <string>
#include <vector>
#include <algorithm>

class Diagnostico {
public:
    Diagnostico() = default;
    Diagnostico(const std::string &codigo, const std::string &nombre, int frecuencia = 1)
        : codigo(codigo), nombre(nombre), frecuencia(frecuencia) {}

    const std::string &getCodigo() const { return codigo; }
    const std::string &getNombre() const { return nombre; }
    int getFrecuencia() const { return frecuencia; }

    void incrementar(int v = 1) { frecuencia += v; }

private:
    std::string codigo;
    std::string nombre;
    int frecuencia = 0;
};

// Un AVL simple que indexa diagnósticos por código y acumula frecuencias.
class DiagnosticoAVL {
    struct Node {
        std::string key;
        int freq;
        int height;
        Node *left, *right;
        Node(const std::string &k): key(k), freq(1), height(1), left(nullptr), right(nullptr) {}
    };

public:
    DiagnosticoAVL(): root(nullptr) {}
    ~DiagnosticoAVL() { clear(root); }

    void insertarOIncrementar(const std::string &codigo) { root = insert(root, codigo); }

    // Recolecta pares (codigo, frecuencia) en in-order
    std::vector<std::pair<std::string,int>> inOrder() const {
        std::vector<std::pair<std::string,int>> out;
        inorder(root, out);
        return out;
    }

private:
    Node *root;

    void inorder(Node *n, std::vector<std::pair<std::string,int>> &out) const {
        if (!n) return;
        inorder(n->left, out);
        out.emplace_back(n->key, n->freq);
        inorder(n->right, out);
    }

    void clear(Node *n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    int height(Node *n) const { return n ? n->height : 0; }
    int bf(Node *n) const { return n ? height(n->left) - height(n->right) : 0; }

    void updateHeight(Node *n) { if (n) n->height = 1 + std::max(height(n->left), height(n->right)); }

    Node* rotateRight(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y); updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x); updateHeight(y);
        return y;
    }

    Node* insert(Node *node, const std::string &key) {
        if (!node) return new Node(key);
        if (key == node->key) { node->freq++; return node; }
        if (key < node->key) node->left = insert(node->left, key);
        else node->right = insert(node->right, key);

        updateHeight(node);
        int balance = bf(node);
        if (balance > 1 && key < node->left->key) return rotateRight(node);
        if (balance < -1 && key > node->right->key) return rotateLeft(node);
        if (balance > 1 && key > node->left->key) { node->left = rotateLeft(node->left); return rotateRight(node); }
        if (balance < -1 && key < node->right->key) { node->right = rotateRight(node->right); return rotateLeft(node); }
        return node;
    }
};

#endif // DIAGNOSTICO_H
