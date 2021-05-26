#include <iostream>
using namespace std;

#define MAX 50

/**
 * Queue is a data structure which follows the FIFO paradigm of data transfer
 * In a queue the element to entered in a queue first, is the first to leave 
 * the queue. Queues usually have a fixed size, hence circular queues are used
 * for space efficiency. Queues can be specialized to store elements in specific 
 * order, or priority basis
 */ 

template <typename T>
class Queue {
    private:
        T *values;
        int maxSize;
        int currSize;
        int front;
        int rear;

    public:
        // Initializes a queue of specific size
        Queue(int = MAX);

        // De-Allocates Queue Space
        ~Queue();

        // Used to push items to end of queue
        void enqueue(T);

        // Used to remove items from front of queue
        void dequeue();

        // Checks if the queue is full
        bool isFull();

        // Checks if the queue is empty
        bool isEmpty();

        // Returns the element in front of queue
        T getFront();

        // Overloading input operator for easy queue creation
        template <class U>
        friend istream& operator>>(istream &, Queue<U> &);

        // Overloading output operator for easy print
        template <class U>
        friend ostream& operator<<(ostream &, Queue<U> &);
};

template <typename T>
Queue<T> :: Queue(int size) {
    // Sets size and pointers
    maxSize = size;
    currSize = 0;
    front = 0;
    rear = maxSize - 1;
    values = new T[size];
}

template <typename T>
Queue<T> :: ~Queue() {
    delete[] values;
}

template <typename T>
void Queue<T> :: enqueue(T data) {
    // If the queue is not full we add on to it
    if (!isFull()) {
        // Rear represents the latest data
        rear = (rear + 1) % maxSize;
        values[rear] = data;
        currSize += 1;
    }
}

template <typename T>
void Queue<T> :: dequeue() {
    // Removes the first value added
    if (!isEmpty()) {
        // front represents the first value in the queue
        front = (front + 1) % maxSize;
        currSize -= 1;
    }
}

template <typename T>
bool Queue<T> :: isEmpty() {
    // If queue is empty
    return currSize == 0;
}

template <typename T>
bool Queue<T> :: isFull() {
    // If queue is filled
    return currSize == maxSize;
}

template <typename T>
T Queue<T> :: getFront() {
    // Returns the value at front
    return values[front];
}

template <class T>
istream& operator>>(istream &is, Queue<T> &q) {
    T inp;
    cin >> inp;

    q.enqueue(inp);

    // This will allow chaining of operations
    return is;
}

template <class T>
ostream& operator<<(ostream &os, Queue<T> &q) {
    while(!q.isEmpty()) {
        cout << q.getFront();
        q.dequeue();

        if (!q.isEmpty()) cout << " | ";
    }

    // This will allow chaining of operations
    return os;
}

int main() {
    /**
     * We generate an instance of queue class and perform operations
     */ 
    cout << "\nThis program generates a sample queue object.\n" << endl;
    
    Queue<int> que;
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Add data to Queue." << endl;
        cout << "2. Dequeue all & Print all data." << endl;
        cout << "3. Enqueue an element to back." << endl;
        cout << "4. Dequeue an element from front." << endl;
        cout << "5. Find element in front of queue." << endl;
        cout << "6. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int data, sz;

        switch (choice) {
            case 1:
                cout << "\nEnter no. of elements to consider : ";
                cin >> sz;
                cout << "\nEnter space-seperate elements of the queue:" << endl;
                for (int i = 0; i < sz; i += 1) cin >> que;
                break;
            case 2:
                cout << "\nThe last queue was:" << endl;
                cout << que << endl;
                break;
            case 3:
                cout << "\nEnter the element to insert : ";
                cin >> data;
                que.enqueue(data);
                break;
            case 4:
                if (que.isEmpty()) {
                    cout << "\nThere are no elements to dequeue." << endl;
                } else {
                    cout << "\n" << que.getFront() << " has been removed." << endl;
                    que.dequeue();
                }
                break;
            case 5:
                cout << "\nThe frontmost element is " << que.getFront() << endl;
                break;
            case 6:
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