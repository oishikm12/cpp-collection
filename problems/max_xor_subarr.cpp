#include <iostream>
#include <vector>
using namespace std;

#define INT_SIZE 32

class Trie;

class Node {
    // Represents each node of the Trie
    private:
        // We will usre the value only in leaf nodes
        int val;
        Node *left, *right;

    public:
        Node(int v = 0) : val(v), left(NULL), right(NULL) {};
        ~Node() { delete left, delete right; }
        friend class Trie;
};

class Trie {
    private:
        Node *root;

    public:
        Trie() { root = new Node(); }
        ~Trie() { delete root->left, delete root->right; }
        void insert(int);
        int xorQuery(int);
};

void Trie :: insert(int val) {
    // We use a pointer for tree traversal
    Node* temp = root;

    // Then we start from the MSB of the value to insert and
    // push all its bit into the trie
    for (int i = INT_SIZE - 1; i >= 0; i -= 1) {
        // Finding the current bit requires & with 1 at that pos
        int bit = val & (1 << i);

        if (bit == 1) {
            // A set Bit goes to the right
            if (!temp->right) temp->right = new Node();
            // If the node was already there, or we created it, this bit has
            // now been inserted and we move to right
            temp = temp->right;
        } else {
            // An unset Bit goes to the left
            if (!temp->left) temp->left = new Node();
            // If the node was already there, or we created it, this bit has
            // now been inserted and we move to left
            temp = temp->left;
        }
    }

    // The pointer is now at the leaf node, and to indicate, it is a leaf node
    // we store the value whose bit representation we inserted, here
    temp->val = val;
}

int Trie :: xorQuery(int val) {
    // Finds out such a number from the trie, such that the resulting number
    // when XORed with the val, will result in the maximum number. This is done
    // by moving to the bit opposite to current one, such that when XORed, itll 
    // result in the bit being set
    Node* temp = root;

    // Then we start from the MSB of the value all the way to LSB
    for (int i = INT_SIZE - 1; i >= 0; i -= 1) {
        // Finding the current bit requires & with 1 at that pos
        int bit = val & (1 << i);

        if (bit == 1) {
            // The current bit is set, for max XOR pair, we need to find the
            // value which has current bit unset
            if (temp->left) temp = temp->left;
            // If such a bit does not exist then we go the same route
            else temp = temp->right;
        } else {
            // The current bit is unset, for max XOR pair, we need to find the
            // value which has current bit set
            if (temp->right) temp = temp->right;
            // If such a bit does not exist then we go the same route
            else temp = temp->left;
        }
    }

    // Since the temp pointer is now at leaf, the original value is stored here
    // This when XORed with provided val, will result in maximum
    return temp->val;
}

int maximumXORSubArr(vector<int> &);

int main() {
    /**
     * In order to find out the maximum XOR subarray in the array
     * we use a Trie to store the prefix XOR of every element in 
     * the array. This way for any given index in the prefixArray,
     * we only need to find a suitable max XOR pair from the
     * elements before it, and store the maximal of them all
     */
    cout << "\nThis program finds out the maximum XOR subarray possible\n" << endl; 
    int n;
    cout << "Enter the size of the array to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements to consider," << endl;
    for (auto &x : arr) cin >> x;

    int mxXOR = maximumXORSubArr(arr);

    cout << "\nThe maximum XOR subarray yields a result of " << mxXOR << "." << endl;

    cout << endl;

    return 0;
} 

int maximumXORSubArr(vector<int> &arr) {
    // In order to find maximum subarray XOR, we use a Trie structure
    // such that XOR queries can be done in O(log(max))
    Trie xorTrie;

    // To store the maxium XOR found till now
    int result = INT_MIN;
    // To keep track of current XOR
    int prefixXOR = 0;

    // Instead of finding XOR values for all possible subarrays, we find
    // the XOR Prefix array for the given array, this way, we only need to
    // find the maximum XOR subarray between 0 & i where i traverses linearly
    for (auto &x : arr) {
        // Update the current prefix XOR & insert into Trie
        prefixXOR = prefixXOR ^ x;
        xorTrie.insert(prefixXOR);

        // Then we simply query the maximum XOR subarray so far
        result = max(result, xorTrie.xorQuery(prefixXOR) ^ prefixXOR);
    }

    return result;
}