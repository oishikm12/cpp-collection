#include "head_ll.h"
#include <iostream>

using namespace linkedlist;
using namespace std;

int main() {
    /**
     * We generate an instance of linked list class and perform operations
     */ 
    cout << "\nThis program generates a sample linked list object.\n" << endl;
    
    List<int> llist;
    bool flag = true;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Generate List." << endl;
        cout << "2. Print current List." << endl;
        cout << "3. Get Size of List." << endl;
        cout << "4. Insert into List." << endl;
        cout << "5. Delete from List." << endl;
        cout << "6. Search for an Element." << endl;
        cout << "7. Reverse the List." << endl;
        cout << "8. Get Middle Element." << endl;
        cout << "9. Sort the List." << endl;
        cout << "10. Exit." << endl;
        int choice;
        cin >> choice;

        // Variables for choices
        int data, pos, key;

        switch (choice) {
            case 1:
                cout << "\nEnter no. of elements to consider : ";
                cin >> pos;
                cout << "\nEnter space-seperate elements of the list:" << endl;
                for (int i = 0; i < pos; i += 1) cin >> llist;
                break;
            case 2:
                cout << "\nThe current list is:" << endl;
                cout << llist << endl;
                break;
            case 3:
                cout << "\nThe size of list is: " << llist.getSize() << endl;
                break;
            case 4:
                cout << "\nEnter the number you would like to insert ? ";
                cin >> data;
                cout << "\nEnter the position you would like to insert it at ? ";
                cin >> pos;
                llist.insert(pos, data);
                break;
            case 5:
                cout << "\nEnter the position you would like to delete from ? ";
                cin >> pos;
                llist.remove(pos);
                break;
            case 6:
                cout << "\nEnter the value to search for ? ";
                cin >> key;
                pos = llist.linearSearch(key);
                if (pos == -1) cout << "\nThe element was not found." << endl;
                else cout << "\nThe element was found at position " << pos << "." << endl;
                break;
            case 7:
                llist.reverseList();
                cout << "\nThe List has been reversed." << endl;
                cout << llist << endl;
                break;
            case 8:
                cout << "\nThe middle element is : " << llist.mid() << "." << endl;
                break;
            case 9:
                llist.sort();
                cout << "\nThe sorted list is :" << endl;
                cout << llist << endl;
                break;
            case 10:
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