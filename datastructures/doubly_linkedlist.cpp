#include <iostream>
using namespace std;

/**
 * Doubly Linked List consists of multiple nodes, connected to each other
 * via their address. These nodes exist in heap, and are not necessarily
 * continious. Unlike SLL,  there exists two pointers, one for the previous,
 * one for the next, allowing bidirectional traversal
 * H <-> [val1 | addr2] <-> [val2 | addr3] -> NULL
 */ 

template <typename T>
class List;

template <typename T>
class Node {
    private:
        T data;
        Node<T> *next, *prev;

    public:
        // Used to assign value to a node
        Node(T);

        // Deallocate space for Node
        ~Node();

        // Retrieves data in this node
        T getData();

        // Retrieves next pointer location
        Node<T>* getNext();

        // Retrieves previous pointer location
        Node<T>* getPrev();

        // Will allow list to access Nodes
        friend class List<T>;
};

template <typename T>
class List {
    private:
        Node<T> *HEAD;

    public:
        // Used to initialize a new Linked List
        List();

        // Deallocates List
        ~List();

        // Finds out current size of List
        int getSize();

        // Inserts a new element into list
        void insert(int, T);

        // Insert an element at head position
        void insertAtHead(T);

        // Insert an element at tail position
        void insertAtTail(T);

        // Deletes a new element from list
        void remove(int);

        // Deletes from head of list
        void removeFromHead();

        // Deletes from tail of list
        void removeFromTail();

        // Searches for an element in list
        int linearSearch(T);

        // Reverses the linked list
        void reverseList();

        // Gets middle of current list
        T mid();

        // Gets the middle node in the list
        Node<T>* getMiddle(Node<T>*);

        // Merges two sorted node list into a single list
        Node<T>* merge(Node<T> *, Node<T> *);

        // Merge sorts the list
        Node<T>* mergeSort(Node<T> *);

        // Caller for merge sort
        void sort();

        // Overloading input operator for easy list creation
        template <class U>
        friend istream& operator>>(istream &, List<U> &);

        // Overloading output operator for easy print
        template <class U>
        friend ostream& operator<<(ostream &, List<U> &);
};

template <typename T>
Node<T> :: Node(T val) {
    data = val;
    next = NULL;
    prev = NULL;
}

template <typename T>
Node<T> :: ~Node() {
    delete prev;
    delete next;
    next = NULL;
    prev = NULL;
}

template <typename T>
T Node<T> :: getData() {
    return data;
}

template <typename T>
Node<T>* Node<T> :: getNext() {
    return next;
}

template <typename T>
Node<T>* Node<T> :: getPrev() {
    return prev;
}

template <typename T>
List<T> :: List() {
    HEAD = NULL;
}

template <typename T>
List<T> :: ~List() {
    delete HEAD;
    HEAD = NULL;
}

template <typename T>
int List<T> :: getSize() {
    // Getting the size would simply require us to traverse to end
    int len = 0;
    Node<T> *temp = HEAD;

    while (temp != NULL) {
        temp = temp->next;
        len += 1;
    }

    return len; 
}

