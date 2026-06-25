#ifndef DIAGNOSTICO_H
#define DIAGNOSTICO_H

#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

// Clase base de datos para un diagnóstico
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

// ============================================================
// BST simple (sin balanceo) para diagnósticos
// Ordenado por código (string), acumula frecuencias.
// ============================================================
class DiagnosticoBST {
    struct Node {
        std::string key;
        int freq;
        Node *left, *right;
        Node(const std::string &k): key(k), freq(1), left(nullptr), right(nullptr) {}
    };

public:
    DiagnosticoBST(): root(nullptr) {}
    ~DiagnosticoBST() { clear(root); }

    // Inserta un nuevo diagnóstico o incrementa su frecuencia si ya existe
    void insertarOIncrementar(const std::string &codigo) {
        root = insert(root, codigo);
    }

    // Elimina un diagnóstico del árbol manteniendo la propiedad BST
    // Retorna true si se encontró y eliminó, false si no existía
    bool eliminar(const std::string &codigo) {
        bool encontrado = false;
        root = remove(root, codigo, encontrado);
        return encontrado;
    }

    // Recorre el árbol inorder y devuelve pares (codigo, frecuencia)
    std::vector<std::pair<std::string,int>> inOrder() const {
        std::vector<std::pair<std::string,int>> out;
        inorder(root, out);
        return out;
    }

    // Encuentra el diagnóstico con mayor frecuencia recorriendo todo el árbol
    // Lanza excepción si el árbol está vacío
    std::pair<std::string,int> masFrecuente() const {
        if (!root) throw std::runtime_error("Arbol vacio");
        std::string bestKey;
        int bestFreq = -1;
        findMax(root, bestKey, bestFreq);
        return {bestKey, bestFreq};
    }

    // Retorna la altura del árbol (0 si está vacío)
    int getAltura() const {
        return height(root);
    }

    // Detecta si el árbol está desbalanceado
    // (algún subárbol con diferencia de alturas > 2)
    bool estaDesbalanceado() const {
        return checkImbalance(root);
    }

    // Retorna true si el árbol está vacío
    bool vacio() const {
        return root == nullptr;
    }

private:
    Node *root;

    int height(Node *n) const {
        if (!n) return 0;
        return 1 + std::max(height(n->left), height(n->right));
    }

    void inorder(Node *n, std::vector<std::pair<std::string,int>> &out) const {
        if (!n) return;
        inorder(n->left, out);
        out.emplace_back(n->key, n->freq);
        inorder(n->right, out);
    }

    void findMax(Node *n, std::string &bestKey, int &bestFreq) const {
        if (!n) return;
        if (n->freq > bestFreq) {
            bestFreq = n->freq;
            bestKey = n->key;
        }
        findMax(n->left, bestKey, bestFreq);
        findMax(n->right, bestKey, bestFreq);
    }

    bool checkImbalance(Node *n) const {
        if (!n) return false;
        int diff = height(n->left) - height(n->right);
        if (diff > 2 || diff < -2) return true;
        return checkImbalance(n->left) || checkImbalance(n->right);
    }

    void clear(Node *n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    Node* insert(Node *node, const std::string &key) {
        if (!node) return new Node(key);
        if (key == node->key) { node->freq++; return node; }
        if (key < node->key) node->left = insert(node->left, key);
        else node->right = insert(node->right, key);
        return node;
    }

    // Encuentra el nodo con la clave mínima en un subárbol
    Node* findMin(Node *n) const {
        while (n && n->left) n = n->left;
        return n;
    }

    // Eliminación estándar BST:
    // Caso 0 hijos: eliminar nodo
    // Caso 1 hijo: reemplazar por el hijo
    // Caso 2 hijos: reemplazar por sucesor inorder (mínimo del subárbol derecho)
    Node* remove(Node *node, const std::string &key, bool &encontrado) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key, encontrado);
        } else if (key > node->key) {
            node->right = remove(node->right, key, encontrado);
        } else {
            // Encontrado
            encontrado = true;

            // Caso 0 o 1 hijo
            if (!node->left) {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            // Caso 2 hijos: sucesor inorder
            Node *sucesor = findMin(node->right);
            node->key = sucesor->key;
            node->freq = sucesor->freq;
            node->right = remove(node->right, sucesor->key, encontrado);
        }
        return node;
    }
};

