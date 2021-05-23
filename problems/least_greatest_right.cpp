#include <iostream>
#include <vector>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node(int d = 0, Node *lc = NULL, Node *rc = NULL) : data(d), left(lc), right(rc) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* insertInBST(Node *, int, Node *&);
void createAndReplace(vector<int> &);

int main() {
    /**
     * In order to replace every element with its least
     * greatest to its right, we will construct a BST starting
     * with elements to the end, that way, the inorder 
     * successor to the recently inserted element will
     * be its least greatest to the right
     */ 
    cout << "\nThis program replaces every element in the array with its least greatest to the right.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the array, " << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    createAndReplace(elems);

    cout << "\nAfter replacing every element with its least greatest element to its right," << endl;
    for (auto &x : elems) cout << x << " ";

    cout << endl;

    return 0;
}

Node* insertInBST(Node* curr, int data, Node *&succ) {
    // Base case when we have reached desired position
    if (curr == NULL) return new Node(data);

    // Recursive case to place data in desired position
    if (data <= curr->data) {
        // For an element to the left, its parent
        // is its inorder successor, and immidiately greater
        succ = curr;
        curr->left = insertInBST(curr->left, data, succ);
    } else curr->right = insertInBST(curr->right, data, succ);

    return curr;
}

void createAndReplace(vector<int> &elems) {
    // Root to a binary search tree
    Node *root = NULL;

    for (int i = elems.size() - 1; i >= 0; i -= 1) {
        Node *succ = NULL;

        // We insert the elements in reverse order
        // this way only elements to right are considered
        root = insertInBST(root, elems[i], succ);

        if (succ) elems[i] = succ->data;
        else elems[i] = -1;
    }

    delete root;
}