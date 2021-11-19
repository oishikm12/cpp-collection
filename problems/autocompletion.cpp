#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Trie;

class Node {
    private:
        char data;
        map<char, Node*> hash;
        bool isTerminal;

    public:
        Node(char d = '\0') : data(d), isTerminal(false) {};
        ~Node() { for (auto &x : hash) delete x.second; }
        friend class Trie;
};

class Trie {
    private:
        Node *root;

    public:
        Trie() { root = new Node(); }
        ~Trie() { for (auto &x: root->hash) delete x.second, root->hash.clear(); }
        void addWord(string);
        bool search(string);
        void dfsPrint(Node*, string);
};

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

    // We have reached the last character of the pattern
    // hence we simply DFS over all possiblities from here
    dfsPrint(temp, s);

    return true;
}

void Trie :: dfsPrint(Node *curr, string s) {
    if (curr->isTerminal) {
        // This is a terminal node, hence we print the string formed so far
        cout << s << endl;
    }

    // Otherwise we iterate for all possiblities
    for (auto &[letter, node] : curr->hash) {
        s.push_back(letter);
        dfsPrint(node, s);
        s.pop_back();
    }
}

int main() {
    /**
     * In order to implement a word based dictionary system, we use a trie
     * to keep track of all words inserted, that way we can search for any 
     * word in O(log(max)) time
     */
    cout << "\nThis program finds out autocompletion words from a given pattern\n" << endl;
    int n;
    cout << "Enter the number of strings in the dictionary: ";
    cin >> n;

    Trie trie;

    cout << "Enter space seperated strings of the dictionary," << endl;
    for (int i = 0; i < n; i += 1) {
        string s;
        cin >> s;
        trie.addWord(s);
    }

    string pattern;
    cout << "\nEnter the strong whose autocompletion you want to perform: ";
    cin >> pattern;

    cout << "\nSearch Results are," << endl;
    if (!trie.search(pattern)) cout << "No results were found." << endl;

    cout << endl;

    return 0;
}