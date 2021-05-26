#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    /**
     * In order to keep track of K largest numbers at all
     * time we will simply be using a priority queue as a
     * min heap, that way whenever we pop an element the 
     * smalles ones will be removed first
     */ 
    cout << "\nThis program finds out K largest elements in a sliding window of elements.\n" << endl;
    int n, k;
    cout << "Enter number of elements to consider: ";
    cin >> n;
    cout << "Enter size of window to consider: ";
    cin >> k;

    // We need to maintain a min heap to ensure 
    // only small elements are removed when needed
    priority_queue<int, vector<int>, greater<int>> window;

    cout << "Enter space seperated elements of the stream," << endl;

    for (int i = 0; i < n; i += 1) {
        int num;
        cin >> num;

        if (window.size() < k) {
            // First k elements
            window.push(num);
        } else {
            if (num > window.top()) {
                // We should only bother if this element is greater
                // Otherwise no need to insert and delete this itself
                window.pop();
                // Remove the smaller element, insert the bigger
                window.push(num);
            }
        }
    }

    cout << "\nThe largest " << k << " elements are," << endl;
    while (!window.empty()) {
        cout << window.top();
        window.pop();
        if (!window.empty()) cout << ", ";
    }

    cout << endl;

    return 0;
}