// ============================================================
// AVL balanceado para diagnósticos
// Mismo interfaz que DiagnosticoBST pero con rotaciones automáticas.
// ============================================================
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

    // Inserta un nuevo diagnóstico o incrementa su frecuencia si ya existe
    void insertarOIncrementar(const std::string &codigo) {
        root = insert(root, codigo);
    }

    // Elimina un diagnóstico del árbol manteniendo balance AVL
    bool eliminar(const std::string &codigo) {
        bool encontrado = false;
        root = remove(root, codigo, encontrado);
        return encontrado;
    }

    // Recorre el árbol inorder y devuelve pares (codigo, frecuencia)
    std::vector<std::pair<std::string,int>> inOrder() const {
        std::vector<std::pair<std::string,int>> out;
        inorder(root, out);
        return out;
    }

    // Encuentra el diagnóstico con mayor frecuencia
    std::pair<std::string,int> masFrecuente() const {
        if (!root) throw std::runtime_error("Arbol vacio");
        std::string bestKey;
        int bestFreq = -1;
        findMax(root, bestKey, bestFreq);
        return {bestKey, bestFreq};
    }

    // Retorna la altura del árbol
    int getAltura() const {
        return root ? root->height : 0;
    }

    // Detecta si está desbalanceado (en un AVL correcto, siempre debería dar false)
    bool estaDesbalanceado() const {
        return checkImbalance(root);
    }

    // Retorna true si el árbol está vacío
    bool vacio() const {
        return root == nullptr;
    }

private:
    Node *root;

    void inorder(Node *n, std::vector<std::pair<std::string,int>> &out) const {
        if (!n) return;
        inorder(n->left, out);
        out.emplace_back(n->key, n->freq);
        inorder(n->right, out);
    }

    void findMax(Node *n, std::string &bestKey, int &bestFreq) const {
        if (!n) return;
        if (n->freq > bestFreq) {
            bestFreq = n->freq;
            bestKey = n->key;
        }
        findMax(n->left, bestKey, bestFreq);
        findMax(n->right, bestKey, bestFreq);
    }

    bool checkImbalance(Node *n) const {
        if (!n) return false;
        int diff = height(n->left) - height(n->right);
        if (diff > 2 || diff < -2) return true;
        return checkImbalance(n->left) || checkImbalance(n->right);
    }

    void clear(Node *n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    int height(Node *n) const { return n ? n->height : 0; }
    int bf(Node *n) const { return n ? height(n->left) - height(n->right) : 0; }

    void updateHeight(Node *n) {
        if (n) n->height = 1 + std::max(height(n->left), height(n->right));
    }

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

    // Balancea un nodo después de inserción o eliminación
    Node* balance(Node *node) {
        updateHeight(node);
        int b = bf(node);

        // Rotación derecha (LL)
        if (b > 1 && bf(node->left) >= 0) return rotateRight(node);
        // Rotación izquierda-derecha (LR)
        if (b > 1 && bf(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Rotación izquierda (RR)
        if (b < -1 && bf(node->right) <= 0) return rotateLeft(node);
        // Rotación derecha-izquierda (RL)
        if (b < -1 && bf(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node *node, const std::string &key) {
        if (!node) return new Node(key);
        if (key == node->key) { node->freq++; return node; }
        if (key < node->key) node->left = insert(node->left, key);
        else node->right = insert(node->right, key);
        return balance(node);
    }

    Node* findMin(Node *n) const {
        while (n && n->left) n = n->left;
        return n;
    }

    // Eliminación AVL: elimina el nodo y rebalancea en el camino de vuelta
    Node* remove(Node *node, const std::string &key, bool &encontrado) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key, encontrado);
        } else if (key > node->key) {
            node->right = remove(node->right, key, encontrado);
        } else {
            encontrado = true;

            if (!node->left) {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node *temp = node->left;
                delete node;
                return temp;
            }

            Node *sucesor = findMin(node->right);
            node->key = sucesor->key;
            node->freq = sucesor->freq;
            node->right = remove(node->right, sucesor->key, encontrado);
        }

        if (!node) return nullptr;
        return balance(node);
    }
};

#endif // DIAGNOSTICO_H
