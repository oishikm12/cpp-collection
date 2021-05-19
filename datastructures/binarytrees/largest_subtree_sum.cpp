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
pair<int, int> getLargestSum(Node *);

int main() {
    /**
     * In order to find the largest subtree sum, we will
     * recursively return both the sum as well as the best
     * subtree sum a t each given stage. While cumulative
     * sum will always change, best sum will carry the largest
     */
    cout << "\nThis program finds out the largest subtree sum in the given tree.\n" << endl; 

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    int maxSum = getLargestSum(root).second;

    cout << "\nThe largest sum of subtree possible here is: " << maxSum << "." << endl;

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

pair<int, int> getLargestSum(Node *root) {
    // Base condition to handle NULL
    if (!root) return make_pair(0, 0);

    // Postorder traversal to store [sum, besSum] for each child
    pair<int, int> left = getLargestSum(root->left);
    pair<int, int> right = getLargestSum(root->right);

    int currSum = root->data + left.first + right.first;

    // We return {cumulativeSum, highest value} at each step
    return make_pair(currSum, max(currSum, max(left.second, right.second)));
}