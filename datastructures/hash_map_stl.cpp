#include <iostream>
#include <unordered_map>
using namespace std;

void print(unordered_map<string, int> &);

int main() {
    /**
     * Like with most other data structures, C++ provides STL <unordered_map>
     * for implementing a hash map. Unlike <map> which is implemented
     * as a Red Black Tree, unordered map uses hash functions to store
     * elements as per key, without any order
     */ 
    cout << "\nThis program implements Hash Map via STL\n" << endl;

    unordered_map<string, int> store;
    bool flag = true;

    string key;
    int val;
    pair<string, int> temp;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Insert element into map" << endl;
        cout << "2. Print all elements in map" << endl;
        cout << "3. Search for an element" << endl;
        cout << "4. Remove an element" << endl;
        cout << "5. Get size of map, and load factor" << endl;
        cout << "6. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter space seperated key & value pair," << endl;
                cin >> key >> val;
                store.insert(make_pair(key, val));
                cout << "\nA record for [" << key << " : " << val << "] has been created." << endl;
                break;
            case 2:
                cout << "\nAll records in the map are: " << endl;
                print(store);
                break;
            case 3:
                cout << "\nEnter the key to search for: ";
                cin >> key;
                if (store.find(key) != store.end()) cout << "\nFound " << store[key] << " for " << key << "." << endl;
                else cout << "The record was not found." << endl;
                break;
            case 4:
                cout << "\nEnter the key of the entry to remove: ";
                cin >> key;
                if (store.erase(key) == true) cout << "The reord has been deleted." << endl;
                else cout << "The record does not exist." << endl;
                break;
            case 5:
                cout << "\nThe map has " << store.size() << " elements and load factor is: " << store.load_factor() << "." << endl;
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

    cout << endl;

    return 0;
}

void print(unordered_map<string, int> &store) {
    int n = store.bucket_count();

    for (int i = 0; i < n; i += 1) {
        // This bucket is empty
        if (store.begin(i) == store.end(i)) continue;

        cout << "Bucket #" << i << ": " ;
        for (auto it = store.begin(i); it != store.end(i); ++it) {
            cout << it->first << "[" << it->second << "]";
        }

        cout << endl;
    }
}
