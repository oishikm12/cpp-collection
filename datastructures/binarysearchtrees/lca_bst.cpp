#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int val = 0, Node *lc = NULL, Node *rc = NULL) : data(val), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildBST();
Node* insertInBST(Node*, int);
Node* LCA(Node *, int, int);

int main() {
    /**
     * In order to find the lowest common ancestor in
     * a binary search tree we simply have to recurse till
     * we find a middle value between the two values
     */ 
    cout << "\nThis program finds out the least common ancestor in a BST.\n" << endl;

    cout << "Enter space seperate elements of the tree," << endl;
    Node *root = buildBST();

    int val1, val2;
    cout << "\nEnter the first value whose LCA to find: ";
    cin >> val1;
    cout << "\nEnter the second value whose LCA to find: ";
    cin >> val2;

    Node *ancestor = LCA(root, val1, val2);
    cout << "\nThe ancestor to " << val1 << " and " << val2 << " is: " << ancestor->data << "." << endl;

    cout << endl;
    delete root;

    return 0;
}

Node* buildBST() {
    // Value of the root node
    int data;
    cin >> data;

    Node *curr = NULL;

    while (data != -1) {
        // We will continue to take user input
        // till user enters -1
        curr = insertInBST(curr, data);
        cin >> data;
    }

    return curr;
}

Node* insertInBST(Node *curr, int data) {
    // If we reach null this becomes desired node
    // to place the value in
    if (!curr) return new Node(data);

    // If data is smaller, it goes into left child
    // else it goes into right child
    if (data <= curr->data) curr->left = insertInBST(curr->left, data);
    else curr->right = insertInBST(curr->right, data);

    return curr;
}

Node* LCA(Node *root, int n1, int n2) {
    // Base if not found
    if (!root) return NULL;
    
    // Since we need to find middle grounds,
    // we need to know the range between the two nodes
    int mn = min(n1, n2);
    int mx = max(n1, n2);
    
    // WE simply recurse till we find a suitable node
    if (root->data < mn) return LCA(root->right, n1, n2);
    else if (root->data > mx) return LCA(root->left, n1, n2);
    
    return root;
}