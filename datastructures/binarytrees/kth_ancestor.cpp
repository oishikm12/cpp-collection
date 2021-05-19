#include <iostream>
#include <queue>
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
pair<int, int> kthAncestor(Node *, int, int);

int main() {
    /**
     * In order to find the kth ancestor we will simply
     * use postorder traversal and return a pair for each
     * node, the first will denote the distance, and the
     * second kth ancestor if found
     */
    cout << "\nThis program finds out the kth ancestor of a node.\n" << endl; 

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    int val, k;
    cout << "Enter the value whose ancestor to find: ";
    cin >> val;
    cout << "Enter the value of k, i.e. distance to ancestor: ";
    cin >> k;

    int ancestor = kthAncestor(root, val, k).first;

    cout << "\nThe ancestor " << k << " distance away is " << ancestor << "." << endl;

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

pair<int, int> kthAncestor(Node *root, int val, int k) {
    // Base case upon reaching post leaf
    if (!root) return make_pair(-1, -1);

    // We found the value at this position
    if (root->data == val) return make_pair(-1, 0);

    // Postorder recursive call till we find the element
    pair<int, int> left = kthAncestor(root->left, val, k);
    pair<int, int> right = kthAncestor(root->right, val, k);

    // Since we have already found kth ancestor,
    // no need to process any further
    if (left.first != -1) return left;
    if (right.first != -1) return right;

    int nxt = -1;
    int dist = -1;

    // This will add to already calculating distance
    // When distance hits k, it will store the ancestor
    if (left.second != -1) {
        dist = left.second + 1;
        if (dist == k) nxt = root->data;
    } else if (right.second != -1) {
        dist = right.second + 1;
        if (dist == k) nxt = root->data;
    }

    return make_pair(nxt, dist);
}