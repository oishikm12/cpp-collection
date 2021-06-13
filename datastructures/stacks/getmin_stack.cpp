#include <iostream>
#include <stack>
using namespace std;

class MinStack {
    private:
        // We will store the minimal element seperately 
        int minEl; 
        stack<int> s;

    public:
        MinStack() : minEl(INT_MAX) {}

        void push(int);
        int pop();
        int top();

        int size() { return s.size(); }
        bool isEmpty() { return s.empty(); }
        int getMin() { return minEl; }
};

void MinStack :: push(int val) {
    if (s.empty()) {
        // If this is the first element in the stack
        // then we simply set the minimal element to this
        s.push(val);
        minEl = val;
        return;
    }

    if (val > minEl) s.push(val);
    else {
        // If the element we want to insert is smaller than the
        // current element then insert [top] = 2 * newMin - oldMin
        // NOTE: 2 * newMin - oldMin is always less than newMin
        s.push(val * 2 - minEl);
        minEl = val;
    }
}

int MinStack :: pop() {
    int temp = top();
    s.pop();

    if (temp < minEl) {
        // If the element we are popping is smaller than
        // what the curret minimum element is, then to 
        // restore previous, we use 2 * newMin - [top], where
        // 2 * newMin - (2 * newMin - oldMin) = oldMin
        minEl = 2 * minEl - temp;
    }

    if (s.empty()) minEl = INT_MAX;

    return temp;
}

int MinStack :: top() {
    int top = s.top();

    // If top is less than minElement, this means
    // that minEl stores our topmost element
    if (top < minEl) return minEl;
    else return top;
}

int main() {
    /**
     * In order to ensure that we can always access the minimal
     * element in a stack, we maintain an external variable storing
     * minimal, and also insert a modified version of the numbers
     * when inserting, such that we can revert to previous minimum
     */ 
    cout << "\nThis program finds out the minimal element in a stack in constant time and space.\n" << endl;

    MinStack stk;

    bool flag = true;
    int var;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Insert an element into stack." << endl;
        cout << "2. Remove an element from stack." << endl;
        cout << "3. Get topmost element." << endl;
        cout << "4. Get minimum element." << endl;
        cout << "5. Exit." << endl; 
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter the element to insert: ";
                cin >> var;
                stk.push(var);
                cout << var << " has been pushed." << endl;
                break;
            case 2:
                if (stk.isEmpty()) cout << "\nThe stack is empty." << endl;
                else {
                    var = stk.pop();
                    cout << var << " has been removed." << endl;
                }
                break;
            case 3:
                if (stk.isEmpty()) cout << "\nThe stack is empty." << endl;
                else {
                    var = stk.top();
                    cout << var << " is the topmost element." << endl;
                }
                break;
            case 4:
                if (stk.isEmpty()) cout << "\nThe stack is empty." << endl;
                else {
                    var = stk.getMin();
                    cout << var << " is the minimal element." << endl;
                }
                break;
            case 5:
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
