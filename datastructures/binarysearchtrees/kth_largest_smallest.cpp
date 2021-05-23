#include <iostream>
#include <stack>
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
Node* getKthLargest(Node *, int);
Node* getKthSmallest(Node *, int);

int main() {
    /**
     * In order to find the kth largest and kth smallest
     * element in a binary search tree, we have to traverse
     * the tree in inorder fashion, & reverse inorder fashion
     * each time keeping the count of nodes traversed
     */ 
    cout << "\nThis program finds out a certain largest & smallest value in a Binary Search Tree.\n" << endl;
    
    cout << "Enter space seperated elements of the BST," << endl;
    Node *root = buildBST();

    int ksm, klg;
    cout << "\nEnter the value of k, i.e smallest number to find: ";
    cin >> ksm;
    cout << "\nEnter the value of k, i.e. largest number to find: ";
    cin >> klg;

    Node *smallest = getKthSmallest(root, ksm);
    Node *largest = getKthLargest(root, klg);

    cout << "\nThe " << ksm << "-th smallest node is " << smallest->data << ", " << klg << "-th largest node is " << largest->data << "." << endl;

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

Node* getKthSmallest(Node *root, int k) {
    if (!root) return NULL;

    // We will use a stack to keep track of visited
    // nodes in order to inorder traverse
    Node *temp = root;
    stack<Node*> s;

    int cnt = 1;

    while (!s.empty() || temp) {
        while (temp) {
            // We move to the leftmost first 
            // in case of forward inorder traversal
            s.push(temp);
            temp = temp->left;
        }

        temp = s.top();
        s.pop();

        // We check the count & increment if needed
        if (cnt == k) return temp;

        cnt += 1;

        // Move right of current in next step
        temp = temp->right;
    }

    return NULL;
}

Node* getKthLargest(Node *root, int k) {
    if (!root) return NULL;

    // We will use a stack to keep track of visited
    // nodes in order to inorder traverse
    Node *temp = root;
    stack<Node*> s;

    int cnt = 1;

    while (!s.empty() || temp) {
        while (temp) {
            // We move to the rightmost first 
            // in case of reverse inorder traversal
            s.push(temp);
            temp = temp->right;
        }

        temp = s.top();
        s.pop();

        // We check the count & increment if needed
        if (cnt == k) return temp;

        cnt += 1;

        // Move left of current in next step
        temp = temp->left;
    }

    return NULL;
}