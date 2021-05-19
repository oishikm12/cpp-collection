#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node() = default;
        Node(int d) : data(d), left(NULL), right(NULL) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildTree();
string dupeSub(Node *, unordered_set<string> &);
string printDupeHead(Node *, unordered_map<string, int> &);

int main() {
    /**
     * In order to find wether a duplicate subtree exists,
     * we will convert them into string and maintain a 
     * dictionary of root, left, right as string. Henceforth
     * if it reappears, we will be able to tell
     */
    cout << "\nThis program finds out if there exists a duplicate subtree of at least height 2 in the tree.\n" << endl; 

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    unordered_set<string> subtrees;
    bool hasDupe = dupeSub(root, subtrees) == "";

    if (hasDupe) {
        cout << "\nThis tree has duplicate subtrees. The heads are: " << endl;
        unordered_map<string, int> roots;
        printDupeHead(root, roots);
        cout << endl;
    } else cout << "\nThis tree does not have any duplicate subtrees of at least height = 2." << endl;

    cout << endl;
    delete root;

    return 0;
}

Node* buildTree() {
    int data;
    cin >> data;

    // -1 means an end Node aka leaf
    if (data == -1) return NULL;

    // Recursively build tree
    Node *curr = new Node(data);
    curr->left = buildTree();
    curr->right = buildTree();

    return curr;
}
 
string dupeSub(Node *root, unordered_set<string> &subtrees) {
    // This function returns empty string if tree
    // contains a duplicate subtree of size 2 or more.
    string s = "";
 
    // If current node is NULL, return marker
    if (!root) return s + "$";
 
    // If left subtree has a duplicate subtree.
    string lStr = dupeSub(root->left, subtrees);
    if (lStr == s) return s;
 
    // Do same for right subtree
    string rStr = dupeSub(root->right, subtrees);
    if (rStr == s) return s;
 
    // Serialize current subtree
    s = s + to_string(root->data) + lStr + rStr;
 
    // If current subtree already exists in hash
    // table. [Note that size of a serialized tree
    // with single node is 3 as it has two marker
    // nodes.
    if (s.length() > 3 && subtrees.find(s) != subtrees.end())
    return "";
 
    subtrees.insert(s);
 
    return s;
}

string printDupeHead(Node *root, unordered_map<string, int> &roots) {
    if (!root) return "";
 
    string str = "(" + printDupeHead(root->left, roots) + to_string(root->data) + printDupeHead(root->right, roots) + ")";
 
    // Subtree already present (Note that we use
    // unordered_map instead of unordered_set because
    // we want to print multiple duplicates only once
    if (roots[str] == 1) cout << root->data << " ";
 
    roots[str] += 1;

    // Return this to calling function for parent string
    return str;
}