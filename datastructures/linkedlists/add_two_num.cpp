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
int len(Node *);
Node* reverse(Node *);
void add(Node *, Node *, int);
Node* addTwoLists(Node *, Node *);

int main() {
    /**
     * In order to add one to linked list to another, we
     * will reverse the whole list first, and then traverse
     * both simultaneously adding both and maintaining a
     * carry variable for each turn
     */ 
    cout << "\nThis program adds two linked list as numbers\n" << endl;
    int n;
    cout << "Enter size of the first list: ";
    cin >> n;

    cout << "Enter space seperated elements of the first list," << endl;
    Node *head1 = NULL;
    head1 = build(head1, n);

    int m;
    cout << "Enter size of the second list: ";
    cin >> m;

    cout << "Enter space seperated elements of the second list," << endl;
    Node *head2 = NULL;
    head2 = build(head2, m);

    cout << "\nThe first list is," << endl;
    print(head1);
    cout << "\nThe second list is," << endl;
    print(head2);
    cout << "\nThe list after adding them is," << endl;
    print(addTwoLists(head1, head2));

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

int len(Node* l) {
    int sz = 0;
    while(l != NULL) {
        // Simply iterating till null will give us size
        sz += 1;
        l = l -> next;
    }
    return sz;
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

void add(Node* first, Node* second, int carry) {
    // We have reached the end
    // since first is bigger & there is no carry
    if (first == NULL && carry == 0) return;
    
    // We add the data of second if present & carry
    if (second != NULL) first -> data += second -> data;
    first -> data += carry;
    
    // Data is modulo 10 to get carry if any
    int cr = first -> data / 10;
    first -> data = first -> data % 10;
    
    // There is a need to add a new node since carry is present
    if (first -> next == NULL && cr != 0) first -> next = new Node(0);
    // If smaller list is finished no need traverse
    Node* nl2 = second == NULL ? second : second -> next;
    add(first -> next, nl2, cr);
}

Node* addTwoLists(Node* first, Node* second) {
    // We need to reverse the lists since addition
    // starts from units place
    first = reverse(first);
    second = reverse(second);

    if (len(first) > len(second)) {
        // If the first list is greater then we store the res in it
        add(first, second, 0);
        return reverse(first);
    } else {
        // If the second list is greater then we store res in it
        add(second, first, 0);
        return reverse(second);
    }
    // We reverse the result back before returning
}