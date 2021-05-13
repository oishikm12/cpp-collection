#include <iostream>
#include <vector>
using namespace std;

int getMaxSubProduct(vector<int>&);

int main() {
    /**
     * In order to find the maximum product subarray, we will be maintaining
     * two product containers, one to store the positive product and one to
     * store negative product. Each time we encounter a negative number,
     * we swap these containers, thereby the positive container will be max
     */ 
    cout << "\nThis program finds out the maximum product subarray inside an array.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array" << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int maxProd = getMaxSubProduct(arr);

    cout << "\nThe maximum product that can be obtained from it's subarray is: " << maxProd << endl;

    cout << endl;

    return 0;
}

int getMaxSubProduct(vector<int> &arr) {
    int maxProd;
    int maxEndingHere = 1, minEndingHere = 1;

    for (auto &x : arr) {
        if (x < 0) {
            // If the value is less than 0, then a negative subarray becomes
            // positive and a positive one becomes negative, so we swap
            int temp = maxEndingHere;
            maxEndingHere = max(1, minEndingHere * x);
            minEndingHere = temp * x;
        } else if (x > 0) {
            // If the value is positive, we simply multiply it to positive subarr
            maxEndingHere = maxEndingHere * x;
            maxEndingHere = min(1, maxEndingHere * x);
        } else {
            // A zero value represents end of a subarray
            maxEndingHere = 1;
            minEndingHere = 1;
        }

        // We store the subarray product at each step
        maxProd = max(maxEndingHere, minEndingHere);
    }

    return maxProd;
}