#include <iostream>
#include <vector>
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
void printKSumPaths(Node *, vector<int> &, int);

int main() {
    cout << "\nThis program finds out all the paths with sum up to `k` in a tree.\n" << endl; 
    int k;
    cout << "Enter the sum that we need to search for: ";
    cin >> k;

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    vector<int> path;
    printKSumPaths(root, path, k);

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

void printKSumPaths(Node *root, vector<int> &path, int k) {
    // Base condition when we hit end
    if (!root) return;

    // We add the current element to the path
    path.push_back(root->data);

    // We are going to traverse in preorder
    printKSumPaths(root->left, path, k);
    printKSumPaths(root->right, path, k);

    int sum = 0;
    // During each recursive loop we will check 
    // if we have formed such a path
    for (int i = path.size() - 1; i >= 0; i += 1) {
        // We start from the end, because the traversal
        // is preorder, i.e. root is the last node to 
        // be popped from path vector
        sum += path[i];

        if (sum == k) {
            for (int j = i; j < path.size(); j += 1) cout << path[j] << " ";
            cout << endl;
        }
    }

    // Remove this node after traversal
    path.pop_back();
}