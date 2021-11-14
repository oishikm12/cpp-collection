#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mex(vector<int> &);
vector<int> calculateGrundy(vector<int> &, int);
int nimSum(vector<int>);

int main() {
    /**
     * In order to find out the winner we will first check if there is any 
     * limitation to number of pebbles we can pick, if so then we apply
     * sprague-grundy theorem, and then apply nimsum, otherwise we simply
     * find out the nim sum of the sets, which is XOR of all the number of 
     * pebbles in each set. If the result is 0 then the starting player loses
     */ 
    cout << "\nThis program finds out winning player in NIM game.\n" << endl;
    int n;
    cout << "Enter the number of stack of pebbles to consider: ";
    cin >> n;

    int mx;
    cout << "Enter the maximum pebbles we can take from a stack, 0 for unlimited: ";
    cin >> mx;

    vector<int> pebbles(n);
    cout << "Enter space seperate size of pebble stacks: ";
    for (auto &x : pebbles) cin >> x;

    int ans = 0;

    if (mx == 0) ans = nimSum(pebbles);
    else ans = nimSum(calculateGrundy(pebbles, mx));

    // The logic behand this is, if the cumulative XOR is 0, when Player 1 starts
    // taking pebbles, itll turn into non-zero for Player 2, who will turn it back
    // into zero. After such exchanges, Player 1 will end with XOR of 0, since there
    // are no pebbles to take and as such lose
    int nimSum = 0;
    for (auto &x : pebbles) nimSum = nimSum ^ x;

    if (nimSum == 0) cout << "\nPlayer 1 will lose the game" << endl;
    else cout << "\nPlayer 1 will win the game" << endl;

    cout << endl;

    return 0;
}

int nimSum(vector<int> vals) {
    // The logic behand this is, if the cumulative XOR is 0, when Player 1 starts
    // taking pebbles, itll turn into non-zero for Player 2, who will turn it back
    // into zero. After such exchanges, Player 1 will end with XOR of 0, since there
    // are no pebbles to take and as such lose
    int nimSum = 0;
    for (auto &x : vals) nimSum = nimSum ^ x;

    return nimSum;
}

vector<int> calculateGrundy(vector<int> &pebbles, int mx) {
    // Grundy number is that number which tells us how many times a certain number
    // can be used in a sequence, hence for our case it tells us how many pebbles
    // remain in optimal chosing case
    int maxSize = *max_element(pebbles.begin(), pebbles.end());
    vector<int> dp(maxSize + 1, 0);

    // Grundy(0) = 0, otherwise for `n`, grundy(n) = MEX({all numbers reachable from n})
    // MEX is minimum positive exclusion, which is non zero positive number not is given set
    for (int i = 1; i <= mx; i += 1) dp[i] = i;
    for (int i = mx + 1; i <= maxSize; i += 1) dp[i] = dp[i - mx - 1];

    vector<int> result;
    for (auto &x : pebbles) result.push_back(dp[x]);

    return result;
}