#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int val = 0, Node *lchild = NULL, Node *rchild = NULL) : data(val), left(lchild), right(rchild) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildTree();
int traverseAndOrder(Node *, int &, int &, int &, bool &);
int largestBST(Node *);

int main() {
    /**
     * In order to find out length of largest BST inside a Binary Tree,
     * a left subtree need to tell the parent whether it is BST or 
     * not and also need to pass maximum value in it. So that we 
     * can compare the maximum value with the parent’s data to check 
     * the BST property. Similarly, the right subtree need to pass 
     * the minimum value up the tree. This is done recursively 
     */ 
    cout << "\nThis program finds out length of the largest BST exising inside a Binary Tree.\n" << endl;

    cout << "Enter space seperated elements of the tree," << endl;
    Node *root = buildTree();

    int size = largestBST(root);

    cout << "\nThe size of the largest possible BST inside this tree is: " << size << "." << endl;

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

int traverseAndOrder(Node *root, int &mn, int &mx, int &maxSize, bool &isBST) {
    // Base Case (empty tree is BST & size is 0)
    if (!root) { 
        isBST = true;
        return 0;
    }
      
    // A flag variable for left subtree property 
    // i.e., max_from(root->left) < root->data
    bool leftFlag = false; 
    // A flag variable for right subtree property 
    // i.e., min_from(root->right) > root->data
    bool rightFlag = false; 
      
      
    // Following tasks are done by recursive call for left subtree 
    // a) Get the maximum value in left subtree (Stored in `mx`) 
    // b) Check whether Left Subtree is BST or not (Stored in `isBST`) 
    // c) Get the size of maximum size BST in left subtree (updates `maxSize`)
    mx = INT_MIN; 
    // To store size of left sutree
    int ls = traverseAndOrder(root->left, mn, mx, maxSize, isBST);
                        
    if (isBST && root->data > mx) leftFlag = true; 
      
    // Before updating mn, store the min
    // value in left subtree. So that we have the
    // correct minimum value for this subtree
    int lastMin = mn; 
      
    // The following recursive call does similar
    // task for right subtree
    mn = INT_MAX; 
    // To store size of right subtree
    int rs = traverseAndOrder(root->right, mn, mx, maxSize, isBST);
                        
    if (isBST && root->data < mn) rightFlag = true; 
      
    // Update min and max values for 
    // the parent recursive calls 
    if (lastMin < mn) mn = lastMin; 
    
    // For leaf nodes 
    if (root->data < mn) mn = root->data; 
    if (root->data > mx) mx = root->data; 
      
    // If both left and right subtrees are BST. 
    // And left and right subtree properties hold
    // for this node, then this tree is BST. 
    // So return the size of this tree
    if(leftFlag && rightFlag) { 
        if (ls + rs + 1 > maxSize) maxSize = ls + rs + 1; 
        return ls + rs + 1; 
    } else { 
        // Since this subtree is not BST, 
        // set is_bst flag for parent calls 
        isBST = false; 
        return 0; 
    } 
}

int largestBST(Node *root) {
    // Referential minima & maxima
	int mn = INT_MAX;
	int mx = INT_MIN;
	
    // Referential maxSize of BST & wether 
    // a node is member of BST
	int maxSize = 0;
	bool isBST = false;
	
	traverseAndOrder(root, mn, mx, maxSize, isBST);
	
	return maxSize;
}
