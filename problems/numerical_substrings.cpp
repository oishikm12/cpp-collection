#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;

int modAdd(long long a, long long b) { return (a % MOD + b % MOD) % MOD; }
int modMul(long long a, long long b) { return (a % MOD * b % MOD) % MOD; }

int getSubSum(string &);

int main() {
    /**
     * In order to find out the sum of all sunstrings, we need 
     * to find the pattern, that for each included digit the 
     * recurring subproblem occurs ~ prev * 10 + digit * idx
     * eg. 16 -> (0 * 10 + 1 * 1) + (1 * 10 + 2 * 6) = 23 
     */ 
    cout << "\nThis program finds out the sum of all possible substrings of a numerical string.\n" << endl;
    string s;
    cout << "Enter the string to find substring sum of: ";
    cin >> s;

    int sum = getSubSum(s);

    cout << "\nThe sum of all substrings is: " << sum << "." << endl;

    cout << endl;

    return 0;
}

int getSubSum(string &s) {
    int n = s.size();
    vector<int> dp(n + 1);
    dp[0] = 0;

    for (int i = 1; i <= n; i += 1) {
        // We simply multiply the previous value with 10
        int prev = modMul(dp[i - 1], 10);
        // The current value is multiplied by the index
        // since it will be added that many times to this position
        int curr = (s[i - 1] - '0') * i;
        dp[i] = modAdd(prev, curr);
    }

    return dp[n];
}