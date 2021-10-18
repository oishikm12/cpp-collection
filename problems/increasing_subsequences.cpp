#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class FenwickTree {
    private:
        vector<vector<int>> tree;

    public:
        // Initializes the binary indexed tree
        FenwickTree(int, int);

        // Adds an element at a specific index
        void addElement(int, int, int);

        // Performs query on range
        int query(int, int);
};

FenwickTree :: FenwickTree(int k, int n) {
    // Since we represent sequential series of elements,
    // there is no need to allocate more space than needed
    // Here k represents, size of subsequence & n the elements
    tree.resize(k + 1, vector<int>(n + 1, 0));
}

void FenwickTree :: addElement(int querySize, int idx, int value) {
    // Unlike Segment Tree, elements are simply
    // inserted one by one. Since in a binary Indexed Tree
    // next element is present in next binary position,
    // we propagate the changes by setting next bit
    for (int i = idx; i < tree.size(); i += i & (-i)) {
        tree[querySize][i] += value;
    }
}

int FenwickTree :: query(int querySize, int idx) {
    // We return the elements all the way from 1st index
    // Propagation is done in the same way, by incrementing
    // the next bit (adding i & (-i))
    int sum = 0;

    for (int i = idx; i > 0; i -= i & (-i)) {
        sum += tree[querySize][i];
    }

    return sum;
}

void compressValues(vector<int> &);

int main() {
    /**
     * In order to find out all increasing subsequence we
     * maintain a 2D binary indexed tree, tracking increasing
     * subsequence count of certain size. We sort the input 
     * and replace them with their respective indices beforehand
     */
    cout << "\nThis program finds out number of increasing subsequences of specified length in a list of numbers.\n" << endl; 
    int n;
    cout << "Enter number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (auto &x : elems) cin >> x;

    int k;
    cout << "Enter the length of subsequences to find: ";
    cin >> k;

    FenwickTree bit(k, n);

    compressValues(elems);

    // To count the number of increasing subsequences
    int total = 0;

    for (int i = 1; i <= n; i += 1) {
        // i represents index of element, j for length
        for (int j = 1; j <= k; j += 1) {
            // x represents the number of increasing subsequences that are
            // smaller in size than current value of j
            int x;
            if (j == 1) x = 1;
            else x = bit.query(j - 1, elems[i - 1] - 1);

            // Adding the current element to tree, so that it propagates
            // for all sunsequences of current query size
            bit.addElement(j, elems[i - 1], x);

            // If this is indeed the required size, we add all possible 
            // subsequences of current size
            if (j == k) total += x;
        }
    }

    cout << "\nThere are " << total << " increasing subsequences, " << k << " units long" << endl;

    cout << endl;

    return 0;
}

void compressValues(vector<int> &elems) {
    // Since we do not actually need the elements, rather
    // only their sorted order, we replace the elemnts with
    // smaller indices to reduce indexing time in bit, 
    // eg: 11, 43, 31, 32, 51, 21 => 1, 5, 3, 4, 6, 2
    set<int> values;

    // Inserting into set, removes duplicates & also sorts them
    for (auto &x : elems) values.insert(x);

    // By calculating the distance between first & current element
    // we find their index in sorted ordering
    // [NOTE: Adding 1 sinces indices start from 0]
    for (auto &x : elems) x = distance(values.begin(), values.find(x)) + 1;
}