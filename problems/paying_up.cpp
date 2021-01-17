#include <iostream>
#include <vector>
using namespace std;

bool isPayable(vector<int>&, int, int);

int main() {
    /**
     * Our task is to find out if there exists a subset among a given array
     * such that its sum is equal to what we desire
     */ 
    cout << "\nThis program finds out if we have the amount payable.\n" << endl;
    int len, amt;
    cout << "Enter the no. of notes you have : ";
    cin >> len;
    cout << "Enter the amount asked of you : ";
    cin >> amt;

    vector<int> arr(len);

    cout << "Enter space seperated denominations you have," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    bool canPay = isPayable(arr, len, amt);

    if (canPay) cout << "\nYes" << endl;
    else cout << "\nNo" << endl;

    cout << endl;

    return 0;
}

bool isPayable(vector<int> &arr, int len, int amt) {
    // In order to find out the suitable subset we use bit manipulations 
    // to check if their sum is equal to desired
    // NOTE : This is viable only if len is small, i.e. < 20

    // This acts as mask for which no. to select, i.e 2 ^ n
    int total = 1 << len;

    for (int i = 1; i < total; i += 1) {
        int sum = 0;

        // For any given value of i, we and with i << j to check which nos
        // get added to mask, eg. 10101 will add 5th+3rd+1st & compare with m
        // This is in essence a brute force approach that calculates all
        // possible substring sum
        for (int j = 0; j < len; j += 1) {
            if (i & (1 << j)) sum += arr[j];
        }

        if (sum == amt) return true;
    }

    return false;
}