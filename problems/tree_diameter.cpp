#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node() = default;
        Node(int d) : data(d), left(NULL), right(NULL) {}
        ~Node() {
            delete left;
            delete right;
            left = right = NULL;
        }
};

Node* buildTree();
pair<int, int> getMaxDiameter(Node *);

int main() {
    /**
     * The maximum diameter possible in a tree can be subdivided into 3 
     * recursive situations, sum of heights of both of its subtree, diameter
     * of the left or diameter of the right, the max of either remains
     */
    cout << "\nThis program demonstrates the maximum possible diameter of a tree\n" << endl;
    
    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    pair<int, int> value = getMaxDiameter(root);

    cout << "\nThe max distance is : " << value.second << endl;

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

pair<int, int> getMaxDiameter(Node *root) {
    // We have reached a leaf node marking end
    if (root == NULL) return make_pair(0, 0);

    // Recursively check values of subtree
    pair<int, int> left = getMaxDiameter(root->left);
    pair<int, int> right = getMaxDiameter(root->right);

    pair<int, int> curr;

    // First denotes their respective heights from both sides
    curr.first = max(left.first, right.first) + 1;
    // Second denotes their respective diameter from both sides
    curr.second = max(left.first + right.first, max(left.second, right.second));

    return curr;
}