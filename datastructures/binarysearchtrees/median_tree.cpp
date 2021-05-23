#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int d = 0, Node *lc = NULL, Node *rc = NULL) : data(d), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildBST();
Node* insertInBST(Node *, int);
int getCount(Node *);
int getMedian(Node *);

int main() {
    /**
     * In order to find the median node in linear time and
     * no auxillary space, we will find out the count of
     * nodes and use it in Morris Inorder traversal.
     */ 
    cout << "\nThis program finds out the median node in a Binary Search Tree.\n" << endl;
    
    cout << "Enter space seperated elements of the BST," << endl;
    Node *root = buildBST();

    int median = getMedian(root);

    cout << "\nThe median of this tree is: " << median << "." << endl;

    cout << endl;
    delete root;

    return 0;
}

Node* buildBST() {
    // First take the data from user
    int data;
    cin >> data;

    // We initialize a pointer to to store data in
    Node *curr = NULL;

    // While user does not enter -1, we continue to push data into tree
    while (data != -1) {
        curr = insertInBST(curr, data);
        cin >> data;
    }

    return curr;
}

Node* insertInBST(Node* curr, int data) {
    // Base case when we have reached desired position
    if (curr == NULL) return new Node(data);

    // Recursive case to place data in desired position
    if (data <= curr->data) curr->left = insertInBST(curr->left, data);
    else curr->right = insertInBST(curr->right, data);

    return curr;
}

int getCount(Node *root) {
    // Base case when we hit post leaf
    if (!root) return 0;
    // Current node counts as 1, added to sum of left & right nodes
    return 1 + getCount(root->left) + getCount(root->right);
}

int getMedian(Node *root) {
    // Morris Traversal works on the idea of threaded BST,
    // wherein for every left node, we traverse its right 
    // subtree, i.e. we find a nodes inorder successor and
    // connect it to current and undo it later, this way
    // we can traverse the entire tree without stack
    if (root == NULL) return 0;
  
    // Median node is center most node in sorted array
    // hence we need to count the no. of nodes
    int count = getCount(root);
    int currCount = 0;

    Node *current = root; 
    Node *pre, *prev;
  
    while (current) {
        if (!current->left) {
            // Count current node
            currCount += 1;
  
            // Check if current node is the median
            // Odd case & Even Case
            if (count % 2 != 0 && currCount == (count + 1) / 2) return prev->data;
            else if (count % 2 == 0 && currCount == (count / 2) + 1) return (prev->data + current->data) / 2;
  
            // Update prev for even no. of nodes
            prev = current;
            // Move to the right
            current = current->right;
        } else {
            // Finding the inorder predecessor of current
            pre = current->left;
            while (pre->right && pre->right != current) pre = pre->right;
  
            // Make current as right child of its inorder predecessor
            if (!pre->right) {
                pre->right = current;
                current = current->left;
            } else {
                // Revert the changes made in if part to restore the
                // original tree i.e., fix the right child of predecssor
                pre->right = NULL;
                prev = pre;
  
                // Count current node
                currCount += 1;
  
                // Check if the current node is the median
                if (count % 2 != 0 && currCount == (count + 1) / 2) return current->data;
                else if (count % 2 == 0 && currCount == (count / 2) + 1) return (prev->data + current->data) / 2;
  
                // Update prev node for the case of even no. of nodes
                prev = current;
                current = current->right;
            }
        }
    }
}
