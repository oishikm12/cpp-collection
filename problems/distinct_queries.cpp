#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Node {
    // DataStructure to hold combined data
    public: 
        int start, end;
        int index;

        Node(int s = 0, int e = 0, int i = -1) : start(s), end(s), index(i) {};
};

class FenwickTree {
    private:
        vector<int> tree;

    public:
        // Initializes the binary indexed tree
        FenwickTree(int);

        // Adds an element at a specific index
        void addElement(int, int);

        // Performs query on range
        int query(int);
};

FenwickTree :: FenwickTree(int n) {
    // Since we represent sequential series of elements,
    // there is no need to allocate more space than needed
    tree.resize(n + 1, 0);
}

void FenwickTree :: addElement(int idx, int value) {
    // Unlike Segment Tree, elements are simply
    // inserted one by one. Since in a binary Indexed Tree
    // next element is present in next binary position,
    // we propagate the changes by setting next bit
    for (int i = idx; i < tree.size(); i += i & (-i)) {
        tree[i] += value;
    }
}

int FenwickTree :: query(int idx) {
    // We return the elements all the way from 1st index
    // Propagation is done in the same way, by incrementing
    // the next bit (adding i & (-i))
    int sum = 0;

    for (int i = idx; i > 0; i -= i & (-i)) {
        sum += tree[i];
    }

    return sum;
}

int main() {
    /**
     * In order to find out distinc queries in a range,
     * we lazily evaluate a binary indexed tree. First we sort
     * the queries in increasing order of ending range. That
     * way, we only have to add current to the list and check
     * for distincts in a given range
     */ 
    cout << "\nThis program finds out distinct elements in multiple ranges.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements to consider," << endl;
    for (auto &x : elems) cin >> x;

    int q;
    cout << "Enter number of queries to perform: ";
    cin >> q;
    
    vector<Node> queries(q);
    cout << "Enter space seperated starting & ending range of each query, delimited by space," << endl;
    for (int i = 0; i < q; i += 1) {
        cin >> queries[i].start >> queries[i].end;
        queries[i].index = i;
    }

    vector<Node> queryBackup = queries;

    sort(queries.begin(), queries.end(), [](auto &a, auto &b) {
        // We sort the indices based on increasing ending of ranges
        // that way, each range counts distincts till its end only
        if (a.end == b.end) return a.start < b.start;
        return a.end < b.end;
    });

    FenwickTree bit(n);
    // Maintains index in queries
    int k = 0;
    // To maintain the number of elements till current element
    int total = 0;
    // To maintain last occurance index of all elements
    unordered_map<int, int> prev;
    // To store answers of queries in correct incoming order
    vector<int> res(q);

    for (int i = 1; i <= n; i += 1) {
        // If previous of current does not exist, then
        // it is unique & hence we store it
        if (prev.count(elems[i - 1]) == 0) {
            // By adding 1, we indicate that from this index
            // onwards, we are considering a new distinct
            bit.addElement(i, 1);
            total += 1;
        } else {
            // This element already exists, so we decrement 
            // the previous occurance, and increment for current
            bit.addElement(prev[elems[i - 1]], -1);
            bit.addElement(i, 1);
        }

        while (k < q && queries[k].end == i) {
            // For all the queries that are ending here,
            res[queries[k].index] = total - bit.query(queries[k].start - 1);
            k += 1;
        }

        prev[elems[i - 1]] = i;
    }

    cout << "\nThe number of distinct elements between," << endl;

    for (auto &x : queryBackup) {
        cout << "Index " << x.start << " [" << elems[x.start - 1] << "] and " << x.end << " [" << elems[x.end - 1] << "] is " << res[x.index] << "." << endl;
    }

    cout << endl;

    return 0;
}
