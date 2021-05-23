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
void findPreSuc(Node *, Node *&, Node *&, int);

int main() {
    /**
     * In order to find the inorder successor and predecessor
     * of a node, we simply recurse first, wherein every recurse
     * to left, the parent becomes successor, and for right
     * becomes predecessor. When we do reach the node, the rightmost
     * in the leftsubtree is predecessor & leftmost in right
     * subtree is successor
     */ 
    cout << "\nThis program finds out inorder successor & predecessor of a node in BST\n" << endl;

    cout << "Enter space seperate elements of the tree," << endl;
    Node *root = buildBST();

    int val;
    cout << "\nEnter the node whose successor & predecessor to find: ";
    cin >> val;

    Node *pre, *suc;
    findPreSuc(root, pre, suc, val);
    cout << "\nThe predecessor to " << val << " is " << pre->data << ", and successor is " << suc->data << "." << endl;

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

void findPreSuc(Node *root, Node *&pre, Node *&suc, int data) {
    // Base condition when we hit post leaf
    if (!root) return;
    
    if (root->data == data) {
        if (root->left) {
            // the maximum value in left subtree is predecessor
            Node *temp = root->left;
            while(temp->right) temp = temp->right;
            pre = temp;
        }
        if (root->right) {
            // the minimum value in right subtree is successor
            Node *temp = root->right;
            while(temp->left) temp = temp->left;
            suc = temp;
        }
        
        return;
    }
    
     // If key is smaller than root's key, go to left subtree
     // else go to right subtree
    if (root->data > data) {
        suc = root;
        findPreSuc(root->left, pre, suc, data);
    } else {
        pre = root;
        findPreSuc(root->right, pre, suc, data);
    }
}