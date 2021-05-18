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
Node* reverse(Node *);
Node* compute(Node *);

int main() {
    /**
     * In order to delete every element which has a node
     * greater to its right, we simply reverse the list and
     * starting from the head, we connect it to the node 
     * greater than current. Finally we reverse the list again
     */ 
    cout << "\nThis program trims a list such that for each element no greater element exists to its right.\n" << endl;
    cout << "Enter size of the list: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "\nThe list is: " << endl;
    print(head);

    cout << "\nThe list after removing nodes which have a greater right value is," << endl;
    head = compute(head);
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
        // If we are not at the end then we connect
        // this node to the next
        if (n > 0) temp->next = new Node();
        temp = temp->next;
    }

    return head;
}

void print(Node *head) {
    while (head != NULL) {
        cout << head->data;
        // This will print a seperator for each element of the list
        if (head->next != NULL) cout << " > ";
        head = head->next;
    }
    cout << endl;
}

Node* reverse(Node *h) {
    // Reversing is done via maintaining a prev & next
    // pointer such that we can change next of current
    // to previous and move on to next
    Node *prev = NULL, *nxt = NULL;
    Node *curr = h;
    
    while (curr != NULL) {
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    
    // Previous stores the last non null value
    h = prev;
    return h;
}

Node* compute(Node *head) {
    // We first reverese such that we have to
    // remove nodes to the right
    head = reverse(head);
    
    Node *curr = head;
    
    while (curr) {
        // We search the next biggest
        // connect to it & mov to it
        Node *next = curr->next;
        while (next && next->data < curr->data) next = next->next;
        curr->next = next;
        curr = next;
    }
    
    // We reverse it back before returning
    return reverse(head);
}