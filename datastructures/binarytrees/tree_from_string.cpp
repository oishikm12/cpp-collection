#include <iostream>
#include <queue>
using namespace std;

class Node {
    public:
        int data;
        Node *left, *right;

        Node() = default;
        Node(int d) : data(d), left(NULL), right(NULL) {}
        ~Node() { delete left, delete right, left = right = NULL; }
};

Node* createFromString(string &, int &);
void printTree(Node *);

int main() {
    /**
     * In order to construct a tree from a string, we will
     * be using a recursive approach to build subtrees whenever
     * we encounter a opening bracket and recurse back whenever
     * we encounter a closing bracket
     */ 
    cout << "\nThis program builds a tree from paranthesis string representation.\n" << endl;
    string s;
    cout << "Enter string representation of tree: ";
    cin >> s;

    int startIdx = 0;
    Node *root = createFromString(s, startIdx);

    cout << "\nThe tree turns out to be," << endl;
    printTree(root);

    cout << endl;

    return 0;
}

Node* createFromString(string &s, int &pos) {
    // Base condition, we have traversed entire string
    if (pos >= s.size()) return NULL;

    // Collecting the entire node number
    string num = "";
    while (pos < s.size() && s[pos] != '(' && s[pos] != ')') num += s[pos++];

    // stoi : string to integer
    Node *curr = new Node(stoi(num));

    if (pos < s.size() && s[pos] == '(') {
        // Represents the left subtree of a node
        pos += 1;
        curr->left = createFromString(s, pos);
        // Represents ')' of the current node
        pos += 1;
        if (pos < s.size() && s[pos] == '(') {
            // Represents the right subtree of a node
            pos += 1;
            curr->right = createFromString(s, pos);
            // Represents ')' of the current node
            pos += 1;
        }
    }

    return curr;
}

void printTree(Node *root) {
    // We use queue to print level wise
    queue<Node*> container;

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
