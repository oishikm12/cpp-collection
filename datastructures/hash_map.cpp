#include <iostream>
using namespace std;

#define MAX 50
#define PRIME 37
#define LOAD 0.7

/**
 * A hash table is a data structure that implements an associative 
 * array abstract data type, a structure that can map keys to values.
 * [{Key} : {Value}, {Key} : {Value}]
 * Since multiple data can have same key, we have collision avoidance
 * -> 1. Use linked list to store multidata for same key (chaining)
 * -> 2. Store in next free key (open addressing)
 * -> 3. Overwrite current data
 */ 

template <typename T>
class HashMap;

template <typename T>
class Node {
    private:
        Node<T> *next;

    public:
        pair<string, T> data;

        // Used to assign data & allocate memory
        Node(pair<string, T>);

        // Deallocates Data
        ~Node();

        // Allows private data access from Hash class
        friend class HashMap<T>;
};

template <typename T>
class HashMap {
    private:
        int currSize;
        int maxSize;
        int multiplier;
        Node<T> **buckets;

    public:
        // Assigns buckets, and space for table
        HashMap(int = MAX, int = PRIME);

        // Deallocates all buckets
        ~HashMap();

        // Maps a certain key to certain index of bucket
        int hashFunc(string);

        // Recreates hash table by doubling capacity
        void rehash();

        // Inserts a value into map
        void insert(pair<string, T>);

        // Finds out load of the map
        pair<int, double> getLoad();

        // Prints all values from map
        void print();

        // Finds a specific value by key
        Node<T>* search(string);

        // Removes a specific entry
        bool erase(string);

        // Overload access & insertion operator []
        T& operator[] (string);
};

template <typename T>
Node<T> :: Node(pair<string, T> val) {
    data = val;
    next = NULL;
}

template <typename T>
Node<T> :: ~Node() {
    delete next;
    next = NULL;
}

template <typename T>
HashMap<T> :: HashMap(int size, int seed) {
    maxSize = size;
    currSize = 0;
    multiplier = seed;

    buckets = new Node<T>*[maxSize];
    for (int i = 0; i < maxSize; i += 1) buckets[i] = NULL;
}

template <typename T>
HashMap<T> :: ~HashMap() {
    for (int i = 0; i < maxSize; i += 1) delete buckets[i];

    delete[] buckets;
}

template <typename T>
int HashMap<T> :: hashFunc(string key) {
    int len = key.size();
    int idx = 0;

    // We will be using a prime modulo function
    // to generate unique hashes for keys
    int primeMod = 1;

    for (int i = 0; i < len; i += 1) {
        // The hash function itself works by adding
        // each character of key, multiplied by a unique
        // prime number to generate index to store it at 
        idx = (idx + key[len - i - 1] * primeMod) % maxSize;
        primeMod = (primeMod * multiplier) % maxSize; 
    }

    return idx;
}

template <typename T>
void HashMap<T> :: rehash() {
    // We first backup the previous items and size
    Node<T> **oldBuckets = buckets;
    int oldSize = maxSize;

    // We reset current size to 0
    // and double the previous size of the map
    maxSize = maxSize * 2;
    currSize = 0;

    buckets = new Node<T>*[maxSize];
    for (int i = 0; i < maxSize; i += 1) buckets[i] = NULL;

    for (int i = 0; i < oldSize; i += 1) {
        if (oldBuckets[i] == NULL) continue;

        // We traverse over all elements in the old map
        // and reinsert them into new bucket, while
        // deallocataing space for old nodes
        Node<T> *temp = oldBuckets[i];

        while (temp != NULL) {
            insert(temp->data);
            temp = temp->next;
        }

        delete oldBuckets[i];
    }

    delete[] oldBuckets;
}

