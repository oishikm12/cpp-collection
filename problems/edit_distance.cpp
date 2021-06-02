#include <iostream>
#include <vector>
using namespace std;

int getEditDistance(string &, string &);

int main() {
    /**
     * If we were to convert one string into another, we would
     * start with two pointers for both strings, at each step,
     * 1. deleting, would increment the first pointer
     * 2. inserting, would increment the second pointer
     * 3. replacing, would increment both the pointers
     */ 
    cout << "\nThis program finds out the minimal cost involved in converting one string to another.\n" << endl;
    
    string s1, s2;
    cout << "Enter the first string to consider: ";
    cin >> s1;
    cout << "Enter the second string to consider: ";
    cin >> s2;

    int dist = getEditDistance(s1, s2);

    cout << "\nThe cost to convert " << s1 << " into " << s2 << " is: " << dist << "." << endl;

    cout << endl;

    return 0;
}

int getEditDistance(string &s1, string &s2) {
    int n = s1.size();
    int m = s2.size();
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // If the length of the second string is fixed at 0
    // then whatever is the length of first string,
    // that becomes the cost to convert it into second
    for (int i = 1; i <= n; i += 1) dp[i][0] = i;
    // The same is true if the first string is fixed at 0
    for (int i = 1; i <= m; i += 1) dp[0][i] = i;

    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= m; j += 1) {
            // The characters at this position are the same
            // hence we simply copy over the cost previously
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            // Inserting a character, adds 1 to whatever was cost at j - 1
            // Deleting a character, adds 1 to whatever was cost at i - 1
            // Replacing a character, adds 1 to whatever was cost at i - 1 & j - 1
            // We simply have to choose the minimal of all these
            else dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
        }
    }
    
    return dp[n][m];
}