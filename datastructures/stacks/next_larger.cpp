#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> nextLargerElement(vector<int> &, int);

int main() {
    /**
     * In order to find out elemnts greater than current to its right
     * we will maintain a stack of elements traversed, and whenever a
     * element greater than last inserted is found, we will pop the 
     * elements and set the greater from them as current element
     */ 
    cout << "\nThis program finds out for every element, a greater element to its right.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    vector<int> great = nextLargerElement(arr, n);

    cout << "The next greater element for every element is," << endl;
    for (int i = 0; i < n; i += 1) {
        cout << arr[i];
        if (i != n - 1) cout << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i += 1) {
        cout << great[i];
        if (i != n - 1) cout << " ";
    }

    cout << endl << endl;

    return 0;
}

vector<int> nextLargerElement(vector<int> &arr, int n) {
    // We will us this to store the previous element as
    // well as its position in the array
    stack<pair<int, int>> prev;
    vector<int> store(n, -1);
    
    prev.push(make_pair(arr[0], 0));
    
    for (int i = 1; i < n; i += 1) {
        while (!prev.empty() && prev.top().first < arr[i]) {
            // If we find a greater element, then it becomes the 
            // right greater to every element in the stack, so we
            // pop the elements, and place the current element 
            // according to their indices
            store[prev.top().second] = arr[i];
            prev.pop();
        }
        
        prev.push(make_pair(arr[i], i));
    }
    
    return store;
}