#include <iostream>
#include <queue>
using namespace std;

int main() {
    /**
     * STL Provides us with queue header file in order to create a
     * queue with all functions prebuilt. Alternatively to headers
     * like priority_queue can be used to create a queue which is always
     * sorted in nature
     */ 
    cout << "\nThis program generates a queue via STL.\n" << endl;
    
    queue<int> que;
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Add data to Queue." << endl;
        cout << "2. Pop all & Print all data." << endl;
        cout << "3. Push one element into back." << endl;
        cout << "4. Pop one element from front." << endl;
        cout << "5. Find frontmost element." << endl;
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
                for (int i = 0; i < sz; i += 1) {
                    // Add each element to the queue end
                    cin >> data;
                    que.push(data);
                }
                break;
            case 2:
                cout << "\nThe last queue was:" << endl;
                while (!que.empty()) {
                    // Traversing involves dequeuing all elements
                    cout << que.front();
                    que.pop();
                    if (!que.empty()) cout << " | ";
                }
                cout << endl;
                break;
            case 3:
                cout << "\nEnter the element to insert : ";
                cin >> data;
                que.push(data);
                break;
            case 4:
                if (que.empty()) {
                    cout << "\nThere are no elements to dequeue." << endl;
                } else {
                    cout << "\n" << que.front() << " has been dequeued." << endl;
                    que.pop();
                }
                break;
            case 5:
                cout << "\nThe frontmost element is " << que.front() << endl;
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