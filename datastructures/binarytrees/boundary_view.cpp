#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
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
vector<int> boundaryTraversal(Node *);

int main() {
    /**
     * In order to find out the boundary of the tree
     * 1. Print the left boundary in top-down manner.
     * 2. Print all leaf nodes from left to right, 
     *    which can again be sub-divided into two sub-parts:
     *   -> Print all leaf nodes of left sub-tree from left to right.
     *   -> Print all leaf nodes of right subtree from left to right.
     * 3. Print the right boundary in bottom-up manner.
     */ 
    cout << "\nThis program prints boundary of a binary tree.\n" << endl;

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    vector<int> boundary = boundaryTraversal(root);

    cout << "\nBoundary traversal of the tree is :" << endl;
    for (auto &x: boundary) cout << x << " ";

    cout << endl << endl;

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

vector<int> getLeaves(Node *root) {
    vector<int> list;
    if (root == NULL) return list;

    // We will traverse the tree inorder upto
    // leaves and store them in the vector
    stack<Node *> container;
    Node *temp = root;

    while(temp || !container.empty()) {
        // In case of inorder, we traverse to the leftmost of
        // every node before printing its value & moving right
        while (temp) {
            container.push(temp);
            temp = temp->left;
        }

        // This way we will always have the leftmost value
        temp = container.top();
        container.pop();
        // This way only leaves will be stored
        if (!temp->left && !temp->right) list.push_back(temp->data);

        // After printing data of head we move to its right subtree
        temp = temp->right;
    }

    return list;
}

vector<int> getBoundaryLeft(Node *root) {
    vector<int> list;
    if (root == NULL) return list;

    // Traverse all left boundary nodes, except a leaf node.
    // Store the nodes in TOP DOWN manner
    Node *curr = root;

    while (curr) {
        if (curr->left) {
            // to ensure top down order, push the node
            // before shifting to left subtree
            list.push_back(curr->data);
            curr = curr->left;
        } else if (curr->right) {
            list.push_back(curr->data);
            curr = curr->right;
        } else {
            curr = NULL;
        }
        // Do nothing if it is a leaf node, avoiding leafs
    }

    return list;
}

// A function to print all right boundary nodes, except a leaf node
// Print the nodes in BOTTOM UP manner
vector<int> getBoundaryRight(Node* root) {
    vector<int> list;
    if (root == NULL) return list;

    // Traverse all right boundary nodes, except a leaf node.
    // Store the nodes in BOTTOM UP manner
    Node *curr = root;

    while (curr) {
        if (curr->right) {
            // push the node before shifting to next
            list.push_back(curr->data);
            curr = curr->right;
        } else if (curr->left) {
            list.push_back(curr->data);
            curr = curr->left;
        } else {
            curr = NULL;
        }
        // Do nothing if it is a leaf node, avoiding leafs
    }

    // Since we need it bottom up
    reverse(list.begin(), list.end());

    return list;
}

vector<int> boundaryTraversal(Node *root) {
    // Here we simply find out all possible
    // diretional values and combine them
    vector<int> list;
    list.push_back(root->data);

    vector<int> left = getBoundaryLeft(root->left);
    vector<int> bottom_left = getLeaves(root->left);
    vector<int> bottom_right = getLeaves(root->right);
    vector<int> right = getBoundaryRight(root->right);

    for (auto &x : left) list.push_back(x);
    for (auto &x : bottom_left) list.push_back(x);
    for (auto &x : bottom_right) list.push_back(x);
    for (auto &x : right) list.push_back(x);

    return list;
}

