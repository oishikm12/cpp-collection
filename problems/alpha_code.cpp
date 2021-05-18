#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;

int modAdd(long long a, long long b) { return (a % MOD + b % MOD) % MOD; }

int getCodes(string &);

int main() {
    /**
     * In order to decide how many posssiblities are there
     * we need to simply add what was possible till last &
     * what would be possible if we consider previous & current
     * to be a 2 digit number
     */ 
    cout << "\nThis program finds out how many possible codes are possible from a number where each 1 to 26 is A to B\n" << endl;
    string s;
    cout << "Enter the encoded string: ";
    cin >> s;

    int possiblities = getCodes(s);

    cout << "There are " << possiblities << " possible secret texts." << endl;

    cout << endl;

    return 0;
}

int getCodes(string &s) {
    int n = s.size();  
  
    // 0 represents no character hence we ignore it
    if (s == "0") return 0;
    
    vector<int> arr(n), dp(n + 1);
    // Here we convert string to integer array for ease
    for (int i = 0; i < n; i += 1) arr[i] = s[i] - '0';
    // There is 1 possible configs for 0 & 1 length of numbers
    dp[0] = dp[1] = 1;
    
    for (int i = 1; i < n; i += 1) {
        // This is for when we consider each digit to be a character
        if (arr[i]) dp[i + 1] = modAdd(dp[i], dp[i + 1]);

        // val will be 0 if both prev & current isnt possible
        // otherwise it will be a 2 digit number 
        int val;
        if (arr[i - 1] && arr[i]) val = arr[i - 1] * 10 + arr[i];
        else val = 0;

        // There are only 26 alphabets
        if (val > 0 && val <= 26) dp[i + 1] = modAdd(dp[i - 1], dp[i + 1]);
    }
    
    return dp[n];
}