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
void printSumTriplets(Node *, int);

int main() {
    /**
     * In order to find triplets which equal to a given sum
     * we will iterate over a given list, and then use binary
     * search to find if two other such numbers exist whose
     * combined sum can give us a triplet
     */ 
    cout << "\nThis program finds out possible triplets in a list whose sum equals a given value.\n" << endl;
    cout << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    cout << "\nEnter sum to search for: ";
    int x;
    cin >> x;

    cout << "\nThe triplets matching the sum are: " << endl;
    printSumTriplets(head, x);

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

void printSumTriplets(Node *head, int x) {
    // One to point to start, one to point to end
    Node *start = head;
    Node *end = head;
    while (end -> next) end = end->next;

    while (start) {
        // We do not need to check if less than 2 elements remain
        if (!start->next || !start->next->next) {
            start = start->next;
            continue;
        }

        // Since the first element is selected, we use
        // binary search from next till end of the list
        Node *first = start->next;
        Node *last = end;

        while (first != last) {
            int sum = start->data + first->data + last->data;
            // If the sum is smaller we increment first pointer
            // if it is greater we decrement last pointer
            if (sum < x) first = first->next;
            else if (sum > x) last = last->prev;
            else {
                cout << start->data << ' ' << first->data << ' ' << last->data << endl;
                first = first->next;
                last = last->prev;
            }
        }

        start = start -> next;
    }
}
