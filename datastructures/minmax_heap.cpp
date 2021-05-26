#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

/**
 * A Heap is a special Tree-based data structure in which the tree
 * is a complete binary tree. Generally, Heaps can be of two types:
 * Max-Heap: The key present at the root node must be greatest among 
 *           the keys present at all of it’s children.
 * Min-Heap: The key present at the root node must be minimum among 
 *           the keys present at all of it’s children.
 * Since the tree is complete, a nodes parent is at `floor(nodeIdx)`
 * a nodes children are at 2 * nodeIdx & 2 * nodeIdx + 1
 */ 

template<typename T>
class Heap {
    private:
        vector<T> data;
        function<bool(T, T)> comparator;

    public:
        // Used to allocate vectors, and set type of heap
        Heap(bool = false);

        // Places a data in its correct position accordingly
        void push(T);

        // Checks if the heap is empty
        bool empty();

        // Finds size of heap
        int getSize();

        // Gives us the topmost element
        T top();

        // Restores heap property after a removal
        void heapify(int pos);

        // Removes an element from the heap
        void pop();

        // Overloading input operator for easy heap creation
        template <class U>
        friend istream& operator>>(istream &, Heap<U> &);

        // Overloading output operator for easy heap printing while removal
        template <class U>
        friend ostream& operator<<(ostream &, Heap<U> &);
};

template<typename T>
Heap<T> :: Heap(bool isMin) {
    // Wether we want to use this as a min heap
    if (isMin) comparator = less<T>();
    else comparator = greater<T>();
    // We do not consider 0th index for ease
    data.push_back(0);
}

template<typename T>
void Heap<T> :: push(T value) {
    // We first insert the element to end
    data.push_back(value);
    // We then restore the heap property by re-arranging elemnts
    int index = data.size() - 1;
    int parent = index / 2;

    // Comparator function checks wether the index is
    // in its correct position or not, we repeat this for all
    // nodes in the same family line
    while (index > 1 && comparator(data[index], data[parent])) {
        swap(data[index], data[parent]);
        index = parent;
        parent = parent / 2;
    }
}

template<typename T>
bool Heap<T> :: empty() {
    return data.size() == 1;
}

template<typename T>
int Heap<T> :: getSize() {
    return data.size() - 1;
}

template<typename T>
T Heap<T> :: top() {
    if (data.size() == 1) return -1;
    return data[1];
}

template<typename T>
void Heap<T> :: heapify(int pos) {
    // Since the tree itself is a complete binary tree
    // we know where the left & right child of a node is
    int leftChild = 2 * pos;
    int rightChild = 2 * pos + 1;

    // Starting by assuming current is minima
    int minIndex = pos;

    if (leftChild < data.size() && comparator(data[leftChild], data[minIndex])) {
        // Checking if the left child has a smaller / greater value
        minIndex = leftChild;
    }

    if (rightChild < data.size() && comparator(data[rightChild], data[minIndex])) {
        // Checking if right is compared differently than left
        minIndex = rightChild;
    }

    if (minIndex != pos) {
        // This means that the node was not in its correct position
        swap(data[pos], data[minIndex]);
        // Recall the function for subsequent nodes
        heapify(minIndex);
    }
}

template<typename T>
void Heap<T> :: pop() {
    if (empty()) return;

    // We fetch the last element in heap
    int last = data.size() - 1;
    // And swap it with the first
    swap(data[1], data[last]);
    data.pop_back();
    // Finally after popping topmost, we restore heap property
    heapify(1);
}

template <class T>
istream& operator>>(istream &is, Heap<T> &h) {
    T inp;
    cin >> inp;

    h.push(inp);

    // This will allow chaining of operations
    return is;
}

template <class T>
ostream& operator<<(ostream &os, Heap<T> &h) {
    while(!h.empty()) {
        cout << h.top();
        h.pop();
        // This will give space b/w output
        if (!h.empty()) cout << " ";
    }

    // This will allow chaining of operations
    return os;
}

int main() {
    /**
     * We generate an instance of a sample Min / Max Heap as desired
     */ 
    cout << "\nThis program generates a sample Min & Max Heap.\n" << endl;

    Heap<int> maxHeap(false);
    Heap<int> minHeap(true);

    bool flag = true;
    int type = 0;
    cout << "Enter 1 for MinHeap & 2 for MaxHeap: ";
    cin >> type;
    type = type % 2;

    auto heap = type == 1 ? minHeap : maxHeap;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Insert elements into Heap." << endl;
        cout << "2. Empty & Print all elements of Heap." << endl;
        cout << "3. Get Size of Heap." << endl;
        cout << "4. Check if Heap is empty." << endl;
        cout << "5. Insert into Heap." << endl;
        cout << "6. Get topmost element of Heap." << endl;
        cout << "7. Delete topmost element of Heap." << endl;
        cout << "8. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int data, pos;

        switch (choice) {
            case 1:
                cout << "\nEnter no. of elements to consider : ";
                cin >> pos;
                cout << "\nEnter space-seperate elements of the heap:" << endl;
                for (int i = 0; i < pos; i += 1) cin >> heap;
                break;
            case 2:
                cout << "\nThe contents of the heap were:" << endl;
                cout << heap << endl;
                break;
            case 3:
                cout << "\nThe size of the heap is: " << heap.getSize() << endl;
                break;
            case 4:
                if (heap.empty()) cout << "\nThe heap is empty." << endl;
                else cout << "\nThe heap is not empty." << endl;
                break;
            case 5:
                cout << "\nEnter the number you would like to insert ? ";
                cin >> data;
                heap.push(data);
                break;
            case 6:
                data = heap.top();
                if (data == -1) cout << "\nThe heap is empty." << endl;
                else cout << "\nThe topmost element is: " << data << endl;
                break;
            case 7:
                data = heap.top();
                if (data == -1) cout << "\nThe heap is empty." << endl;
                else {
                    heap.pop();
                    cout << "\n" << data << " has been popped." << endl;      
                }
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