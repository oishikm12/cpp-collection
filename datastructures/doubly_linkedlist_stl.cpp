#include <iostream>
#include <list>
#include <iterator>
using namespace std;

void prettyPrint(list<int> &);
void insert(list<int> &, int, int);
void remove(list<int> &, int);
int linearSearch(list<int> &, int);
int getMid(list<int> &);

int main() {
    /**
     * Like with most other data structures, C++ provides STL <list>
     * for implementing doubly linked list. Implementation of singly
     * linked list can be done via <forward_list> Unlike vectors linked
     * list has quicker insertion and deletion time
     */ 
    cout << "\nThis program implements linked list via STL\n" << endl;

    list<int> llist;
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
                for (int i = 0; i < pos; i += 1) {
                    int temp;
                    cin >> temp;
                    llist.push_back(temp);
                }
                break;
            case 2:
                cout << "\nThe current list is:" << endl;
                prettyPrint(llist);
                break;
            case 3:
                cout << "\nThe size of list is: " << llist.size() << endl;
                break;
            case 4:
                cout << "\nEnter the number you would like to insert ? ";
                cin >> data;
                cout << "\nEnter the position you would like to insert it at ? ";
                cin >> pos;
                insert(llist, pos, data);
                break;
            case 5:
                cout << "\nEnter the position you would like to delete from ? ";
                cin >> pos;
                remove(llist, pos);
                break;
            case 6:
                cout << "\nEnter the value to search for ? ";
                cin >> key;
                pos = linearSearch(llist, key);
                if (pos == -1) cout << "\nThe element was not found." << endl;
                else cout << "\nThe element was found at position " << pos << "." << endl;
                break;
            case 7:
                llist.reverse();
                cout << "\nThe List has been reversed." << endl;
                prettyPrint(llist);
                break;
            case 8:
                cout << "\nThe middle element is : " << getMid(llist) << "." << endl;
                break;
            case 9:
                llist.sort();
                cout << "\nThe sorted list is :" << endl;
                prettyPrint(llist);
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

void prettyPrint(list<int> &l) {
    // We use a iterator to traverse all elements of the list
    // alternatively auto can be used to traverse
    list<int> :: iterator it = l.begin();

    while (it != l.end()) {
        cout << *it;
        it++;
        if(it != l.end()) cout << " > ";
    }

    cout << endl;
}

void insert(list<int> &l, int pos, int data) {
    // If we need to add to front
    if (pos == 0) {
        l.push_front(data);
        return;
    }

    // If we need to add to tail
    if (pos == -1 || pos >= l.size()) {
        l.push_back(data);
        return;
    }

    // Iterate over all elements
    list<int> :: iterator it = l.begin();
    
    // Move iterator to desired position
    advance(it, pos);

    l.insert(it, data);
}

void remove(list<int> &l, int pos) {
    if (l.size() == 0) return;

    // If we need to delete from head
    if (pos == 0) {
        l.pop_front();
        return;
    }

    // If we need to delete from tail
    if (pos == -1 || pos >= l.size()) {
        l.pop_back();
        return;
    }

    // Iterate over all elements
    list<int> :: iterator it = l.begin();
    
    // Move iterator to desired position
    advance(it, pos);

    l.erase(it);
}

int linearSearch(list<int> &l, int key) {
    // Iterate over all elements
    list<int> :: iterator it;
    int pos = 0;

    for (it = l.begin(); it != l.end(); it++) {
        if (*it == key) return pos;
        pos += 1;
    }

    return -1;
}

int getMid(list<int> &l) {
    int size = l.size();

    if (size == 0) return 0;

    if (size == 1) return l.front();

    list<int> :: iterator it = l.begin();

    // Move ahead to half position
    advance(it, size / 2);

    return *it;
}