#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void sort(stack<int> &);
void sortedInsert(stack<int> &, int);
void getStackContents(stack<int> &, vector<int> &);

int main() {
    /**
     * In order to sort the contents of a stack we will use recursion
     * to pop each element, recurse to next, and then reinsert the element
     * in its desired position
     */ 
    cout << "\nThis program sorts the contents of a stack.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    stack<int> store;
    vector<int> result;
    cout << "Enter space seperated elements to push into the stack," << endl;
    for (int i = 0; i < n; i += 1) {
        int temp;
        cin >> temp;
        store.push(temp);
    }

    getStackContents(store, result);

    cout << "\nThe entered stack looks like," << endl;
    for (int i = 0; i < n; i += 1) {
        cout << result[i];
        if (i != n - 1) cout << " ";
    }

    sort(store);

    result.clear();
    getStackContents(store, result);

    cout << "\nThe sorted stack looks like," << endl;
    for (int i = 0; i < n; i += 1) {
        cout << result[i];
        if (i != n - 1) cout << " ";
    }

    cout << endl << endl;

    return 0;
}

void sort(stack<int> &store) {
    // Base condition when stack is empty
    if (store.empty()) return;

    // We pop the topmost element from the stack
    int temp = store.top();
    store.pop();

    // Recursively call for the rest of the stack to be sorted
    sort(store);

    // Once the rest is sorted, we insert the current
    // element in a sorted manner
    sortedInsert(store, temp);
}

void sortedInsert(stack<int> &store, int data) {
    // If the stack is empty, or the data on top is
    // less than what we have, we insert the data
    if (store.empty() || store.top() < data) {
        store.push(data);
        return;
    }

    // We store the current element at temp and remove it 
    // from the stack. This is continued reursively till the
    // sorted order is maintained, and then reinsert
    int temp = store.top();
    store.pop();

    sortedInsert(store, data);

    // After sorted insertion we simply reinsert the element
    store.push(temp);
}

void getStackContents(stack<int> &store, vector<int> &contents) {
    // Base condition when stack is empty
    if (store.empty()) return;

    // We store the current top in a temp variable, and then
    // pop the element, such that top is changed to next element
    int temp = store.top();
    store.pop();

    // We store the current element in the vector, and then
    // recursively call the function
    contents.push_back(temp);

    getStackContents(store, contents);

    // We then push the element back to prevent any change to stack
    store.push(temp);
}