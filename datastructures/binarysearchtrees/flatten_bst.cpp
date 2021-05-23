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
void printAsList(Node *);
void inorderLinkage(Node *, Node *&);
Node* flatten(Node *);

int main() {
    /**
     * In order to flatten a BST into a list, we have to
     * perform an inorder traversal, while keeping track
     * of predecessor, and connecting it to current
     */ 
    cout << "\nThis program finds flattens a BST into a sorted linked list.\n" << endl;
    
    cout << "Enter space seperated elements of the tree," << endl;
    Node *root = buildBST();

    cout << "\nThe tree flattened as a sorted linked list is," << endl;
    root = flatten(root);
    printAsList(root);

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

void printAsList(Node *root) {
    while (root) {
        cout << root->data;
        // After printing current node, we move to its right
        root = root->right;
        // If the next node is present we delimit via space
        if (root) cout << " ";
    }
    cout << endl;
}

void inorderLinkage(Node *curr, Node *&prev) {
    // Base case for no node
    if (!curr) return;

    inorderLinkage(curr->left, prev);

    // Inorder traversal results in sorted array (BST)
    // Prev node is maintained, whose right is current & left is NULL
    prev->right = curr;
    prev->left = NULL;
    prev = curr;

    inorderLinkage(curr->right, prev);
}

Node* flatten(Node *root) {
    // This is temporary for a new list
    Node *temp = new Node();
    Node *prev = temp;

    // Link every node with its previous
    // while traversing in Inorder fashion
    inorderLinkage(root, prev);

    // This is now pointing to last node
    prev->left = NULL;
    prev->right = NULL;

    // We point the root to the right of our temp node
    root = temp->right;
    temp->right = NULL;

    delete temp;
    return root;
}