#include <iostream>
#include <vector>
#include <deque>
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
int heightBalance(Node *);
bool isBalanced(Node *);

int main() {
    /**
     * In order to find out wether a tree is balanced we
     * will recursively find out the heiht of either children
     * and if they have a diff greater than 1 we will return
     * an arbituray value up the call stack else the max height + 1
     */ 
    cout << "\nThis program finds out if the tree is balanced or not.\n" << endl;

    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    bool bal = isBalanced(root);

    if (bal) cout << "\nThe tree is balanced." << endl;
    else cout << "\nThe tree is not balanced." << endl;

    cout << endl;

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

bool isBalanced(Node *root) {
    // If the function never returned -1, then it is balanced
    return heightBalance(root) != -1;
}

int heightBalance(Node *root) {
    // Base condition to start height calculation
    if (!root) return 0;
    
    int lHt = heightBalance(root->left);
    int rHt = heightBalance(root->right);
    
    // If any of the subtrees are not balacned or if
    // the current diff is greater than 1 then we return
    // -1 up the recursion stack to calling function
    if (lHt == -1 || rHt == -1 || abs(lHt - rHt) > 1) return -1;
    
    return 1 + max(lHt, rHt);
}
