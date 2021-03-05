#include <iostream>

/**
 * Queue is a data structure which follows the FIFO paradigm of data transfer
 * In a queue the element to entered in a queue first, is the first to leave 
 * the queue. Queues usually have a fixed size, hence circular queues are used
 * for space efficiency. Queues can be specialized to store elements in specific 
 * order, or priority basis
 */ 

#ifndef QUEUE_CLASS_H
#define QUEUE_CLASS_H

#define MAX 50

namespace queue {
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
            friend std::istream& operator>>(std::istream &, Queue<U> &);

            // Overloading output operator for easy print
            template <class U>
            friend std::ostream& operator<<(std::ostream &, Queue<U> &);
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
    std::istream& operator>>(std::istream &is, Queue<T> &q) {
        T inp;
        std::cin >> inp;

        q.enqueue(inp);

        // This will allow chaining of operations
        return is;
    }

    template <class T>
    std::ostream& operator<<(std::ostream &os, Queue<T> &q) {
        while(!q.isEmpty()) {
            std::cout << q.getFront();
            q.dequeue();

            if (!q.isEmpty()) std::cout << " | ";
        }

        // This will allow chaining of operations
        return os;
    }
}

#endif /* QUEUE_CLASS_H */