#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *next, *prev;

        Node(int val = 0, Node *lfwd = NULL, Node *lbck = NULL) : data(val), next(lfwd), prev(lbck) {};
        ~Node() { delete prev, delete next; }
};

Node* build(Node *, int);
void print(Node *);
Node* reverseDLL(Node *);

int main() {
    /**
     * In order to reverse a doubly linked list, we will
     * simply use a past pointer to keep track of next
     * and accordingly change directions 
     */ 
    cout << "\nThis problem reveres a doubly linked list.\n" << endl;
    cout << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    cout << "\nThe list after reversal is: " << endl;
    head = reverseDLL(head);
    print(head);

    cout << endl;

    return 0;
}

Node* build(Node *head, int n) {
    // We allocate space to head for a node
    head = new Node();
    Node *temp = head;

    while (n--) {
        // We take input for user for this node
        cin >> temp->data;
        if (n != 0) {
            // If we are not at the end then we connect
            // this node to the next, also set the previous
            // of next to current node
            temp->next = new Node();
            temp->next->prev = temp;
        }
        temp = temp->next;
    }

    return head;
}

void print(Node *head) {
    while (head != NULL) {
        cout << head->data;
        // This will print a seperator for each element of the list
        if (head->next != NULL) cout << " <> ";
        head = head->next;
    }
    cout << endl;
}

Node* reverseDLL(Node * head) {
    // This will be used to point to head after reversal
    Node *newHead;
    
    while (head) {
        // To store the next location
        Node *temp = head->next;
        // Make the next point to previous
        head->next = head->prev;
        head->prev = temp;
        // Reset the head
        newHead = head;
        head = temp;
    }
    
    return newHead;
}

