#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
void levelPrint(Node *);
void inorderStore(Node *, vector<Node *> &);
Node* balance(Node *);
Node* buildBalanced(vector<Node *> &, int, int);

int main() {
    /**
     * In order to balance a skewes binary search tree
     * we will simply inorder traverse it, store the elements
     * in a vector, sort it and finaly use binary division
     * to construct a new binary search tree
     */ 
    cout << "\nThis program converts a skewed BST into a balanced BST.\n" << endl;

    cout << "Enter space seperate elements of the tree," << endl;
    Node *root = buildBST();

    cout << "\nThe skewed tree looks like," << endl;
    levelPrint(root);
    cout << endl;

    cout << "\nThe tree after balancing looks like," << endl;
    root = balance(root);
    levelPrint(root);
    
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

void levelPrint(Node *root) {
    // In order to traverse level wise we use a queue to store 
    // current levels nodes. Since queue is FIFO, this ensures 
    // nodes of a certain level are printed before next level
    queue<Node *> container;

    Node *temp = root;
    container.push(temp);

    while (!container.empty()) {
        // By checking its size we know exactly how many nodes in this level
        int n = container.size();

        while (n--) {
            temp = container.front();
            container.pop();
            cout << temp->data << " ";

            // We check if it has children and accordingly print
            if (temp->left != NULL) container.push(temp->left);
            if (temp->right != NULL) container.push(temp->right);
        }

        cout << endl;
    }
}

void inorderStore(Node *root, vector<Node *> &nodes) {
    // Base case
    if (root==NULL) return;
  
    // Store nodes in Inorder (which is sorted order for BST)
    inorderStore(root->left, nodes);
    nodes.push_back(root);
    inorderStore(root->right, nodes);
}

Node* balance(Node *root) {
    // We store the values in sorted inorder manner
    vector<Node *> nodes;
    inorderStore(root, nodes);

    // We call the recursive function to build the tree
    return buildBalanced(nodes, 0, nodes.size() - 1);
}

Node* buildBalanced(vector<Node *> &nodes, int left, int right) {
    // We have hit leaf
    if (left > right) return NULL;

    // Since the nodes are sorted, middle is the
    // middle most value, i.e suitable for root
    int mid = (right - left) / 2 + left;
    Node *root = nodes[mid];

    // We then reconstruct every node to its left
    // and to its right in the same manner
    root->left = buildBalanced(nodes, left, mid - 1);
    root->right = buildBalanced(nodes, mid + 1, right);

    return root;
}