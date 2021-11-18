#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void radixSort(vector<int> &);
void countSort(vector<int> &, int);

int main() {
    /**
     * Radix Sort implements Counting Sort, however instead of using 
     * the entire number, it uses a specific unit at a time, i.e a
     * unit's place, ten's place, etc while mainting relative ordering
     * done by the previous iteration of the sort
     */ 
    cout << "\nThis program uses Radix Sorting to sort a list in ascending order\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array to consider," << endl;
    for (auto &x : arr) cin >> x;

    radixSort(arr);

    cout << "\nAfter sorting, the list becomes," << endl;
    for (auto &x : arr) cout << x << ' ';

    cout << endl << endl;

    return 0;
}

void radixSort(vector<int> &arr) {
    // First we need to find out the biggest number in the list, since
    // that many digits need to parsed for each number
    int mxElem = *max_element(arr.begin(), arr.end());

    // Since we need a digit at specific place for each number, we need
    // to divide each of them with a specific exponent, which we loop here
    for (int exponent = 1; (mxElem / exponent) > 0; exponent *= 10) countSort(arr, exponent);
}

void countSort(vector<int> &arr, int exponent) {
    // We use an ouptut vector to store the result of the sorting
    vector<int> output(arr.size());
    // Similarly, to implement counting sort, we will need an array to store
    // the relative ordering, and since there are only 10 digit
    int cnt[10] = {0};

    // Just like count sort, we simply store the digits in its indices
    for (int i = 0; i < arr.size(); i += 1) cnt[(arr[i] / exponent) % 10] += 1;

    // Then we convert this array into its prefix version, this way
    // we know exactly how many occurances of the same digit are there
    for (int i = 1; i < 10; i += 1) cnt[i] += cnt[i - 1];

    // In order to get our sorted arr, we simply reinsert them into
    // positions referred to by their prefixed Count array 
    // The reason we traverse from the end, is because our prefix arr
    // tells us the last occurance of a certain digit, not its first
    for (int i = arr.size() - 1; i >= 0; i -= 1) {
        output[cnt[(arr[i] / exponent) % 10] - 1] = arr[i];
        cnt[(arr[i] / exponent) % 10] -= 1;
    }

    // We copy the values back to the input array
    for (int i = 0; i < arr.size(); i += 1) arr[i] = output[i];
}