#include <iostream>
using namespace std;

// Klasa za čvor u binarnom stablu pretrage
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Konstruktor
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Klasa za binarno stablo pretrage
class BST {
private:
    Node* root;

    // Privatna pomoćna funkcija za umetanje čvora
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    // Privatna pomoćna funkcija za pretragu čvora
    Node* search(Node* node, int value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    // Privatna pomoćna funkcija za ispis stabla u in-order načinu
    void inOrder(Node* node) const {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }
    }

    // Privatna pomoćna funkcija za pronalaženje minimuma u stablu
    Node* findMin(Node* node) const {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Privatna pomoćna funkcija za brisanje čvora
    Node* remove(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // Čvor sa samo jednim detetom ili bez deteta
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Čvor sa dva deteta
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

public:
    // Konstruktor
    BST() : root(nullptr) {}

    // Destruktor
    ~BST() {
        clear(root);
    }

    // Funkcija za umetanje čvora
    void insert(int value) {
        root = insert(root, value);
    }

    // Funkcija za pretragu čvora
    bool search(int value) const {
        return search(root, value) != nullptr;
    }

    // Funkcija za ispis stabla u in-order načinu
    void inOrder() const {
        inOrder(root);
        cout << endl;
    }

    // Funkcija za brisanje čvora
    void remove(int value) {
        root = remove(root, value);
    }

    // Funkcija za čišćenje stabla
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // Funkcija za čišćenje stabla
    void clear() {
        clear(root);
        root = nullptr;
    }
};

int main() {
    BST tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "In-Order Traversal: ";
    tree.inOrder();

    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 90: " << (tree.search(90) ? "Found" : "Not Found") << endl;

    tree.remove(20);
    cout << "In-Order Traversal after removing 20: ";
    tree.inOrder();

    tree.remove(30);
    cout << "In-Order Traversal after removing 30: ";
    tree.inOrder();

    tree.remove(50);
    cout << "In-Order Traversal after removing 50: ";
    tree.inOrder();

    return 0;
}

