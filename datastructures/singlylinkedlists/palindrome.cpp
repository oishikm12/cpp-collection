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
bool isPalindrome(Node *);

int main() {
    /**
     * In order to find the nth number from end we will maintain
     * two pointers, one moving n elements ahead from the previous
     * this way when the future pointer reaches the end, the past
     * pointer will be exactly n distance from the end
     */ 
    cout << "\nThis program finds if a list is palindrome.\n" << endl;
    cout << "Enter size of the list: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    bool pally = isPalindrome(head);

    if (pally) cout << "\nThe list is palindromic." << endl;
    else cout << "\nThe list is not palindromic." << endl;

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

bool isPalindrome(Node *head) {
    // Temp pointer to iterate forward
    Node* temp = head;
    stack<int> s;

    // Push all elements of the list to the stack
    while (temp) {
        s.push(temp->data);
        temp = temp->next;
    }

    // Iterate in the list again and
    // check by popping from the stack
    while (head != NULL ) {
        // Get the top most element
        int curr = s.top();
        s.pop();

        // Check if data is not same as popped element
        if(head -> data != curr) return false;

        head = head->next;
    }
 
    return true;
}