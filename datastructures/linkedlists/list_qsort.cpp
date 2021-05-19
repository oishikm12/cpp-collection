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
Node* quickSort(Node *, Node *);
Node* getTail(Node *);
Node* partition(Node *, Node *, Node *&, Node *&);

int main() {
    /**
     * In order to use quick sort on a list, we will be
     * finding pivot at the end and moving every element
     * smaller than pivot to left. In order to do this we
     * will be maintaining constant positions of head & tail
     */ 
    cout << "\nThis program sorts a linked list via quicksort.\n" << endl;
    cout << "Enter size of the List: ";
    int n;
    cin >> n;

    cout << "Enter space seperated elements of the list" << endl;
    Node *head = NULL;
    head = build(head, n);
    cout << "The list is: " << endl;
    print(head);

    cout << "\nThe list after sorting is: " << endl;
    head = quickSort(head, getTail(head));
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

Node* getTail(Node *head) {
    Node *curr = head;
    // We simply traverse to the end and return
    // the last node's location
    while (curr && curr->next) curr = curr->next;
    return curr;
}

Node* partition(Node *start, Node *end, Node *&newStart, Node *&newEnd) {
    // We consider the last node to be the pivot
    Node *pivot = end;
    Node *prev = NULL; 
    Node *curr = start; 
    Node *tail = pivot;
 
    while (curr != pivot) {
        if (curr->data < pivot->data) {
            // While the current data is smaller, we
            // simply keep on traversing
            if (newStart == NULL) newStart = curr;
            prev = curr;
            curr = curr->next;
        } else {
            // If this is not the head node, we remove
            // this node from the list
            if (prev) prev->next = curr->next;
            
            // We insert out pivot / tail element just before 
            // this element and continue
            Node* temp = curr->next;
            curr->next = NULL;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }
 
    if (newStart == NULL) newStart = pivot;
 
    newEnd = tail;

    return pivot;
}

Node* quickSort(Node *start, Node *end) {
    if (!start || start == end) return start;
    
    // These will allow us to select scope of next
    // loop iteration
    Node *newStart = NULL, *newEnd = NULL;
    
    // Fet the pivot element at its correct position
    Node *pivot = partition(start, end, newStart, newEnd);
    
    if (newStart != pivot) {
        Node *temp = newStart;
        
        // We will need to find the position till which
        // to recursively qs before pivot
        while (temp->next != pivot) temp = temp->next;
        temp->next = NULL;
 
        newStart = quickSort(newStart, temp);
 
        // Connecting the sorted list to pivot
        temp = getTail(newStart);
        temp->next = pivot;
    }
 
    // Qs mid + 1 till end
    pivot->next = quickSort(pivot->next, newEnd);
 
    return newStart;
}
