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
Node* divide(Node *);

int main() {
    /**
     * In order to segregate the list, we will maintain two
     * seperate pointers one to connect to even nodes, other 
     * for odd, in then end we simply connect them and return
     */ 
    cout << "\nThis program segregates a list based on odd even members.\n" << endl;
    cout << "Enter size of the list: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    cout << "\nThe list after segregating even and odd nodes is," << endl;
    head = divide(head);
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

Node* divide(Node *head) {
    // One to track even nodes and one for odd nodes
    Node *even = new Node(0);
    Node *odd = new Node(0);
    
    Node *t1 = even, *t2 = odd;
    
    while(head) {
        if (head->data & 1) {
            odd->next = head;
            odd = odd->next;
        } else {
            even->next = head;
            even = even->next;
        }
        head = head->next;
    }
    
    // Connecting even to odd, and odd to null to indicate end
    even->next = t2->next;
    odd->next = NULL;
    
    return t1->next;
}