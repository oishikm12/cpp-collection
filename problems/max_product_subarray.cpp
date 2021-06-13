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
    // We initialize all variables with the first element of list
    int maxProd = arr[0];
    int maxEndingHere = arr[0];
    int minEndingHere = arr[0];

    for (int i = 1; i < arr.size(); i += 1) {
        // If the value is less than 0, then a negative subarray becomes
        // positive and a positive one becomes negative, so we swap
        if (arr[i] < 0) swap(maxEndingHere, minEndingHere);

        // We store the greater of the multiplication in maximum
        // and smaller of them in minimum, simply to swap later
        maxEndingHere = max(arr[i], maxEndingHere * arr[i]);
        minEndingHere = min(arr[i], minEndingHere * arr[i]);

        // We store the subarray product at each step
        maxProd = max(maxProd, maxEndingHere);
    }

    return maxProd;
}