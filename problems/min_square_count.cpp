#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int getConfigs(int);

int main() {
    /**
     * Finding out all squares whose sum results in a specific value
     * can be done via iteration, in order to find out the one which
     * requires minimum addition of squares, we can use min function
     */ 
    cout << "\nThis program finds out the possible configurations where sum of squares results in a particular value.\n" << endl;
    int num;
    cout << "Enter the number whose sum of squares to find: ";
    cin >> num;

    int configs = getConfigs(num);

    cout << "\nThe sum of (at least) " << configs << " squares will result in " << num << "." << endl;

    cout << endl;

    return 0;
}

int getConfigs(int num) {
    vector<int> dp(num + 1);
  
    // For all perfect squares it takes just 1 square to reach them
    for (int i = 1; i <= sqrt(num); i += 1) dp[i * i] = 1;
    
    for (int i = 2; i <= num; i += 1) {
        // We can already reach this via 1 square
        if (dp[i] != 0) continue;
        
        // Possible ways to reach a number will be 
        // y to reach something, n - y to reach the rest
        // We need to repeat this for till we get the value
        // In case a number is not reachable, it remains INF
        int minSqs = INFINITY;
        for (int j = 1; j < sqrt(i); j += 1) {
            int pos = j * j;
            minSqs = min(minSqs, dp[pos] + dp[i - pos]);
        }
        
        dp[i] = minSqs;
    }

    return dp[num];
}