#include <iostream>
using namespace std;

/**
 * Circular Linked List consists of multiple nodes, connected to each other
 * via their address. These nodes exist in heap, and are not necessarily
 * continious. Unlike SLL, the tail node in the end is connected to the
 * head node, thereby creating a continious loop of nodes
 * H -> [val1 | addr2] -> [val2 | addr3] -> H
 */ 

template <typename T>
class List;

template <typename T>
class Node {
    private:
        T data;
        Node<T> *next;

    public:
        // Used to assign value to a node
        Node(T);

        // Deallocate space for Node
        ~Node();

        // Retrieves data in this node
        T getData();

        // Retrieves next pointer location
        Node<T>* getNext();

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

        // Deletes a new element from list
        void remove(int);

        // Deletes from head of list
        void removeFromHead();

        // Searches for an element in list
        int linearSearch(T);

        // Reverses the linked list
        void reverseList();

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
}

template <typename T>
Node<T> :: ~Node() {
    delete next;
    next = NULL;
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
    // Base case when no list exists
    if (HEAD == NULL) return 0;

    // Getting the size would simply require us to traverse to end
    int len = 1;
    Node<T> *temp = HEAD->next;

    while (temp != HEAD) {
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

    // Handling Tail case
    if (pos == -1) pos = size;

    int curr = 0;
    // A temporary node to traverse
    Node<T> *temp = HEAD;

    // We now traverse till we reach the position desired by user or end
    while (curr < pos && curr < size) {
        temp = temp->next;
        curr += 1;
    }

    // We create a new node, set it to target next node of the node currently
    // occupying its position, and set the occupying node to target the
    // newly created node, inserting in the middle
    Node<T> *newNode = new Node<T>(data);
    newNode->next = temp->next;
    temp->next = newNode;
}

template <typename T>
void List<T> :: insertAtHead(T data) {
    // First we create our new node, to store our data
    Node<T> *temp = new Node<T>(data);

    if (HEAD == NULL) {
        temp->next = temp;
    } else {
        // We then iterate to end to correct the loop
        Node<T> *last = HEAD;
        while (last->next != HEAD) last = last->next;
        // We then make this new node to point wherever our head was pointing
        // This way, this node becomes the first in the list
        temp->next = HEAD;
        // Then we make the last element point to this
        last->next = temp;
    }
    
    // We finally make the head point to this newly inserted node
    HEAD = temp;
}

template <typename T>
void List<T> :: remove(int pos) {
    int size = getSize();

    if (size == 0) return;

    if (pos == 0 || size == 1) {
        removeFromHead();
        return;
    }

    // Handling Tail case
    if (pos == -1) pos = size;

    int curr = 0;
    // A temporary node to traverse and select the node to delete
    Node<T> *temp = HEAD;
    // A node pointing to previous node to temp
    Node<T> *prev;

    // We now traverse till we reach the position desired by user or end
    while (curr < pos && curr < size) {
        prev = temp;
        temp = temp->next;
        curr += 1;
    }

    // We connect the previous with the next node, and delete the current one
    prev->next = temp->next;
    // Unless we remove this link destructor will be called for all
    temp->next = NULL;
    delete temp; 
}

template <typename T>
void List<T> :: removeFromHead() {
    // We need to check if the list is not empty
    if (HEAD == NULL) return;
    // We first generate a temp pointer to head
    Node<T> *temp = HEAD;
    // We then iterate to the last element
    Node<T> *curr = HEAD;
    while (curr->next != HEAD) curr = curr->next;
    // We then move head by one step ahead
    HEAD = HEAD->next;
    // Reset the end pointer loop
    curr->next = HEAD;
    // We then free up the memory held by deleted node
    temp->next = NULL;
    delete temp;
}

template <typename T>
int List<T> :: linearSearch(T key) {
    if (HEAD == NULL) return -1;

    int pos = 0;
    Node<T> *temp = HEAD;

    do {
        // We traverse and increment pos till we find our desired element
        if (temp->data == key) break;
        pos += 1;
        temp = temp->next;
    } while (temp != HEAD);

    // temp can only reach NULL, if it does not break even on last element
    // Hence we could not find the element
    if (temp == NULL) return -1;
    else return pos;
}

template <typename T>
void List<T> :: reverseList() {
    if (HEAD == NULL) return;

    Node<T> *prev = NULL;
    Node<T> *curr = HEAD;
    Node<T> *next;

    while (curr != HEAD) {
        // First we save the next node
        next = curr->next;
        // We then make the current point to previous
        curr->next = prev;
        // We update the pointers
        prev = curr;
        curr = next;
    }
    // We now restore circular property
    curr->next = prev;
    // Previous now points to first node, so we attach it to head
    HEAD = prev;
}

template <class T>
istream& operator>>(istream &is, List<T> &l) {
    T inp;
    cin >> inp;

    l.insert(0, inp);

    // This will allow chaining of operations
    return is;
}

template <class T>
ostream& operator<<(ostream &os, List<T> &l) {
    if (l.HEAD == NULL) return os;

    Node<T> *temp = l.HEAD;

    do {
        cout << temp->getData();
        temp = temp->getNext();

        if (temp != l.HEAD) cout << " +> ";
    } while (temp != l.HEAD);

    // This will allow chaining of operations
    return os;
}

int main() {
    /**
     * We generate an instance of circular linked list class and perform operations
     */ 
    cout << "\nThis program generates a sample circular linked list object.\n" << endl;
    
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
        cout << "8. Exit." << endl;
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