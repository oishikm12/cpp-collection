#include <iostream>
#include <vector>
using namespace std;

class SegTree {
    private:
        vector<int> arr;
        vector<pair<int, int>> tree;

    public:
        // Initializes the segment tree
        SegTree(vector<int> &);

        // Builds a segment Tree via recursion
        void buildTree(int, int, int = 1);

        // Performs query on range
        pair<int, int> query(int, int, int, int, int = 1);
};

SegTree :: SegTree(vector<int> &elems) {
    // We allocate four times the size of the given array
    // The actual size is 2 * pow(2, ceil(log2(arr.size()))) - 1
    tree.resize(4 * elems.size());
    arr = elems;

    // Recursively build the tree
    buildTree(1, arr.size() - 1);
}

void SegTree :: buildTree(int startingNode, int endingNode, int currNode) {
    // Base Condition, i.e. when start and end match, we
    // want to place the element at this node
    if (startingNode == endingNode) {
        // We will store a pair of value, -startingNode (dist from start)
        tree[currNode] = {arr[startingNode], -startingNode};
        return;
    }

    int mid = (endingNode - startingNode) / 2 + startingNode;

    // For a complete binary tree, the children of a node are
    // present at 2 * curr for left & 2 * curr + 1 for right
    buildTree(startingNode, mid, 2 * currNode);
    buildTree(mid + 1, endingNode, 2 * currNode + 1);

    // We store the element which can fetch us ticket to
    // the station closest to destination
    tree[currNode] = max(tree[2 * currNode], tree[2 * currNode + 1]);
}

pair<int, int> SegTree :: query(int left, int right, int startingNode, int endingNode, int currNode) {
    // Case when completely outiside given range [S, E] < L || R < [S, E]
    if (left > endingNode || right < startingNode) return {0, -(int)(arr.size())};

    // Case when completely inside range L <= [S, E] <= R
    if (left <= startingNode && endingNode <= right) return tree[currNode];

    // Otherwise we will consider the range to be
    // partially present in both of its children
    // S <= L <= E || S <= R <= E
    int mid = (endingNode - startingNode) / 2 + startingNode;
    auto part1 = query(left, right, startingNode, mid, 2 * currNode);
    auto part2 = query(left, right, mid + 1, endingNode, 2 * currNode + 1);

    // We will simply return the maximum value from these
    // i.e. one that can likely reach destination
    return max(part1, part2);
}

int getMaxTicketSum(vector<int> &);

int main() {
    /**
     * In order to find the no.of tickets needed from each station
     * to destination, we will use a segment tree, and in order 
     * prevent re calculation, we will memoize the results
     */
    cout << "\nThis problem calculates sum of minimum tickets required from each station to reach the last destination.\n" << endl;
    int n;
    cout << "Enter the number of stations to consider: ";
    cin >> n;

    vector<int> tickets(n);
    cout << "Enter space seperated, max reachable station from each station, for all except last," << endl;
    for (int i = 1; i < n; i += 1) cin >> tickets[i];

    int maxSum = getMaxTicketSum(tickets);

    cout << "\nThe sum of minimum tickets required from each station to reach destination is " << maxSum << '.' << endl;

    cout << endl;

    return 0;
}

int getMaxTicketSum(vector<int> &arr) {
    int n = arr.size();

    SegTree seg(arr);

    // We will use a memoiztion table to store
    // the minimum tickets needed to reach the destination
    // from a certain station. As such any train 
    // arriving here will simply add to this minimum
    vector<int> dp(n + 1, 0);

    int res = 0;

    for (int i = n - 1; i >= 1; i -= 1) {
        auto [value, idx] = seg.query(i + 1, arr[i], 1, n - 1);
        // The actual cost is equal to distance from destination
        // minus the intermediate node, added to cost from intermediate
        // station to destination
        dp[i] = (n - i) - (arr[i] - abs(idx)) + dp[abs(idx)];
        res += dp[i];
    }

    return res;
}