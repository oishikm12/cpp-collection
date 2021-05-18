#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

const long long MOD = 1e9 + 7;

int modAdd(long long a, long long b) { return (a % MOD + b % MOD) % MOD; }

int getIncSub(vector<int> &);

int main() {
    /**
     * In order to find out what number to possibly select, we can
     * maintain an 2D array representing ending at value for first 
     * index, and gcd value as 2nd index. In the end we have to add
     * all the endings at GCD 1
     */
    cout << "\nThis program finds out number of increasing subsequences with GCD equal to 1.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> elems(n);
    cout << "Enter space space seperated elements of the list," << endl;
    for (int i = 0; i < n; i += 1) cin >> elems[i];

    int seqs = getIncSub(elems);

    cout << "\nThere exists " << seqs << " such sequences." << endl;

    cout << endl;

    return 0;
}

int getIncSub(vector<int> &elems) {
    int n = elems.size();
    // Since we know that each individual element
    // can be upto 100, we design our dp array,
    // such that [ending at this idx(0 -> n - 1)][gcd(1 -> 100)]
    vector<vector<int>> dp(n, vector<int>(101));

    for (int i = 0; i < n; i += 1) {
        // dp for index and the gcd equal to that element is 1
        // i.e. 1 such sequence exist where GCD & number is same
        dp[i][elems[i]] = 1;

        for (int j = 0; j < i; j += 1) {
            // Since the subsequence needs to be increasing
            // if the current element is greater we do not 
            // consider it
            if (elems[j] >= elems[i]) continue;

            for (int gc = 1; gc <= 100; gc += 1) {
                // We check GCD after comparing with all possible
                // values with the current element
                int hcf = gcd(gc, elems[i]);
                // We simply add how many ended at `j` with hcf = `gc`
                dp[i][hcf] = modAdd(dp[i][hcf], dp[j][gc]);
            }
        }
    }
    
    // Now we simply need to add all subsequences with GCD 1
    int gcOne = 0;
    for (int i = 0; i < n; i += 1) gcOne = modAdd(gcOne, dp[i][1]);
    
    return gcOne;
}