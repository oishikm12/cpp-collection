#include <iostream>
#include <unordered_map>
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
Node* findIntersection(Node *, Node *);

int main() {
    /**
     * In order to find the intersection of two lists, we will
     * be using a map to check if elements are present in both
     */ 
    cout << "\nThis program checks if two lists are palindromic.\n" << endl;
    cout << "Enter size of the first list: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the first list" << endl;
    Node *head1 = NULL;
    head1 = build(head1, n);
    cout << "The first list is: " << endl;
    print(head1);

    cout << "Enter size of the second list: ";
    int m;
    cin >> m;

    cout << "Enter space seperated elements of the second list" << endl;
    Node *head2 = NULL;
    head2 = build(head2, m);
    cout << "The second list is: " << endl;
    print(head2);

    Node *head3 = findIntersection(head1, head2);

    cout << "\nThe intersection of these two lists are," << endl;
    print(head3);

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

Node* findIntersection(Node* head1, Node* head2) {
    // This will store the if an element is present
    unordered_map<int, bool> data;
    
    Node *head3 = new Node(0);
    Node *temp = head3;
    
    // First we insert all the elements in the first list
    while (head1 != NULL) {
        data[head1->data] = true;
        head1 = head1 -> next;
    }
    
    // Here we check for intersection
    while (head2 != NULL) {
        if (data[head2->data]) {
            // For every element there can be one copy in
            // the other, so we delete that instance
            data[head2->data] = false;
            head3 -> next = new Node(head2->data);
            head3 = head3 -> next;
        }
        head2 = head2 -> next;
    }
    
    return temp->next;
}