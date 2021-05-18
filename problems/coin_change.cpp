#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;

int modAdd(long long a, long long b) { return (a % MOD + b % MOD) % MOD; }

int getDenomWays(vector<int> &, int);

int main() {
    /**
     * In order to find the number of ways to reach a certain value
     * we have to add all the possible ways to reach that number
     * given we added a certain denomination. This process is to be 
     * repeated for all denominations and values till we reach that
     */ 
    cout << "\nThis program demonstrates the number of ways to attain a value with given set of denominations.\n" << endl;
    int n, val;
    cout << "Enter the number of denominations you have: ";
    cin >> n;
    cout << "Enter value you have to pay: ";
    cin >> val;

    vector<int> denoms(n);
    cout << "Enter space seperated values of denominations," << endl;
    for (int i = 0; i < n; i += 1) cin >> denoms[i];

    int possiblities = getDenomWays(denoms, val);

    cout << "\nThere are " << possiblities << " possible ways to reach " << val << "." << endl;

    cout << endl; 
    
    return 0;
}

int getDenomWays(vector<int> &denoms, int val) {
    // Since we only want to calculate till val
    vector<int> dp(val + 1);
    dp[0] = 1;

    // We will iterate for every currency in denomination
    for (auto &currency : denoms) {
        // Now we will add all possible ways to reach
        // a given value, after adding the denomination
        for (int j = currency; j <= val; j += 1) {
            // We need to add 'curr' to 'j - curr' to reach 'j'
            dp[j] = modAdd(dp[j], dp[j - currency]);
        }
    }

    return dp[val];
}