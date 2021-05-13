#include <iostream>
using namespace std;

const long long MOD = 1e9 + 7;

int modAdd(long long a, long long b) { return (a % MOD + b % MOD) % MOD; }
int modMul(long long a, long long b) { return (a % MOD * b % MOD) % MOD; }

int calculateBT(int);

int main() {
    /**
     * When we consider a balanced binary tree there are only
     * 3 possible configurations:
     * a. Left and right nodes are both one height less
     * b. Left node is twice less and the other one less
     * c. Right node is twice less and the other one less
     */ 
    cout << "\nThis problem finds out possible number of balanced binary tree configs\n" << endl;
    int n;
    cout << "Enter the number of nodes to consider: ";
    cin >> n;

    int bbt = calculateBT(n);

    cout << "\nThere are " << bbt << " possible balanced binary trees." << endl;

    cout << endl;

    return 0;
}

int calculateBT(int nodes) {
    // There can only be 1 possiblity involving 
    // one node and empty tree
    if (nodes == 0 || nodes == 1) return 1;

    // Either the child can have height of n - 1 or n - 2
    // only then the parent node can be considered balanced
    int prev = calculateBT(nodes - 1);
    int prevOfPrev = calculateBT(nodes - 2);

    // Possible configurations = x * x + y * x + x * y
    // where x is n - 1 nodes & y is n - 2 nodes 
    int possiblities = modAdd(modMul(prev, prev), modMul(2, modMul(prev, prevOfPrev)));

    return possiblities;
}
