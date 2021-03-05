#include <iostream>

/**
 * Linked List consists of multiple nodes, connected to each other
 * via their address. These nodes exist in heap, and are not necessarily
 * continious
 * H -> [val1 | addr2] -> [val2 | addr3] -> NULL
 */ 

#ifndef LIST_CLASS_H
#define LIST_CLASS_H

namespace linkedlist {
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
            friend std::istream& operator>>(std::istream &, List<U> &);

            // Overloading output operator for easy print
            template <class U>
            friend std::ostream& operator<<(std::ostream &, List<U> &);
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
        Node<T> *temp;

        while (HEAD != NULL && HEAD->next != NULL) {
            temp = HEAD;
            delete temp;
            HEAD = HEAD->next;
        }

        temp = NULL;
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
        // We then make this new node to point wherever our head was pointing
        // This way, this node becomes the first in the list
        temp->next = HEAD;
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
        // A node pointing to previous node to temp
        Node<T> *prev;

        // We now traverse till we reach the position desired by user
        while (curr < pos) {
            prev = temp;
            temp = temp->next;
            curr += 1;
        }

        // We connect the previous with the next node, and delete the current one
        prev->next = temp->next;
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
        // We then free up the memory held by deleted node
        delete temp;
    }

    template <typename T>
    void List<T> :: removeFromTail() {
        // Node to store previous to current traversing node
        Node<T> *prev;
        // Node to traverse and select the last node
        Node<T> *temp = HEAD;

        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }

        // We make the 2nd last node point to end, and delete the last node  
        prev->next = NULL;
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
        Node<T> *prev = NULL;
        Node<T> *curr = HEAD;
        Node<T> *next;

        while (curr != NULL) {
            // First we save the next node
            next = curr->next;
            // We then make the current point to previous
            curr->next = prev;
            // We update the pointers
            prev = curr;
            curr = next;
        }

        // Previous now points to first node, so we attach it to head
        HEAD = prev;
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
    std::istream& operator>>(std::istream &is, List<T> &l) {
        T inp;
        std::cin >> inp;

        l.insert(-1, inp);

        // This will allow chaining of operations
        return is;
    }

    template <class T>
    std::ostream& operator<<(std::ostream &os, List<T> &l) {
        Node<T> *temp = l.HEAD;

        while(temp != NULL) {
            std::cout << temp->getData();
            temp = temp->getNext();

            if (temp != NULL) std::cout << " > ";
        }

        // This will allow chaining of operations
        return os;
    }
}

#endif /* LIST_CLASS */