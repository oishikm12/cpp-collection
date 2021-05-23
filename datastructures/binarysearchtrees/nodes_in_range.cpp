#include <iostream>
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
int getCountInRange(Node *, int, int);

int main() {
    /**
     * In order to finds node in range, traverse the BST 
     * starting from root. For every node check if this 
     * node lies in range, if so, add 1 and recur for both 
     * of its children. If current node is smaller than low,
     * then recur for right child, else recur for left child.
     */ 
    cout << "\nThis program finds out the number of nodes in BST between a given range.\n" << endl;
    
    cout << "Enter space seperated elements of the BST," << endl;
    Node *root = buildBST();

    int low, high;
    cout << "\nEnter space seperated low and high range to scan the BST," << endl;
    cin >> low >> high;

    int count = getCountInRange(root, low, high);

    cout << "\nThis tree has, " << count << " nodes in between " << low << " and " << high << "." << endl;

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

int getCountInRange(Node *root, int l, int h) {
    // Base Case when we hit a leaf
    if (!root) return 0;
    
    // If the value is smaller than low, the desired
    // nodes are likely to be in right subtree
    if (root->data < l) return getCountInRange(root->right, l, h);
    // Alternatively if greater, then left subtree
    if (root->data > h) return getCountInRange(root->left, l, h);
  
    // If the current node is in range, then both subtrees 
    // and the current node itself is counted
    return 1 + getCountInRange(root->left, l, h) + getCountInRange(root->right, l, h);
}