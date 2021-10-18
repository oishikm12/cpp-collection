#include <iostream>
#include <vector>
using namespace std;

/**
 * Fenwick Tree is a data structure which is based on trees and
 * allows us range based queries in logarithmic time. Unlike Segment
 * Trees, this precalculates cumulative sum, based on binary 
 * represention of a number converted to tree like structure
 */ 

class FenwickTree {
    private:
        vector<int> tree;

    public:
        // Initializes the binary indexed tree
        FenwickTree(int n);

        // Adds an element at a specific index
        void addElement(int, int);

        // Performs query on range
        int query(int);
};

FenwickTree :: FenwickTree(int n) {
    // Since we represent sequential series of elements,
    // there is no need to allocate more space than no. of elements
    tree.resize(n + 1, 0);
    // There is no specific building of tree, rather we update
    // each index with its desired value, from calling function itself
}

void FenwickTree :: addElement(int idx, int value) {
    // Unlike Segment Tree, elements are simply
    // inserted one by one. Since in a binary Indexed Tree
    // next element is present in next binary position,
    // we propagate the changes by setting next bit
    for (int i = idx; i < tree.size(); i += i & (-i)) {
        tree[i] += value;
    }
}

int FenwickTree :: query(int idx) {
    // We return the elements all the way from 1st index
    // Propagation is done in the same way, by incrementing
    // the next bit (adding i & (-i))
    int sum = 0;

    for (int i = idx; i > 0; i -= i & (-i)) {
        sum += tree[i];
    }

    return sum;
}

int main() {
    /**
     * We generate an instance of fenwick tree class and perform operations
     */ 
    cout << "\nThis program generates a sample BIT object to generate subarray sum.\n" << endl;
    int n;
    cout << "Enter number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the array to consider," << endl; 
    for (int i = 0; i < n; i += 1) cin >> elems[i];
    
    FenwickTree bit(n);
    for (int i = 0; i < n; i += 1) bit.addElement(i + 1, elems[i]);
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Update element of array." << endl;
        cout << "2. Query a specific range." << endl;
        cout << "3. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int idx1, idx2, val;

        switch (choice) {
            case 1:
                cout << "\nEnter index of element to update: ";
                cin >> idx1;
                cout << "\nEnter the value to add to element: ";
                cin >> val;
                bit.addElement(idx1, val);
                break;
            case 2:
                cout << "\nEnter starting range: ";
                cin >> idx1;
                cout << "\nEnter ending range: ";
                cin >> idx2;
                val = bit.query(idx2) - bit.query(idx1);
                cout << "\nThe sum from " << idx1 << " to " << idx2 << " is " << val << "." << endl;
                break;
            case 3:
                cout << "\nGoodbye !!!" << endl;
                flag = !flag;
                break;
            default:
                cout << "\nPlease try again" << endl;
                break;
        }
    }

    cout << endl;
   
    return 0;
}