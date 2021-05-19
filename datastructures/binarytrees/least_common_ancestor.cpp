#include <iostream>
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
Node* lowestCommonAncestor(Node *, int, int);

int main() {
    /**
     * In order to find the lowest common ancestor, we will
     * simply recurse to either side, in postorder fashion 
     * and return whichever node matches the value, or is not 
     * NULL. Eventually LCS will be the node that matches
     */
    cout << "\nThis program finds out the least common ancestor of two nodes in the given tree.\n" << endl; 

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    int first, second;
    cout << "\nEnter the first node to consider: ";
    cin >> first;
    cout << "\nEnter the second node to consider: ";
    cin >> second;

    Node *common = lowestCommonAncestor(root, first, second);

    cout << "\nThe lowest common ancestor of " << first << " and " << second << " is " << common->data << "." << endl;

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

Node* lowestCommonAncestor(Node *root, int first, int second) {
    // Base condition, when we heat NULL, or find 
    // one of the elements we have to find LCA of
    if (!root || root->data == first || root->data == second) return root;

    // Recursively search for the elements
    // down the tree (postorder)
    Node *left = lowestCommonAncestor(root->left, first, second);
    Node *right = lowestCommonAncestor(root->right, first, second);

    // If we were able to find one of the values, 
    // we return that. This will also handle the 
    // case when we recieve NULL, i.e. this subtree 
    // has none of the desired value
    if (!left) return right;
    if (!right) return left;

    // If at any point we have both left & right,
    // this signifies this is the node where both
    // subtrees meet, and is the lowest common ancestor
    return root;
}