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
bool isIsomorphic(Node *, Node *);

int main() {
    /**
     * Since in isomorphic trees, either the left matches
     * with right or matches with left of the other tree, we
     * only have to check this condition recursively for all nodes
     */
    cout << "\nThis program finds out if two trees are isomorphic to each other.\n" << endl; 

    Node *root1;
    cout << "Enter space seperated elements of the first tree :" << endl;
    root1 = buildTree();

    Node *root2;
    cout << "Enter space seperated elements of the second tree :" << endl;
    root2 = buildTree();

    bool isIso = isIsomorphic(root1, root2);

    if (isIso) cout << "\nThe trees are isomorphic." << endl;
    else cout << "\nThe trees are not isomorphic." << endl;

    cout << endl;
    delete root1;
    delete root2;

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

bool isIsomorphic(Node *root1,Node *root2) {
    // Both roots are NULL, trees isomorphic by definition
    if (!root1 && !root2) return true;
    
    // Exactly one of the n1 and n2 is NULL, trees not isomorphic
    if (!root1 || !root2) return false;
    
    if (root1->data != root2->data) return false;
    
    // There are two possible cases for the trees to be isomorphic
    // Case 1: The subtrees rooted at these nodes have NOT been "Flipped".
    // Both of these subtrees have to be isomorphic, hence the &&
    // Case 2: The subtrees rooted at these nodes have been "Flipped"
    bool sameIso = isIsomorphic(root1->left, root2->left) && isIsomorphic(root1->right, root2->right);
    bool alterIso = isIsomorphic(root1->left, root2->right) && isIsomorphic(root1->right, root2->left);
    
    return sameIso || alterIso;
}