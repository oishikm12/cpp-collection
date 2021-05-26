#include <iostream>
#include <stack>
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
Node *reverseGroup(Node *, int);

int main() {
    /**
     * In order to reverse linked list in subsequences of k
     * we will use a stack, since it is FIFO, it will be able
     * to reverse every k nodes, we will just connect them
     */ 
    cout << "\nThis problem reverses every k nodes in a linked list.\n" << endl;
    cout << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    cout << "\nEnter the subsection position till which to reverse: ";
    int k;
    cin >> k;

    cout << "\nThe list after group reversal: " << endl;
    head = reverseGroup(head, k);
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

Node *reverseGroup(Node *head, int k) {
    // This will be used to reverse
    stack<Node*> container;

    // This will be used tp traverse the nodes
    // and store a pointer to head
    Node *prev = NULL;
    Node *curr = head;

    while (curr != NULL) {
        // Push k nodes into stack or as many are available
        for (int i = 0; i < k && curr != NULL; i += 1) {
            container.push(curr);
            curr = curr->next;
        }

        while (!container.empty()) {
            Node *next = container.top();
            container.pop();

            if (prev == NULL) {
                // This is to connect head to the first node
                prev = next;
                head = prev;
            } else {
                // This resets connections & reverses nodes
                prev->next = next;
                prev = prev->next;
            }
        }
    }

    // The last node points to NULL to indicate end
    prev->next = NULL;
    return head;
}
