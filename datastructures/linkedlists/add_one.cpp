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
void print(Node *);
int addToEach(Node *);
Node* addOne(Node *);

int main() {
    /**
     * In order to add one to linked list, we will simply
     * recurse to the last node and add to it, thereby returning
     * the carry if any to caller function
     */ 
    cout << "\nThis program adds 1 to a number represented as linked list\n" << endl;
    int n;
    cout << "Enter size of the list: ";
    cin >> n;

    cout << "Enter space seperated elements of the list," << endl;
    Node *head = NULL;
    head = build(head, n);

    cout << "\n1 added to ";
    print(head);
    head = addOne(head);
    cout << " is ";
    print(head);

    cout << endl << endl;

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
        // this node to the next
        if (n > 0) temp->next = new Node();
        temp = temp->next;
    }

    return head;
}

void print(Node *head) {
    // Since this is a number space is not required
    while (head != NULL) {
        cout << head->data;
        head = head->next;
    }
}

int addToEach(Node *head) {
    if (head->next == NULL) {
        // Base case when we have reached the last node
        head->data += 1;
    } else {
        // Recurse to the next node and return
        // any carry if needed
        int prevCarry = addToEach(head->next);
        head->data += prevCarry;
    }
    
    // Carry can be found by dividing by 10, where modulo is the ans
    int nextCarry = head->data / 10;
    head->data = head->data % 10;
    
    return nextCarry;
}

Node* addOne(Node *head) {
    int carry = addToEach(head);
    
    if (carry != 0) {
        // This will occur when the size of the
        // number after adding 1 is more than original
        Node *newHead = new Node(carry);
        newHead->next = head;
        head = newHead;
    }
    
    return head;
}