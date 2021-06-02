#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getMaximumProfit(vector<pair<int, int>> &, int);

int main() {
    /**
     * In order to find out the maximum possible value we can 
     * get while placing items in our bag, we will maintain a 3D
     * array with first index representing which prime, the no. 
     * is multiplied with, 2nd index representing the number itself
     * and the third index representing the weight 
     */
    cout << "\nThis program finds out the maximal profit in carrying items in limited weight weherin each profit can have a certain multiplier\n" << endl;
    int n, cap;
    cout << "Enter number of items to consider: ";
    cin >> n;
    cout << "Enter capacity of bag to consider: ";
    cin >> cap;

    vector<pair<int, int>> items(n);
    cout << "Enter space seperated, value & weight of items delimited by line,";
    for (int i = 0; i < n; i += 1) cin >> items[i].first >> items[i].second;

    int maxValue = getMaximumProfit(items, cap);

    cout << "\nThe maximal profit we can get is: " << maxValue << endl;

    cout << endl;

    return 0;
}

int getMaximumProfit(vector<pair<int, int>> &items, int cap) {
    int n = items.size();

    // First 10 primes, indexed from 1
    vector<int> PRIMES = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    // Since to get the greates profit, we would want to 
    // multiply highest value with highes prime, we sort it
    sort(items.begin(), items.end());

    // Here the first index represents the selected value of prime
    // The second index represents the current item index we are considering
    // The third index represents the capacity of bag we are considering
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(n + 1, vector<int>(cap + 1, 0)));

    // Base case without any prime multiplication
    for (int i = 1; i <= n; i += 1) {
        for (int j = 1; j <= cap; j += 1) {
            if (j < items[i - 1].second) {
                // If the current item cannot be placed yet,
                // then we place whatever was possible till here
                dp[0][i][j] = dp[0][i - 1][j];
            } else {
                // We place max of whatever was possible, or including current
                int withoutCurr = dp[0][i - 1][j];
                int withCurr = items[i - 1].first + dp[0][i - 1][j - items[i - 1].second];
                dp[0][i][j] = max(withoutCurr, withCurr);
            } 
        }
    }

    // Now we simply check wether multiplication with primes
    // is worth for a certain index or not
    for (int prime = 1; prime <= 10; prime += 1) {
        // Since only the previous position is important
        // we can switch the indices b/w current & previous
        int p = prime % 2;

        for (int i = 1; i <= n; i += 1) {
            for (int j = 1; j <= cap; j += 1) {
                if (j < items[i - 1].second) {
                    // If the current item cannot be placed yet,
                    // we cannot multiply it with prime
                    dp[p][i][j] = dp[p][i - 1][j];
                } else {
                    // The first case would be not considering current
                    // and not multiplying with prime number
                    int withoutPrimeAndCurr = dp[p][i - 1][j];
                    // The next case would be considering current but
                    // not multiplying with prime number
                    int withoutPrimeButCurr = items[i - 1].first + dp[p][i - 1][j - items[i - 1].second];
                    // The last case would be considering current &
                    // multiplying with a prime, therein we have to 
                    // select last number multiplied with previous prime
                    // NOTE: for 2 row, previous is 1 ^(XOR) of current
                    int withPrimeAndCurr = items[i - 1].first * PRIMES[prime] + dp[p ^ 1][i - 1][j - items[i - 1].second];

                    dp[p][i][j] = max(withoutPrimeAndCurr, max(withoutPrimeButCurr, withPrimeAndCurr));
                } 
            }
        }
    }

    // Since there are 10 primes, the last value will be at 0 (10 % 2)
    return dp[0][n][cap];
}