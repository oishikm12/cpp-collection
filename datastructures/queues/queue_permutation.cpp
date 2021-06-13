#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

bool checkQueuePermutation(vector<int> &, vector<int> &, int);

int main() {
    /**
     * In order to check if it is possible for one queue ordering to be
     * a permutation of the other, we will use a queue to store all the
     * elements in order, then compare all elements in same order as insertion,
     * if they do not match, we will use a stack to keep track of traversed
     * elements, till a match is found 
     */ 
    cout << "\nThis program compares contents of two queue to check if they are permutations of each other or not.\n" << endl;
    int n;
    cout << "Enter number of elements to consider: ";
    cin >> n;

    vector<int> queue1(n), queue2(n);

    cout << "Enter space seperated elements of the first queue," << endl;
    for (int i = 0; i < n; i += 1) cin >> queue1[i];
    cout << "Enter space sepreated elements of the second queue," << endl;
    for (int j = 0; j < n; j += 1) cin >> queue2[j];

    bool isPerm = checkQueuePermutation(queue1, queue2, n);

    if (isPerm) cout << "\nThe first queue can be permuted into the second queue." << endl;
    else cout << "\nThe first queue cannot be permuted into the second queue." << endl;

    cout << endl;

    return 0;
}

bool checkQueuePermutation(vector<int> &ip, vector<int> &op, int n) {
    // Input queue
    queue<int> input;
    for (auto &x : ip) input.push(x);
  
    // Output queue
    queue<int> output;
    for (auto &y : op) output.push(y);
  
    // Stack to be used for permutation
    stack <int> tempStack;

    while (!input.empty()) {
        int ele = input.front();
        input.pop();

        if (ele == output.front()) {
            output.pop();

            while (!tempStack.empty()) {
                if (tempStack.top() == output.front()) {
                    tempStack.pop();
                    output.pop();
                } else break;
            }
        } else {
            tempStack.push(ele);
        }
    }
  
    // If after processing, both input queue and
    // stack are empty then the input queue is
    // permutable otherwise not.
    return (input.empty() && tempStack.empty());
}