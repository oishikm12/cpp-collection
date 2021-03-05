#include <iostream>
#include <stack>
using namespace std;

int main() {
    /**
     * STL Provides us with stack header file in order to create a
     * stack with all functions prebuilt
     */ 
    cout << "\nThis program generates a stack via STL.\n" << endl;
    
    stack<int> stk;
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
                for (int i = 0; i < sz; i += 1) {
                    // Add each element to the stack end
                    cin >> data;
                    stk.push(data);
                }
                break;
            case 2:
                cout << "\nThe last stack was:" << endl;
                while (!stk.empty()) {
                    // Traversing involves popping all elements
                    cout << stk.top();
                    stk.pop();
                    if (!stk.empty()) cout << " | ";
                }
                cout << endl;
                break;
            case 3:
                cout << "\nEnter the element to insert : ";
                cin >> data;
                stk.push(data);
                break;
            case 4:
                if (stk.empty()) {
                    cout << "\nThere are no elements to pop." << endl;
                } else {
                    cout << "\n" << stk.top() << " has been popped." << endl;
                    stk.pop();
                }
                break;
            case 5:
                cout << "\nThe topmost element is " << stk.top() << endl;
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