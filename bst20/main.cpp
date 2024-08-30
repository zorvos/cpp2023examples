#include <iostream>
#include <memory>    // Za std::unique_ptr
#include <ranges>    // Za std::views::iota
#include <vector>
#include <algorithm>

using namespace std;

// Klasa za čvor u binarnom stablu pretrage
class Node {
public:
    int data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;

    // Konstruktor
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Klasa za binarno stablo pretrage
class BST {
private:
    unique_ptr<Node> root;

    // Privatna pomoćna funkcija za umetanje čvora
    Node* insert(Node* node, int value) {
        if (!node) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left.reset(insert(node->left.release(), value));
        } else if (value > node->data) {
            node->right.reset(insert(node->right.release(), value));
        }

        return node;
    }

    // Privatna pomoćna funkcija za pretragu čvora
    Node* search(Node* node, int value) const {
        if (!node || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left.get(), value);
        } else {
            return search(node->right.get(), value);
        }
    }

    // Privatna pomoćna funkcija za ispis stabla u in-order načinu
    void inOrder(const Node* node) const {
        if (node) {
            inOrder(node->left.get());
            cout << node->data << " ";
            inOrder(node->right.get());
        }
    }

    // Privatna pomoćna funkcija za pronalaženje minimuma u stablu
    Node* findMin(Node* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    // Privatna pomoćna funkcija za brisanje čvora
    Node* remove(Node* node, int value) {
        if (!node) {
            return node;
        }

        if (value < node->data) {
            node->left.reset(remove(node->left.release(), value));
        } else if (value > node->data) {
            node->right.reset(remove(node->right.release(), value));
        } else {
            if (!node->left) {
                return node->right.release();
            } else if (!node->right) {
                return node->left.release();
            }

            Node* temp = findMin(node->right.get());
            node->data = temp->data;
            node->right.reset(remove(node->right.release(), temp->data));
        }

        return node;
    }

public:
    // Konstruktor
    BST() : root(nullptr) {}

    // Funkcija za umetanje čvora
    void insert(int value) {
        root.reset(insert(root.release(), value));
    }

    // Funkcija za pretragu čvora
    bool search(int value) const {
        return search(root.get(), value) != nullptr;
    }

    // Funkcija za ispis stabla u in-order načinu
    void inOrder() const {
        inOrder(root.get());
        cout << endl;
    }

    // Funkcija za brisanje čvora
    void remove(int value) {
        root.reset(remove(root.release(), value));
    }

    // Funkcija za čišćenje stabla
    void clear() {
        root.reset();
    }
};

int main() {
    BST tree;

    // Inicijalizacija stabla sa nekim vrednostima
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    for (int value : values) {
        tree.insert(value);
    }

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

