#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *next;

        Node(int val = 0, Node *link = NULL) : data(val), next(link) {};
        ~Node() { delete next; }
};

Node* build(Node *, int);
int len(Node *);
Node* delNode(Node *, int);
void print(Node *);

int main() {
    /**
     * Task is to delete a node from circular linked list
     */ 
    cout << endl << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << endl << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << endl << "The list is: " << endl;
    print(head);

    cout << endl << "Enter number to delete: ";
    int x;
    cin >> x;

    head = delNode(head, x);

    cout << endl << "The list after deletion is:" << endl;
    print(head);

    cout << endl;
    delete head;

    return 0;
}

Node* build(Node *head, int n) {
    // We allocate space to head for a node
    head = new Node();
    Node *temp = head;

    while (n--) {
        // We take input for user for this node
        cin >> temp->data;
        // If we are not at the end then we connect
        // this node to the next else we connect to head
        if (n != 0) temp->next = new Node();
        else temp->next = head;
        temp = temp->next;
    }

    return head;
}

void print(Node *head) {
    Node *temp = head;

    do {
        cout << temp->data;
        // This will print a seperator for each element of the list
        if (temp->next != head) cout << " > ";
        temp = temp->next;
    } while (temp != head);

    cout << endl;
}

int len(Node *head) {
    int sz = 0;
    while (head) {
        // Traverse till head and count all the same
        sz += 1;
        head = head->next;
    }
    return sz;
}

Node* delNode(Node *head, int x) {
    // There is no node to delete
    if (!head) return head;

    if (head->data == x) {
        // Case when we are deleting head itself
        if (!head->next) {
            // Case when only 1 element existed
            delete head;
            return NULL;
        }

        // Since its circular, the last element should
        // point to next of head
        Node *temp = head->next;
        while (temp->next != head) temp = temp->next;
        temp->next = head->next;

        // Deleting head node
        head->next = NULL;
        delete head;
        return temp->next;
    } else {
        // One element, not what we wanted
        if (!head->next) return head;

        // Traverse till we find the element
        Node *temp = head->next;
        Node *prev = head;
        while (temp != head && temp->data != x) {
            prev = temp;
            temp = temp->next;
        }
        // Element not found
        if (temp == head) return head;

        // Correct pointers and delete node
        prev->next = temp->next;
        temp->next = NULL;
        delete temp;
        return head;
    }
} 


