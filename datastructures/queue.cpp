#include "head_q.h"
#include <iostream>

using namespace queue;
using namespace std;

int main() {
    /**
     * We generate an instance of queue class and perform operations
     */ 
    cout << "\nThis program generates a sample queue object.\n" << endl;
    
    Queue<int> que;
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Add data to Queue." << endl;
        cout << "2. Dequeue all & Print all data." << endl;
        cout << "3. Enqueue an element to back." << endl;
        cout << "4. Dequeue an element from front." << endl;
        cout << "5. Find element in front of queue." << endl;
        cout << "6. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int data, sz;

        switch (choice) {
            case 1:
                cout << "\nEnter no. of elements to consider : ";
                cin >> sz;
                cout << "\nEnter space-seperate elements of the queue:" << endl;
                for (int i = 0; i < sz; i += 1) cin >> que;
                break;
            case 2:
                cout << "\nThe last queue was:" << endl;
                cout << que << endl;
                break;
            case 3:
                cout << "\nEnter the element to insert : ";
                cin >> data;
                que.enqueue(data);
                break;
            case 4:
                if (que.isEmpty()) {
                    cout << "\nThere are no elements to dequeue." << endl;
                } else {
                    cout << "\n" << que.getFront() << " has been removed." << endl;
                    que.dequeue();
                }
                break;
            case 5:
                cout << "\nThe frontmost element is " << que.getFront() << endl;
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