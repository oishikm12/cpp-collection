#include <iostream>
#include <unordered_set>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int d = 0, Node *lc = NULL, Node *rc = NULL) : data(d), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildBST();
Node* insertInBST(Node *, int);
void traverse(Node *, unordered_set<int> &, unordered_set<int> &);
bool isDead(Node *);

int main() {
    /**
     * In order to finds nodes which can have no nodes in 
     * a BST, we will maintain a set for all nodes & a seperate
     * set for leaf nodes. In essence a leaf node is dead
     * if its value + 1 & value - 1 already exists in the tree
     */ 
    cout << "\nThis program finds out if any leaf node in this tree can have no child.\n" << endl;
    
    cout << "Enter space seperated elements of the BST," << endl;
    Node *root = buildBST();

    bool hasDeadNodes = isDead(root);

    if (hasDeadNodes) cout << "\nThis tree has dead nodes." << endl;
    else cout << "\nThis tree has no dead nodes." << endl;
    
    cout << endl;
    delete root;

    return 0;
}

Node* buildBST() {
    // First take the data from user
    int data;
    cin >> data;

    // We initialize a pointer to to store data in
    Node *curr = NULL;

    // While user does not enter -1, we continue to push data into tree
    while (data != -1) {
        curr = insertInBST(curr, data);
        cin >> data;
    }

    return curr;
}

Node* insertInBST(Node* curr, int data) {
    // Base case when we have reached desired position
    if (curr == NULL) return new Node(data);

    // Recursive case to place data in desired position
    if (data <= curr->data) curr->left = insertInBST(curr->left, data);
    else curr->right = insertInBST(curr->right, data);

    return curr;
}

void traverse(Node *root, unordered_set<int> &all, unordered_set<int> &leaf) {
    // Base condition after hitting leaf
    if (!root) return;
    
    // Postorder traversal, but any would do
    traverse(root->left, all, leaf);
    traverse(root->right, all, leaf);
    
    // If the current node is a leaf, we insert it
    // into leaf, every node is inserted into all
    if (!root->left && !root->right) leaf.insert(root->data);
    all.insert(root->data);
}

bool isDead(Node *root) {
    // Base
    if (!root) return true;
    
    // Create two empty hash sets that store all
    // BST elements and leaf nodes respectively.
    unordered_set<int> all, leaf;
    
    // Insert 0 to handle case of `1` value node
    all.insert(0);
    
    traverse(root, all, leaf);
    
    for (auto &x : leaf) {
        // Here we check first and last element of
        // continuous sequence that are x-1 & x+1
        if (all.find(x - 1) != all.end() && all.find(x + 1) != all.end()) return true;
    }
    
    return false;
}