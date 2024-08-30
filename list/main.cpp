#include <iostream>
using namespace std;

// Klasa za čvor u povezanoj listi
class Node {
public:
    int data;
    Node* next;

    // Konstruktor
    Node(int val) : data(val), next(nullptr) {}
};

// Klasa za povezanu listu
class LinkedList {
private:
    Node* head;

public:
    // Konstruktor
    LinkedList() : head(nullptr) {}

    // Destruktor
    ~LinkedList() {
        clear();
    }

    // Dodavanje čvora na početak liste
    void prepend(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Dodavanje čvora na kraj liste
    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Brisanje prvog pojavljivanja vrednosti
    void deleteValue(int value) {
        if (!head) return;

        // Ako je prvi čvor onaj koji treba obrisati
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        // Ako je čvor sa zadatom vrednošću pronađen
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // Ispis liste
    void printList() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Čišćenje liste
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    list.append(1);
    list.append(2);
    list.append(3);
    list.prepend(0);

    cout << "List after appending and prepending: ";
    list.printList();

    list.deleteValue(2);
    cout << "List after deleting 2: ";
    list.printList();

    list.clear();
    cout << "List after clearing: ";
    list.printList();

    return 0;
}
