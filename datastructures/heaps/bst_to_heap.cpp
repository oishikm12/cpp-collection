#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int val = 0, Node *lc = NULL, Node *rc = NULL) : data(val), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* buildBST();
Node* insertInBST(Node*, int);
void levelPrint(Node *);
void inorderTraversal(Node *, vector<int> &);
void BSTToMinHeap(Node *, vector<int> &, int &);
void minHeapify(Node *);

int main() {
    /**
     * In order to convert the given BST into a MinHeap, we will first
     * use inorder traversal on the tree, to acquire a sorted representation
     * of the data, then we will insert the elements into the Min Heap in
     * an inorder fashion ensuring that the left subtree is smaller than 
     * the right subtree all the while maintaining heap property
     */ 
    cout << "\nThis program converts a given Binary Search Tree into a Min Heap.\n" << endl;
    
    cout << "Enter space seperated elements of the Binary Search Tree," << endl;
    Node *root = buildBST();

    cout << "\nThe binary search tree is," << endl;
    levelPrint(root);

    minHeapify(root);

    cout << "\nThe tree converted to a min heap is," << endl;
    levelPrint(root);

    cout << endl;

    return 0;
}

Node* buildBST() {
    // Value of the root node
    int data;
    cin >> data;

    Node *curr = NULL;

    while (data != -1) {
        // We will continue to take user input
        // till user enters -1
        curr = insertInBST(curr, data);
        cin >> data;
    }

    return curr;
}

Node* insertInBST(Node *curr, int data) {
    // If we reach null this becomes desired node
    // to place the value in
    if (!curr) return new Node(data);

    // If data is smaller, it goes into left child
    // else it goes into right child
    if (data <= curr->data) curr->left = insertInBST(curr->left, data);
    else curr->right = insertInBST(curr->right, data);

    return curr;
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

void inorderTraversal(Node *root, vector<int>& arr) {
    if (root == NULL) return;
 
    // First recur on left subtree
    inorderTraversal(root->left, arr);
    // Then copy the data of the node
    arr.push_back(root->data);
    // Now recur for right subtree
    inorderTraversal(root->right, arr);
}

void BSTToMinHeap(Node *root, vector<int> &arr, int &i) {
    if (root == NULL) return;
 
    // First copy data at index 'i' of 'arr' to the node
    root->data = arr[++i];
 
    // then recur on left subtree
    BSTToMinHeap(root->left, arr, i);
    // now recur on right subtree
    BSTToMinHeap(root->right, arr, i);
}
 
void minHeapify(Node *root) {
    // Vector to store the data of all the nodes of the BST
    vector<int> arr;
    int i = -1;
 
    // inorder traversal to populate 'arr'
    inorderTraversal(root, arr);
    // BST to MIN HEAP conversion
    BSTToMinHeap(root, arr, i);
}