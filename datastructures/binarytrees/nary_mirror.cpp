#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

bool areMirrors(vector<int> &, vector<int> &);
bool mirroredSubtrees(vector<stack<int>> &, vector<queue<int>> &);

int main() {
    /**
     * In order to find out wether two n-ary trees are
     * mirror of each other or not, we can store one in
     * stack, and the other in queue, that way when popped
     * same values represent a mirror
     */ 
    cout << "\nThis program checks if two n-ary trees are mirror of each other or not.\n" << endl;
    int n, m;
    cout << "Enter the number of edges in the trees: ";
    cin >> n;

    vector <int> tree1(n * 2), tree2(n * 2);
    cout << "Enter space seperated (u - v) edge values of the first tree,";
    for (int i = 0; i < n * 2; i += 1) cin >> tree1[i];
    cout << "Enter space seperated (u - v) edge values of the second tree,";
    for (int i = 0; i < n * 2; i += 1) cin >> tree2[i];

    bool isMirrorred = areMirrors(tree1, tree2);

    if (isMirrorred) cout << "\nThe two trees are mirrors of each other." << endl;
    else cout << "\nThe two trees are not mirrors." << endl;

    cout << endl;

    return 0;
}


bool areMirrors(vector<int> &tree1, vector<int> &tree2) {
    int n = tree1.size();

    vector<stack<int>> t1(n / 2 + 1);
    vector<queue<int>> t2(n / 2 + 1);
    
    for (int i = 0; i < n; i += 2) {
        // Pushing node in the stack of first tree.
        t1[tree1[i]].push(tree1[i + 1]);  
        // Pushing node in the queue of second tree.
        t2[tree2[i]].push(tree2[i + 1]);
    }
 
    return mirroredSubtrees(t1, t2);
}


bool mirroredSubtrees(vector<stack<int>> &tree1, vector<queue<int>> &tree2) {
    // 1st vector stores all nodes and adjacent of every node in a stack.
    // 2ns vector stores all nodes and adjacent of every node in a queue.
    // Traversing each node in tree.
    for (int i = 1; i < tree1.size(); i += 1) {
        stack<int> &s = tree1[i];
        queue<int> &q = tree2[i];
 
        // While stack is not empty && Queue is not empty
        while (!s.empty() && !q.empty()) { 
            // Checking top element of stack and front of queue.
            if (s.top() != q.front()) return false;
 
            s.pop();
            q.pop();
        }
 
        // If queue or stack is not empty, return false.
        if (!s.empty() || !q.empty()) return false;
    }
 
    return true;
}
