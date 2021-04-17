#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node() = default;
        Node(int d) : data(d), left(NULL), right(NULL) {}
        ~Node() {
            delete left;
            delete right;
            left = right = NULL;
        }
};

Node* buildBalanceTree(vector<int> &, int, int);
Node* createFromTrav(vector<int> &, vector<int> &, int&, int, int);
void printTree(Node *);

int main() {
    /**
     * In order to reconstruct a binary tree from an array there are two
     * possible ordering
     * > Inorder only - In this case the tree turns out to be a balanced tree
     *      with the center element being root
     * > Preorder + Inorder - In this case every node is compared with its 
     *      preorder counterpart to reconstruct tree 
     */ 
    cout << "\nThis program demonstrates tree reconstruction from an array.\n" << endl;

    int size, choice;
    cout << "Enter no. of elements to consider : ";
    cin >> size;

    Node *root;
    vector<int> inorder(size), preorder(size);
    int pos;
    bool loop = true;

    while(loop) {
        cout << "\nEnter:\n1. Reconstruct via Inorder\n2. Reconstruct via Inorder + Preorder\n3. Exit" << endl;
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\nEnter space seperated inorder elements of tree." << endl;
                for (int i = 0; i < size; i += 1) cin >> inorder[i];

                root = buildBalanceTree(inorder, 0, size - 1);
                cout << "\nThe tree is : " << endl;
                printTree(root);

                break;
            case 2: 
                cout << "\nEnter space seperated inorder elements of tree." << endl;
                for (int i = 0; i < size; i += 1) cin >> inorder[i];
                cout << "Enter space seperated preorder elements of tree." << endl;
                for (int i = 0; i < size; i += 1) cin >> preorder[i];

                pos = 0;
                root = createFromTrav(preorder, inorder, pos, 0, size - 1);
                cout << "\nThe tree is : " << endl;
                printTree(root);

                break;
            default:
                cout << "\nGoodbye ..." << endl;
                loop = false;
                break;
        }
    }

    cout << endl;

    return 0;
}

Node* buildBalanceTree(vector<int> &in, int start, int end) {
    // Base condition when we reach a leaf
    if (start > end) return NULL;

    // Since the tree itself is balanced in nature we simply
    // calculate the mid and call recursively for equal child distribution
    int mid = (end - start) / 2 + start;

    Node *root = new Node(in[mid]);
    root->left = buildBalanceTree(in, start, mid - 1);
    root->right = buildBalanceTree(in, mid + 1, end);

    return root;
}

Node* createFromTrav(vector<int> &pre, vector<int> &in, int &pos, int start, int end) {
    // Base condition to hit when we reach a leaf
    if (start > end || pos == in.size()) return NULL;

    // Place the current value in a new node
    Node *root = new Node(pre[pos]);

    int idx = 1;
    // We need to find the index of inorder which matches with the 
    // corresponding preorder value we have stored in root, as such 
    // we will call recursively from that position
    for (int j = start; j <= end; j += 1) {
        if (in[j] == pre[pos]) {
            idx = j;
            break;
        }
    }

    // Increment to place next preorder element
    pos += 1;
    root->left = createFromTrav(pre, in, pos, start, idx - 1);
    root->right = createFromTrav(pre, in, pos, idx + 1, end);

    return root;
}

void printTree(Node *root) {
    // We use queue to print level wise
    queue<Node*> container;

    Node *temp = root;
    container.push(temp);
    // By inserting an extra NULL we can identify when a level changes
    container.push(NULL);

    while (!container.empty()) {
        temp = container.front();
        container.pop();

        if (temp == NULL) {
            cout << endl;
            // There are more levels below, so we use another seperator
            if (!container.empty()) container.push(NULL);
        } else {
            cout << temp->data << " ";
            // We check if it has children and accordingly print
            if (temp->left != NULL) container.push(temp->left);
            if (temp->right != NULL) container.push(temp->right);
        }
    }
}