template <typename T>
void List<T> :: insert(int pos, T data) {
    int size = getSize();

    if (pos == 0 || size == 0) {
        insertAtHead(data);
        return;
    }
    
    if (pos >= size || pos == -1) {
        insertAtTail(data);
        return;
    }

    int curr = 0;
    // A temporary node to traverse
    Node<T> *temp = HEAD;

    // We now traverse till we reach the position desired by user
    while (curr < pos) {
        temp = temp->next;
        curr += 1;
    }

    // We create a new node, set it to target next node of the node currently
    // occupying its position, the new node's prev points to the occupying node 
    // and set the occupying node's next to target the newly created node, 
    // inserting in the middle
    Node<T> *newNode = new Node<T>(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    temp->next->prev = newNode;
    temp->next = newNode;
}

template <typename T>
void List<T> :: insertAtHead(T data) {
    // First we create our new node, to store our data
    Node<T> *temp = new Node<T>(data);
    // We then make this new node to point wherever our head was pointing
    // This way, this node becomes the first in the list
    temp->next = HEAD;
    // We need to set our previous pointer if needed
    if (HEAD) HEAD->prev = temp;
    // We finally make the head point to this newly inserted node
    HEAD = temp;
}

template <typename T>
void List<T> :: insertAtTail(T data) {
    // Create a temporary node to traverse
    Node<T> *temp = HEAD;
    // We then traverse till we reach the end
    while (temp->next != NULL) temp = temp->next;

    temp->next = new Node<T>(data);
    temp->next->prev = temp;
}

template <typename T>
void List<T> :: remove(int pos) {
    int size = getSize();

    if (size == 0) return;

    if (pos == 0 || size == 1) {
        removeFromHead();
        return;
    }

    if (pos >= size - 1 || pos == -1) {
        removeFromTail();
        return;
    }

    int curr = 0;
    // A temporary node to traverse and select the node to delete
    Node<T> *temp = HEAD;

    // We now traverse till we reach the position desired by user
    while (curr < pos) {
        temp = temp->next;
        curr += 1;
    }

    // We interconnect previous & next, and then delete current
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    // Unless we remove these links, destructors will be called for all
    temp->next = NULL;
    temp->prev = NULL;
    delete temp; 
}

template <typename T>
void List<T> :: removeFromHead() {
    // We need to check if the list is not empty
    if (HEAD == NULL) return;
    // We first generate a temp pointer to head
    Node<T> *temp = HEAD;
    // We then move head by one step ahead
    HEAD = HEAD->next;
    HEAD->prev = NULL;
    // We then free up the memory held by deleted node
    temp->next = NULL;
    delete temp;
}

template <typename T>
void List<T> :: removeFromTail() {
    // Node to traverse and select the last node
    Node<T> *temp = HEAD;

    while (temp->next != NULL) temp = temp->next;

    // We make the 2nd last node point to end, and delete the last node  
    temp->prev->next = NULL;
    temp->prev = NULL;
    delete temp;
}

template <typename T>
int List<T> :: linearSearch(T key) {
    int pos = 0;
    Node<T> *temp = HEAD;

    while (temp != NULL) {
        // We traverse and increment pos till we find our desired element
        if (temp->data == key) break;
        pos += 1;
        temp = temp->next;
    }

    // temp can only reach NULL, if it does not break even on last element
    // Hence we could not find the element
    if (temp == NULL) return -1;
    else return pos;
}

template <typename T>
void List<T> :: reverseList() {
    // We will use this to point to our reversed head
    Node<T> *newHead;
    Node<T> *curr = HEAD;
    Node<T> *next;
    
    while (curr) {
        // To store the next location
        next = curr->next;
        // Make the next point to previous
        curr->next = curr->prev;
        curr->prev = next;
        // Update the pointers & increment head
        newHead = curr;
        curr = next;
    }

    // This will point to the last node in itself
    HEAD = newHead;
}

template <typename T>
T List<T> :: mid() {
    return getMiddle(HEAD)->data;
}

template <typename T>
Node<T>* List<T> :: getMiddle(Node<T>* start) {
    // In order to get to middle, we initialize two pointers
    // first pointer jumps ahead by 1 element
    // second pointer jumps ahead by 2 elements
    // by the time second pointer reaches the end, the first pointer is at mid
    if (start == NULL) return NULL;
    else if (start->next == NULL) return start;

    Node<T> *first = start;
    Node<T> *second = first->next;

    while (second != NULL && second->next != NULL) {
        second = second->next->next;
        first = first->next;
    }

    return first;
}

template <typename T>
Node<T>* List<T> :: merge(Node<T> *a, Node<T> *b) {
    // If either one of the node is fully traversed the other one is merged
    if (a == NULL) return b;
    if (b == NULL) return a;

    // Node to traverse and connect both lists 
    Node<T> *c;

    // Connects whichever is smaller
    if (a->data < b->data) {
        c = a;
        c->next = merge(a->next, b);
    } else {
        c = b;
        c->next = merge(a, b->next);
    }

    // Connect current to previous of next
    c->next->prev = c;

    return c;
}

template <typename T>
Node<T>* List<T> :: mergeSort(Node<T> *start) {
    // Base case when there is only one element
    if (start == NULL || start->next == NULL) return start;

    // We divide the list into two parts recursively
    Node<T> *mid = getMiddle(start);
    Node<T> *a = start;
    Node<T> *b = mid->next;

    // We remove the link between these two parts
    mid->next = NULL;

    // We now sort these two parts
    a = mergeSort(a);
    b = mergeSort(b);

    // We merge the sorted nodes
    Node<T> *c = merge(a, b);
    return c;
}

template <typename T>
void List<T> :: sort() {
    HEAD = mergeSort(HEAD);
}

template <class T>
istream& operator>>(istream &is, List<T> &l) {
    T inp;
    cin >> inp;

    l.insert(-1, inp);

    // This will allow chaining of operations
    return is;
}

template <class T>
ostream& operator<<(ostream &os, List<T> &l) {
    Node<T> *temp = l.HEAD;

    while(temp != NULL) {
        cout << temp->getData();
        temp = temp->getNext();

        if (temp != NULL) cout << " <=> ";
    }

    // This will allow chaining of operations
    return os;
}

int main() {
    /**
     * We generate an instance of doubly linked list class and perform operations
     */ 
    cout << "\nThis program generates a sample doubly linked list object.\n" << endl;
    
    List<int> llist;
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Generate List." << endl;
        cout << "2. Print current List." << endl;
        cout << "3. Get Size of List." << endl;
        cout << "4. Insert into List." << endl;
        cout << "5. Delete from List." << endl;
        cout << "6. Search for an Element." << endl;
        cout << "7. Reverse the List." << endl;
        cout << "8. Get Middle Element." << endl;
        cout << "9. Sort the List." << endl;
        cout << "10. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int data, pos, key;

        switch (choice) {
            case 1:
                cout << "\nEnter no. of elements to consider : ";
                cin >> pos;
                cout << "\nEnter space-seperate elements of the list:" << endl;
                for (int i = 0; i < pos; i += 1) cin >> llist;
                break;
            case 2:
                cout << "\nThe current list is:" << endl;
                cout << llist << endl;
                break;
            case 3:
                cout << "\nThe size of list is: " << llist.getSize() << endl;
                break;
            case 4:
                cout << "\nEnter the number you would like to insert ? ";
                cin >> data;
                cout << "\nEnter the position you would like to insert it at ? ";
                cin >> pos;
                llist.insert(pos, data);
                break;
            case 5:
                cout << "\nEnter the position you would like to delete from ? ";
                cin >> pos;
                llist.remove(pos);
                break;
            case 6:
                cout << "\nEnter the value to search for ? ";
                cin >> key;
                pos = llist.linearSearch(key);
                if (pos == -1) cout << "\nThe element was not found." << endl;
                else cout << "\nThe element was found at position " << pos << "." << endl;
                break;
            case 7:
                llist.reverseList();
                cout << "\nThe List has been reversed." << endl;
                cout << llist << endl;
                break;
            case 8:
                cout << "\nThe middle element is : " << llist.mid() << "." << endl;
                break;
            case 9:
                llist.sort();
                cout << "\nThe sorted list is :" << endl;
                cout << llist << endl;
                break;
            case 10:
                cout << "\nGoodbye !!!" << endl;
                flag = !flag;
                break;
            default:
                cout << "\nPlease try again" << endl;
                break;
        }
    }
   
    return 0;
}