#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int> &, int, int);
void heapSort(vector<int> &, int);

int main() {
    /**
     * Heap sort is a comparison-based sorting technique based on 
     * Binary Heap data structure. It is similar to selection sort 
     * where we first find the minimum element and place the minimum 
     * element at the beginning. We repeat this for the rest
     */ 
    cout << "\nThis program sorts a given array via Heap Sort.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    heapSort(arr, n);

    cout << "\nThe sorted array is," << endl;
    for (int i = 0; i < n; i += 1) {
        cout << arr[i];
        if (i == n - 1) cout << endl;
        else cout << ", ";
    }

    cout << endl;

    return 0;
}

void heapSort(vector<int> &data, int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i -= 1) {
        heapify(data, n, i);
    }
 
    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i -= 1) {
        // Move current root to end
        swap(data[0], data[i]);
 
        // Call max heapify on the reduced heap
        heapify(data, i, 0);
    }
}

void heapify(vector<int> &data, int n, int pos) {
    // Since the tree itself is a complete binary tree
    // we know where the left & right child of a node is
    int leftChild = 2 * pos;
    int rightChild = 2 * pos + 1;

    // Starting by assuming current is minima
    int minIndex = pos;

    if (leftChild < n && data[leftChild] > data[minIndex]) {
        // Checking if the left child has a smaller / greater value
        minIndex = leftChild;
    }

    if (rightChild < n && data[rightChild] > data[minIndex]) {
        // Checking if right is compared differently than left
        minIndex = rightChild;
    }

    if (minIndex != pos) {
        // This means that the node was not in its correct position
        swap(data[pos], data[minIndex]);
        // Recall the function for subsequent nodes
        heapify(data, n, minIndex);
    }
}
 