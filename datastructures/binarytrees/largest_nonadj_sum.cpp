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
pair<int, int> getLargestDisjointSum(Node *);

int main() {
    /**
     * In order to find the largest disjoint node sum, we will
     * return two things as a pair, the first being the sum if the
     * current node is seleceted, other being if not selected
     */
    cout << "\nThis program finds out the largest disjoint node in the given tree.\n" << endl; 

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    pair<int, int> disjointSum = getLargestDisjointSum(root);
    int maxSum = max(disjointSum.first, disjointSum.second);

    cout << "\nThe largest disjoint node sum possible here is: " << maxSum << "." << endl;

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

pair<int, int> getLargestDisjointSum(Node *root) {
    // Base condition when we reach NULL after leaf
    // First pair is value when considering current
    // Second pair is when we are not including it
    if (!root) return make_pair(0, 0);

    // Postorder traversal to acquire values of left & right
    pair<int, int> left = getLargestDisjointSum(root->left);
    pair<int, int> right = getLargestDisjointSum(root->right);

    // When we include current, we cannot select left
    // or right child, we must select nodes after them, 
    // so we access second element of the pair
    int includingCurrent = root->data + left.second + right.second;
    // If we are not including current, we simply select
    // whatever is max including / excluding the left & right nodes
    int excludingCurrent = max(left.first, left.second) + max(right.first, right.second);

    return make_pair(includingCurrent, excludingCurrent); 
}