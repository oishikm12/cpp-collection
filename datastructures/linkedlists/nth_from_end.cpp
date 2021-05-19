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
int getNthFromLast(Node *, int);

int main() {
    /**
     * In order to find the nth number from end we will maintain
     * two pointers, one moving n elements ahead from the previous
     * this way when the future pointer reaches the end, the past
     * pointer will be exactly n distance from the end
     */ 
    cout << "\nThis program finds the n'th element from the end in a list.\n" << endl;
    cout << "Enter size of the list: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    cout << "\nEnter the distance whose element to find from end: ";
    int x;
    cin >> x;

    int val = getNthFromLast(head, x);

    if (val == -1) cout << "\nThe list is smaller than the requested element." << endl;
    else cout << "\nThe element is: " << val << "." << endl;

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

int getNthFromLast(Node *head, int n) {
    Node *past = head;
    Node *future = head;
    
    // First we move the future pointer n steps ahead
    int cnt = 1;
    while (future->next && cnt < n) {
        future = future->next;
        cnt += 1;
    }
    
    // If we reached the end before n steps, the
    // size of the list is smaller than desired position
    if (cnt != n) return -1;
    
    // We shift the future pointer to the end
    while (future->next) {
        future = future->next;
        past = past->next;
    }
    
    // Past is nth position from end
    return past->data;
}
