#include <iostream>
#include <vector>
using namespace std;

class Node {
    public:
        int data;
        Node *next, *bottom;

        Node(int val = 0, Node *link = NULL, Node *btm = NULL) : data(val), next(link), bottom(btm) {};
        ~Node() { delete next, delete bottom; }
};

Node* build(Node *, vector<int> &);
void print(Node *);
Node* merge(Node *, Node *);
Node* flattenList(Node *);

int main() {
    /**
     * In order to flatten a list which consists of left 
     * & bottom pointers, we can recursively merge left sub lists
     * such that all nodes belong to bottom of one
     */ 
    cout << "\nThis problem flattens a 2D linked list\n" << endl;
    cout << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << "Enter space seperated sizes of each sublist" << endl;
    vector<int> elems(n);
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    cout << "\nEnter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, elems);

    cout << "\nThe list before flattening is: " << endl;
    print(head);

    cout << "\nThe list after flattening is: " << endl;
    head = flattenList(head);
    print(head);

    cout << endl;

    return 0;
}

Node* build(Node *head, vector<int> &lims) {
    head = new Node();
    // We need two pointers we have to simultaneously
    // traverse bottom and once its done, to right
    Node *top = head;
    Node *temp = head;

    for(int i = 0; i < lims.size(); i += 1) {
        while (lims[i]--) {
            cin >> head->data;
            if (lims[i] != 0) head->bottom = new Node();
            head = head->bottom;
        }

        // Next head in the 2D list
        head = top;
        if (i != lims.size() - 1) head->next = new Node();
        head = head->next;
        top = head;
    }

    return temp;
}

void print(Node *head) {
    while (head != NULL) {
        Node *temp = head;

        // First we print every node in the bottom pointer
        while (head != NULL) {
            cout << head->data;
            if (head->bottom != NULL) cout << " > ";
            head = head->bottom;
        }

        // Then we shift to the right sublist
        head = temp->next;
        cout << endl;
    }
}

Node* merge(Node *a, Node *b) {
    // This will be the connecting node to merge
    Node *head = new Node(0);
    Node *temp = head;
    
    while (a != NULL && b != NULL) {
        if (a->data < b->data) {
            head->bottom = a;
            a = a->bottom;
        } else {
            head->bottom = b;
            b = b->bottom;
        }
        head = head->bottom;
        // We are resetting the next pointer while merge
        // to flatten the list
        head->next = NULL;
    }
    
    head->bottom = a ? a : b;
    while(head->bottom) {
        // Even after joining we need to reset the next
        // pointers if any
        head->next = NULL;
        head = head->bottom;
    }
    
    return temp->bottom;
}

Node* flattenList(Node *head) {
    // We recursively merge every head with its next head node
    if (!head || !head->next) return head;
    return merge(head, flattenList(head->next));
}
