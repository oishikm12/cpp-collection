#include <iostream>
using namespace std;

#define MAX 50

/**
 * Stack is a data structure which follows LIFO data flow, wherin the element
 * inserted in the end is the first one that can be removed
 */ 

template <typename T>
class Stack {
    private:
        T *values;
        int top;
        int max;

    public:
        // Initializes stack class
        Stack(int = MAX);

        // DeAllocates memory used by stack
        ~Stack();

        // Used to add items to the stack
        void push(T);

        // Used to remove items from the stack
        void pop();

        // Checks if the stack is full
        bool isFull();

        // Checks if the stack is empty
        bool isEmpty();

        // Returns the Topmost item
        T getTop();

        // Overloading input operator for easy stack creation
        template <class U>
        friend istream& operator>>(istream &, Stack<U> &);

        // Overloading output operator for easy print
        template <class U>
        friend ostream& operator<<(ostream &, Stack<U> &);
};

template <typename T>
Stack<T> :: Stack(int size) {
    max = size;
    top = -1;
    values = new T[size];
}

template <typename T>
Stack<T> :: ~Stack() {
    delete[] values;
}


template <typename T>
void Stack<T> :: push(T data) {
    // Adds a new value to the end
    if (!isFull()) values[++top] = data;
}

template <typename T>
void Stack<T> :: pop() {
    // Removes the last value added
    if (!isEmpty()) values[top--] = 0;
}

template <typename T>
bool Stack<T> :: isFull() {
    // If stack is full
    return top == max - 1;
}

template <typename T>
bool Stack<T> :: isEmpty() {
    // If stack is empty
    return top == -1;
}

template <typename T>
T Stack<T> :: getTop() {
    // Returns the value at the end
    return values[top];
}

template <class T>
istream& operator>>(istream &is, Stack<T> &s) {
    T inp;
    cin >> inp;

    s.push(inp);

    // This will allow chaining of operations
    return is;
}

template <class T>
ostream& operator<<(ostream &os, Stack<T> &s) {
    while(!s.isEmpty()) {
        cout << s.getTop();
        s.pop();

        if (!s.isEmpty()) cout << " | ";
    }

    // This will allow chaining of operations
    return os;
}

int main() {
    /**
     * We generate an instance of stack class and perform operations
     */ 
    cout << "\nThis program generates a sample stack object.\n" << endl;
    
    Stack<int> stk;
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Add data to Stack." << endl;
        cout << "2. Pop all & Print all data." << endl;
        cout << "3. Push one element into back." << endl;
        cout << "4. Pop one element from back." << endl;
        cout << "5. Find topmost element." << endl;
        cout << "6. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int data, sz;

        switch (choice) {
            case 1:
                cout << "\nEnter no. of elements to consider : ";
                cin >> sz;
                cout << "\nEnter space-seperate elements of the stack:" << endl;
                for (int i = 0; i < sz; i += 1) cin >> stk;
                break;
            case 2:
                cout << "\nThe last stack was:" << endl;
                cout << stk << endl;
                break;
            case 3:
                cout << "\nEnter the element to insert : ";
                cin >> data;
                stk.push(data);
                break;
            case 4:
                if (stk.isEmpty()) {
                    cout << "\nThere are no elements to pop." << endl;
                } else {
                    cout << "\n" << stk.getTop() << " has been popped." << endl;
                    stk.pop();
                }
                break;
            case 5:
                cout << "\nThe topmost element is " << stk.getTop() << endl;
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