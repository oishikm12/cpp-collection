#include <iostream>
#include <vector>
using namespace std;

class Node {
    public:
        int low, high, mx;
        Node *left, *right;

        Node(int l = 0, int h = 0, Node *lc = NULL, Node *rc = NULL) : low(l), high(h), mx(h), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* insertInBST(Node *, int, int); 
Node* overlapSearch(Node *, pair<int, int>); 
void printConflicting(vector<pair<int, int>> &);

int main() {
    /**
     * In order to find all the appointments that are
     * overlapping, we will construct an interval tree,
     * in the form of a Binary Search Tree, on the basis
     * of arrival times
     */ 
    cout << "\nThis program takes in the arrival & departure times of appointments, and lists out the overlaps.\n" << endl;
    int n;
    cout << "Enter the number of appointments to consider: ";
    cin >> n;

    vector<pair<int, int>> appt(n);
    cout << "Enter space seperated, line delimited arrival & departure times of clients," << endl;
    for (int i = 0; i < n; i += 1) cin >> appt[i].first >> appt[i].second;

    printConflicting(appt);

    cout << endl;

    return 0;
}

Node* insertInBST(Node *root, int low, int high) {
    // Base case: Tree is empty, new node becomes root
    if (!root) return new Node(low, high);

    // Here the low value, not the others
    // of interval is used tomaintain BST property
    // If current nodes's low value is smaller, then left or right
    if (low < root->low) root->left = insertInBST(root->left, low, high);
    else root->right = insertInBST(root->right, low, high);

    // Update the max value of this ancestor if needed
    if (root->mx < high) root->mx = high;

    return root;
}

Node* overlapSearch(Node *root, pair<int, int> i) {
    // Base Case, tree is empty
    if (root == NULL) return NULL;
 
    // If given interval overlaps with root
    if (root->low < i.second && root->high > i.first) return root;
 
    // If left child of root is present and max of left child
    // is greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != NULL && root->left->mx >= i.first) {
        return overlapSearch(root->left, i);
    }
 
    // Else interval can only overlap with right subtree
    return overlapSearch(root->right, i);
}

void printConflicting(vector<pair<int, int>> &appt) {
    // Creating root of Interval Search Tree
    Node *root = NULL;
    cout << endl;

    // Process rest of the intervals
    for (int i = 0; i < appt.size(); i += 1) {
        // If current appointment conflicts with any of the
        // existing intervals, print it
        Node *res = overlapSearch(root, appt[i]);

        if (res) {
            cout << "[" << appt[i].first << "," << appt[i].second << "] Conflicts with [" << res->low << "," << res->high << "]" << endl;
        }    

        // Insert this appointment
        root = insertInBST(root, appt[i].first, appt[i].second);
    }

    delete root;
}