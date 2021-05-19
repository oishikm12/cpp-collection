#include <iostream>
#include <queue>
#include <vector>
#include <map>
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
void print(Node *);
Node *treeToDLL(Node *);
Node *convSubtree(Node *);

int main() {
    /**
     * In order to inplace convert this binary tree into
     * doubly linked list we will simply be using a recursive approach 
     * where we will be passing the parent node to convert the link
     */
    cout << "\nThis program converts a binary tree to a doubly linked list.\n" << endl;
    
    Node *root;
    cout << "Enter space seperated elements of the tree :" << endl;
    root = buildTree();

    cout << "\nThe tree after converting to a DLL is," << endl;
    root = treeToDLL(root);
    print(root);

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

void print(Node *head) {
    while (head != NULL) {
        cout << head->data;
        // This will print a seperator for each element of the list
        if (head->right != NULL) cout << " <> ";
        head = head->right;
    }
    cout << endl;
}

Node *treeToDLL(Node *root) {
    if (!root) return root;

    // We call this function to recursively convert
    // left & right subtrees to DLL
    root = convSubtree(root);

    // We are still at root, we need to point to
    // first element in the list
    while (root->left) root = root->left;

    return root;
}

Node *convSubtree(Node *root) {
    // Base case
    if (!root) return root;
 
    // Convert the left subtree and link to root
    if (root->left) {
        // Convert the left subtree
        Node* left = convSubtree(root->left);
 
        // Find inorder predecessor. After this loop, left
        // will point to the inorder predecessor
        while (left->right) left = left->right;
 
        // Make root as next of the predecessor
        left->right = root;
        // Make predecssor as previous of root
        root->left = left;
    }
 
    // Convert the right subtree and link to root
    if (root->right != NULL) {
        // Convert the right subtree
        Node* right = convSubtree(root->right);
 
        // Find inorder successor. After this loop, right
        // will point to the inorder successor
        while (right->left) right = right->left;
 
        // Make root as previous of successor
        right->left = root;
        // Make successor as next of root
        root->right = right;
    }
 
    return root;
}