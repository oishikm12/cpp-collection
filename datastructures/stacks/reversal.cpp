#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void reverse(stack<int> &);
void insertAtEnd(stack<int> &, int);
void getStackContents(stack<int> &, vector<int> &);

int main() {
    /**
     * In order to reverse the contents of a stack, we will use a
     * recursive function that will pop the topmost elment, recursively
     * call the same function, and then re insert the current element
     * at the end of the stack
     */ 
    cout << "\nThis program reverses the contents of a stack.\n" << endl;
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

    reverse(store);

    result.clear();
    getStackContents(store, result);

    cout << "\nThe reversed stack looks like," << endl;
    for (int i = 0; i < n; i += 1) {
        cout << result[i];
        if (i != n - 1) cout << " ";
    }

    cout << endl << endl;

    return 0;
}

void reverse(stack<int> &store) {
    // Base condition when stack is empty
    if (store.empty()) return;

    // We pop the topmost element from the stack
    int temp = store.top();
    store.pop();

    // Recursively call for the rest of the stack to be reversed
    reverse(store);

    // Once the rest is reversed, we insert the current
    // element in its correct position, i.e. at the end
    insertAtEnd(store, temp);
}

void insertAtEnd(stack<int> &store, int data) {
    // If the stack is empty, the first is the last position
    if (store.empty()) {
        store.push(data);
        return;
    }

    // We store the current element at temp and remove it 
    // from the stack. This is continued reursively till the
    // stack is empty, and the element is inserted in the end
    int temp = store.top();
    store.pop();

    insertAtEnd(store, data);

    // After insertion we simply reinsert the element
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