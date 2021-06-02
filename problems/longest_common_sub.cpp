#include <iostream>
#include <vector>
using namespace std;

int getLongestCommonSub(string &, string &);

int main() {
    /**
     * If we were to iterate over both the strings simultaneously,
     * there could be two possible scenarios:
     * 1. The letter at both the indices in either string is same
     *    hence we would increment both the pointers
     * 2. The letters are not same, wherein we could increment just
     *    th first, or just the second pointer
     * Thus, in order to find the LCS, we implement this logic  
     */ 
    cout << "\nThis program finds out the length of the longest common subsequence between two strings.\n" << endl;
    
    string s1, s2;
    cout << "Enter the first string to consider: ";
    cin >> s1;
    cout << "Enter the second string to consider: ";
    cin >> s2;

    int lcs = getLongestCommonSub(s1, s2);

    cout << "\nThe longest common subsequence between " << s1 << " and " << s2 << " is of length: " << lcs << "." << endl;

    cout << endl;

    return 0;
}

int getLongestCommonSub(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            // If the characters at this positions are equal
            // then we add 1 to whatever the count was till
            // previous positions of both strings, i.e i - 1 & j - 1
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
            // Otherwise we simply take whatever count was maximum
            // one step back of either string
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    return dp[n][m];
}