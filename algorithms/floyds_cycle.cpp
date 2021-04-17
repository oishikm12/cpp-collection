#include <iostream>
#include <unordered_set>
using namespace std;

class Node {
    public:
        int data;
        Node *next;

        Node(int x) : data(x), next(NULL) {}
        ~Node() {
            delete next;
            next = NULL;
        }
};

Node* push(Node*, int);
bool detectCycle(Node*);

int main() {
    /**
     * The idea is to use two pointers, one fast the other slow, should
     * the fast pointer reach slow, from behind, it denotes presence of cycle
     */ 
    cout << "\nThis program denotes presence of Floyd's Cycle in a list\n" << endl;

    int n;
    cout << "Enter no. of elements to consider: ";
    cin >> n;

    Node *root = NULL;
    cout << "Enter space delimited elements in the list:" << endl;
    for (int i = 0; i < n; i += 1) {
        int data;
        cin >> data;
        root = push(root, data);
    }

    // manually Placing a loop in the list
    root->next->next->next = root->next;

    if (detectCycle(root)) cout << "A cycle is present in the list" << endl;
    else cout << "A cycle is not present in the list" << endl;

    cout << endl;

    return 0;
}

Node* push(Node* root, int data) {
    if (root == NULL) {
        return new Node(data);
    }
    root->next = push(root->next, data);
    return root;
}


bool detectCycle(Node* head) {
    // Function to detect a cycle in a linked list using
    // Floyd’s cycle detection algorithm
    // take two pointers – `slow` and `fast`
    Node *slow = head, *fast = head;
 
    while (fast && fast->next) {
        // move slow by one pointer
        slow = slow->next;
        // move fast by two pointers
        fast = fast->next->next;
        // if they meet any node, the linked list contains a cycle
        if (slow == fast) return true;
    }
 
    // we reach here if the slow and fast pointer does not meet
    return false;
}
