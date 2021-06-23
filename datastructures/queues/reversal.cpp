#include <iostream>
#include <queue>
using namespace std;

void reverse(queue<int> &);

int main() {
    /**
     * In order to reverse a queue, we will simply be using the call
     * stack to recursively store the elements till the queue is empty
     * and then reinserting them, effectively reversing the order.
     */ 
    cout << "\nThis program recursively revereses a queue.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    queue<int> q1, q2;

    cout << "Enter space seperated elements to insert into queue," << endl;
    for (int i = 0; i < n; i += 1) {
        int temp;
        cin >> temp;
        q1.push(temp);
        q2.push(temp);
    }

    reverse(q2);

    cout << "\nThe order of elements before reversal is," << endl;
    while (!q1.empty()) {
        cout << q1.front();
        q1.pop();
        if (!q1.empty()) cout << " ";
    }
    cout << "\nThe order of elements after reversal is," << endl;
    while (!q2.empty()) {
        cout << q2.front();
        q2.pop();
        if (!q2.empty()) cout << " ";
    }

    cout << endl << endl;

    return 0;
}

void reverse(queue<int> &q) {
    // Base case when queue is empty
    if (q.empty()) return;

    // We store the current element, remove it from queue and then
    // recursively call the same function till it hits base case
    int temp = q.front();
    q.pop();

    reverse(q);

    // When we reinsert after recursive function, the elements after
    // the front have already been reinserted, and current is now
    // pushed onto the back of the queue 
    q.push(temp);
}