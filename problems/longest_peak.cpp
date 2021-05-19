#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * In order to find the longest peak, we can maintain
     * two auxillary arrays, one maintaing how many descending
     * elements to the left & the other how many descending 
     * to the right. Adding these will give us length of peak
     */ 
    cout << "\nThis problem finds out longest numerical peak (ascending then descending), in a sequence of numbers.\n" << endl;
    int n;
    cout << "Enter the length of the list: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space seperated elements of the list," << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    vector<int> leftDesc(n, 1), rightDesc(n, 1);
    for (int i = 1; i < n; i += 1) {
        if (elems[i - 1] <= elems[i]) leftDesc[i] += leftDesc[i - 1];
        if (elems[n - i - 1] >= elems[n - i]) rightDesc[n - i - 1] += rightDesc[n - i];
    }

    int maxPeak = INT_MIN;
    for (int i = 0; i < n; i += 1) maxPeak = max(maxPeak, leftDesc[i] + rightDesc[i] - 1);

    cout << "\nThe longest peak possible here is of length: " << maxPeak << "." << endl;

    cout << endl;

    return 0;
}