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
Node* kSort(Node *, int);

int main() {
    /**
     * In order to selection sort a doubly linked list we will swap
     * the selected with its previous and continue this till all
     * elements to its left are smaller than itself
     */ 
    cout << "\nThis problem sorts a doubly linked list where each node is at most k away from its sorted position.\n" << endl;
    cout << endl << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    cout << "\nEnter max distance of sorted node postion: ";
    int k;
    cin >> k;

    cout << "\nThe list after sorting is: " << endl;
    head = kSort(head, k);
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

Node* kSort(Node *head, int k) {
    // We cannot sort if there exists only one element
    if (!head || !head->next) return head;
    Node *curr = head;

    while (curr) {
        // This is the current element we want to place
        Node *temp = curr;

        while(temp->prev && temp->data < temp->prev->data) {
            // Swap the nodes, while maintaining pointers
            Node *past = temp->prev->prev; 
            Node *present = temp->prev; 
            Node *future = temp->next; 

            //       |---------|   
            // a <-> b -> c -> d
            // |----------|  

            present->next = future;
            present->prev = temp;
            temp->prev = past;
            temp->next = present;

            if(past != NULL) past->next = temp;
            if(future != NULL) future->prev = present;
        }

        if(temp->prev == NULL) head = temp;
        curr = curr->next;
    }

    return head;
}

