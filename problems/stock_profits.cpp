#include <iostream>
#include <vector>
using namespace std;

int maximumProfit(int, int, int, bool, vector<int> &, vector<vector<vector<int>>> &);

int main() {
    /**
     * In order to find out what maximum profit we can get, we will
     * maintain a 3D array representing what the current item being
     * considered is, the number of transactions left & wether a
     * transaction is ongoing or not. Accordingly we will recurse
     */ 
    cout << "\nThis program finds out the maximum profit that can be made by buying and selling stocks a certain number of times.\n" << endl;
    int n, k;
    cout << "Enter the number of days stock market is open: ";
    cin >> n;
    cout << "Enter the number of transactions you are allowed to make: ";
    cin >> k;

    vector<int> prices(n);
    cout << "Enter space seperated prices of stock on each of those days," << endl;
    for (int i = 0; i < n; i += 1) cin >> prices[i];

    vector<vector<vector<int>>> profits(n + 1, vector<vector<int>>(k + 1, vector<int>(2, -1)));

    int profit = maximumProfit(0, n, k, false, prices, profits);

    cout << "\nThe maximum profit you can make is: " << profit << "." << endl;

    cout << endl;

    return 0;
}

int maximumProfit(int curr, int days, int trans, bool ongoing, vector<int> &prices, vector<vector<vector<int>>> &profits) {
    // We have traversed all days or have finished desired transactions
    if (curr == days || trans == 0) return 0;

    // We have previously found out max profit this way
    if (profits[curr][trans][ongoing] != -1) return profits[curr][trans][ongoing];

    // We are not going to consider any transaction on this day
    int excludeCurrent = maximumProfit(curr + 1, days, trans, ongoing, prices, profits);
    // We will include current, but check if we can buy or sell
    int includeCurrent = INT_MIN;

    if (ongoing) {
        // We are considering selling previously bought stock at this stage
        // as such we are finishing one transaction
        includeCurrent = maximumProfit(curr + 1, days, trans - 1, false, prices, profits) + prices[curr];
    } else {
        // We will consider buying a new stock, however no. of transaction
        // only goes down when selling, since that marks end of trade
        includeCurrent = maximumProfit(curr + 1, days, trans, true, prices, profits) - prices[curr];
    }

    profits[curr][trans][ongoing] = max(excludeCurrent, includeCurrent);
    
    return profits[curr][trans][ongoing];
}