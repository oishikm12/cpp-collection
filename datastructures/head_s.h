#include <iostream>

/**
 * Stack is a data structure which follows LIFO data flow, wherin the element
 * inserted in the end is the first one that can be removed
 */ 

#ifndef STACK_CLASS_H
#define STACK_CLASS_H

#define MAX 50

namespace stack {
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
            friend std::istream& operator>>(std::istream &, Stack<U> &);

            // Overloading output operator for easy print
            template <class U>
            friend std::ostream& operator<<(std::ostream &, Stack<U> &);
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
    bool Stack<T> :: isEmpty() {
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
    std::istream& operator>>(std::istream &is, Stack<T> &s) {
        T inp;
        std::cin >> inp;

        s.push(inp);

        // This will allow chaining of operations
        return is;
    }

    template <class T>
    std::ostream& operator<<(std::ostream &os, Stack<T> &s) {
        while(!s.isEmpty()) {
            std::cout << s.getTop();
            s.pop();

            if (!s.isEmpty()) std::cout << " | ";
        }

        // This will allow chaining of operations
        return os;
    }
}

#endif /* STACK_CLASS_H */