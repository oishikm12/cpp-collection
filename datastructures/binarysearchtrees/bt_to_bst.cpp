#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int val = 0, Node *lc = NULL, Node *rc = NULL) : data(val), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildTree(vector<int> &);
Node* binaryTreeToBST (Node *);
void getInorder(Node *, list<int> &);
void putInorder(Node *, list<int> &);
void levelPrint(Node *);

int main() {
    /**
     * Since we have to preserve the structure of the
     * tree, we simply traverse the binary tree in inorder
     * fashion and then sort it, and finally replace the
     * elements in inorder fashion (BST - Inorder is sorted)
     */ 
    cout << "\nThis program converts a binary tree into a binary search tree.\n" << endl;

    cout << "Enter space seperate elements of the binary tree," << endl;
    Node *root = buildTree();

    cout << "\nThe tree thus formed is," << endl;
    levelPrint(root);

    cout << endl;

    root = binaryTreeToBST(root);
    cout << "\nThe tree converted to binary search tree is,";
    levelPrint(root);

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

Node *binaryTreeToBST (Node *root) {
    // We will place the nodes in this list
    list<int> vals;

    // Inorder travrse and place the element in the list
    getInorder(root, vals);
    // Sort the list, since inorder of BST is sorted
    vals.sort();
    // Re insert the elements in the tree
    putInorder(root, vals);

    return root;
}
    
void getInorder(Node *root, list<int> &vals) {
    if (!root) return;
    
    getInorder(root->left, vals);
    
    // While traversing elements place them in list
    vals.push_back(root->data);
    
    getInorder(root->right, vals);
}

void putInorder(Node *root, list<int> &vals) {
    if (!root) return;
    
    putInorder(root->left, vals);
    
    // After placing the items, remove them from the list
    root->data = vals.front();
    vals.pop_front();
    
    putInorder(root->right, vals);
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