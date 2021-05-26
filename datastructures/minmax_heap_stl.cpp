#include <iostream>
#include <queue>
using namespace std;

int main() {
    /**
     * Like other data structures, C++ provides STL priority_queue
     * as an implementation of heap. Heap itself is implemented
     * as a complete binary tree represented in continious memory space
     */ 
    cout << "\nThis program implements a Heap via STL.\n" << endl;
    
    priority_queue<int> pq;
    // priority_queue<int, vector<int>, greater<int>()> pq;
    bool flag = true;

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
                for (int i = 0; i < pos; i += 1) {
                    cin >> data;
                    pq.push(data);
                }
                break;
            case 2:
                cout << "\nThe contents of the heap were:" << endl;
                while (!pq.empty()) {
                    data = pq.top();
                    pq.pop();
                    cout << data << " ";
                }
                cout << endl;
                break;
            case 3:
                cout << "\nThe size of the heap is: " << pq.size() << endl;
                break;
            case 4:
                if (pq.empty()) cout << "\nThe heap is empty." << endl;
                else cout << "\nThe heap is not empty." << endl;
                break;
            case 5:
                cout << "\nEnter the element to insert: ";
                cin >> data;
                pq.push(data);
                break;
            case 6:
                if (pq.empty()) cout << "\nThe heap is empty." << endl;
                else cout << "\nThe topmost element is: " << pq.top() << endl;
                break;
            case 7:
                if (pq.empty()) cout << "\nThe heap is empty." << endl;
                else {
                    data = pq.top();
                    pq.pop();
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