template <typename T>
void HashMap<T> :: insert(pair<string, T> data) {
    // First we find a suitable index for this key
    int idx = hashFunc(data.first);

    // We then allocate space for this node
    Node<T> *curr = new Node<T>(data);
    
    // We first check if the bucket at the specified
    // index is empty, if so, we place the item
    if (buckets[idx] == NULL) buckets[idx] = curr;
    else {
        // If there are elements at that index,
        // we traverse to check if the same key might
        // exist already
        Node<T> *temp = buckets[idx];
        bool same = false;

        while (temp != NULL) {
            if (temp->data.first == data.first) {
                same = true;
                break;
            }
            temp = temp->next;
        }
        
        // If we find an entry with an identical key
        // we simply update the record instead of inserting
        if (same) temp->data = data;
        else {
            // Otherwise we attach this node to the start of
            // the bucket list
            curr->next = buckets[idx];
            buckets[idx] = curr;
            currSize += 1;
        }
    }

    if (getLoad().second > LOAD) rehash();
}

template <typename T>
pair<int, double> HashMap<T> :: getLoad() {
    // Load factor reprsents how many elements are stuffed
    // into current capacity, we rehash when too many
    // elements are present in smaller hash table
    double loadFactor = (double) currSize / maxSize;
    return make_pair(currSize, loadFactor);
}

template <typename T>
void HashMap<T> :: print() {
    for (int i = 0; i < maxSize; i += 1) {
        // While iterating over buckets we check if 
        // any of them has stored data, and print them
        if (buckets[i] == NULL) continue;

        Node<T> *temp = buckets[i];
        cout << "Bucket #" << i << ": ";
        while (temp != NULL) {
            cout << temp->data.first << "[" << temp->data.second << "]";
            temp = temp->next;

            // For proper indenting and ease of understanding
            if (temp != NULL) cout << ", ";
        }

        cout << endl;
    }
}

template <typename T>
Node<T>* HashMap<T> :: search(string key) {
    // First we generate a suitable hash table position
    int idx = hashFunc(key);

    // We then simply traverse till we find it or return NULL
    Node<T> *temp = buckets[idx];
    while (temp != NULL && temp->data.first != key) temp = temp->next;

    return temp;
}

template <typename T>
bool HashMap<T> :: erase(string key) {
    // This element does not exist
    if (search(key) == NULL) return false;

    int idx = hashFunc(key);

    Node<T> *prev = NULL;
    Node<T> *temp = buckets[idx];

    // We backup the last found node, just before
    // the one we want to delete
    while (temp->data.first != key) {
        prev = temp;
        temp = temp->next;
    }

    // If a middle node is to be deleted, we
    // attach the previous to next of current
    // If the first node itself is to be deleted,
    // we simply move the bucket pointer to next of head
    if (prev != NULL) prev = temp->next;
    else buckets[idx] = temp->next;

    temp->next = NULL;
    delete temp;

    currSize -= 1;

    return true;
}

template <typename T>
T& HashMap<T> :: operator[] (string key) {
    Node<T> *temp = search(key);
 
    if (temp == NULL) {
        // If the indexed entry does not exist,
        // we create a new entry and return reference to it
        T garbage;
        insert(make_pair(key, garbage));

        return *(search(key)->data.second);
    }

    // We are returning reference to data to allow
    // user to change the data if needed
    return *(temp->data.second);
}

int main() {
    /**
     * We generate an instance of Hash Map and store items in it
     */
    cout << "\nThis program crates a sample Hash Map Instance.\n" << endl; 

    HashMap<int> store;

    bool flag = true;

    string key;
    int val;
    Node<int> *temp;

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
                store.print();
                break;
            case 3:
                cout << "\nEnter the key to search for: ";
                cin >> key;
                temp = store.search(key);
                if (temp != NULL) cout << "\nFound " << temp->data.second << " for " << temp->data.first << "." << endl;
                else cout << "The record was not found." << endl;
                break;
            case 4:
                cout << "\nEnter the key of the entry to remove: ";
                cin >> key;
                if (store.erase(key) == true) cout << "The reord has been deleted." << endl;
                else cout << "The record does not exist." << endl;
                break;
            case 5:
                cout << "\nThe map has " << store.getLoad().first << " elements and load factor is: " << store.getLoad().second << "." << endl;
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
