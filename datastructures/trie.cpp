#include <iostream>
#include <unordered_map>
using namespace std;

/**
 * A trie is a tree-like data structure whose nodes store the 
 * letters of an alphabet. By structuring the nodes in a particular 
 * way, words and strings can be retrieved from the structure by 
 * traversing down a branch path of the tree. 
 *    .- b
 * a -|        => ["ab", "ac"]
 *    `- c  
 */

class Trie;

class Node {
    private:
        char data;
        unordered_map<char, Node*> hash;
        bool isTerminal;

    public:
        // Initializes values and mappings
        Node(char = '\0');

        // Deallocates Children Nodes
        ~Node();

        // Ease of access from caller class
        friend class Trie;
};

class Trie {
    private:
        Node *root;

    public:
        // Assigns Root node
        Trie();

        // Deallocates All Trie Nodes
        ~Trie();

        // Adds a new word to Trie
        void addWord(string);

        // Searches for a word
        bool search(string);

        // Deletes a word if present
        bool deleteWord(string);

        // Recursively removes letters of a word
        Node* remove(Node *, string &, int);

        // Ease of calling recursive function
        void displayWords();

        // Displays all words recursively
        void print(Node *, string);
};

Node :: Node(char val) {
    data = val;
    isTerminal = false;
}

Node :: ~Node() {
    // Removes all children nodes, i.e calls their destructors
    for (auto &x : hash) delete x.second;
}

Trie :: Trie() {
    // Base node is never used
    root = new Node();
}

Trie :: ~Trie() {
    // We do not actually delete the root node itself
    for (auto &x: root->hash) delete x.second;
    root->hash.clear();
}

void Trie :: addWord(string s) {
    // Iterator over root
    Node *temp = root;

    for (auto &x : s) {
        // We iterate over every character of string
        if (temp->hash.count(x) == 0) {
            // If the current node does not have any
            // child with this character, we simply
            // create it and link it to current
            Node *child = new Node(x);
            temp->hash[x] = child;
            temp = child;
        } else {
            // Otherwise we move to that character node
            temp = temp->hash[x];
        }
    }

    // Since temp is now at last character, we mark it terminal
    temp->isTerminal = true;
}

bool Trie :: search(string s) {
    // Iterator over root
    Node *temp = root;

    for (auto &x : s) {
        // We iterate and check if every character is present
        if (temp->hash.count(x) == 0) {
            // The character is not present
            return false;
        } else {
            temp = temp->hash[x];
        }
    }

    // When we reach the last character of string, we
    // have to check if it is terminal in the Trie too
    return temp->isTerminal;
}

bool Trie :: deleteWord(string key) {
    if (search(key) == false) return false;

    root = remove(root, key, 0);

    return true;
}

Node* Trie :: remove(Node *curr, string &key, int depth) {
    // If tree beyond is empty
    if (curr == NULL) return NULL;

    // The last letter of word is being processed
    if (depth == key.size()) {
        // The node is not the end of word after deletion
        if (curr->isTerminal) curr->isTerminal = false;

        // If the node is the last of line
        if (curr->hash.empty()) {
            delete curr;
            curr = NULL;
        }

        return curr;
    }

    char nextChar = key[depth];

    // Recursively move to the last node before deleting
    curr->hash[nextChar] = remove(curr->hash[nextChar], key, depth + 1);

    // If the next node has been deleted, then we remove
    // the element from the map itself
    if (curr->hash[nextChar] == NULL) curr->hash.erase(nextChar);

    // If current does not have any child (its only child got
    // deleted), and it is not end of another word or the root
    if (curr->hash.empty() && curr->isTerminal == false && curr->data != '\0') {
        delete curr;
        curr = NULL;
    }

    return curr;
}

void Trie :: displayWords() {
    for (auto &x : root->hash) {
        // Recursively calling display function
        print(x.second, "");
    }
}

void Trie :: print(Node *curr, string host) {
    // We add the current letter to word
    host.push_back(curr->data);

    if (curr->isTerminal == true) {
        // We have reached the word end, and we will print
        cout << host << endl;
        return;
    }

    // We recursively call for every child this node has
    for (auto &n : curr->hash) {
        print(n.second, host);
    }
}

int main() {
    /**
     * We generate an instance of Trie, and store strings in it
     */
    cout << "\nThis program crates a sample Trie Instance.\n" << endl; 

    Trie dict;

    bool flag = true;
    string word;

    while (flag) {
        cout << "\nEnter your choice:" << endl;
        cout << "1. Insert words into Trie" << endl;
        cout << "2. Check if a word exists in Trie" << endl;
        cout << "3. Delete a word from the Trie" << endl;
        cout << "4. Print all words in Trie" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nEnter the word to insert: ";
                cin >> word;
                dict.addWord(word);
                cout << word << " has been inserted." << endl;
                break;
            case 2:
                cout << "\nEnter the word to check: ";
                cin >> word;
                if (dict.search(word)) cout << "The word " << word << " exists in the trie." << endl;
                else cout << "The word " << word << " does not exist in the trie." << endl;
                break; 
            case 3:
                cout << "\nEnter the word to delete: ";
                cin >> word;
                if (dict.deleteWord(word)) cout << "The word " << word << " has been deleted." << endl;
                else cout << "The word " << word << " was not found.";
                break;
            case 4:
                cout << "\nAll the words in the trie are," << endl;
                dict.displayWords();
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