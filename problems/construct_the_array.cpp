#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;

int modAdd(long long a, long long b) { return (a % MOD + b % MOD) % MOD; }
int modMul(long long a, long long b) { return (a % MOD * b % MOD) % MOD; }

int getUniArrs(int, int, int);

int main() {
    /**
     * In order to prevent consequitive elements from repeating
     * all we have to do is add the possible subsequences of all
     * other numbers till then other than the one we are at
     */ 
    cout << "\nThis program finds out the possible variations of arrays possible such that consequitive elements are unique.\n" << endl;
    int n, end, range;
    cout << "Enter the length of this array: ";
    cin >> n;
    cout << "Enter the element to end with: ";
    cin >> end;
    cout << "Enter the range of elements to consider in the array: ";
    cin >> range;

    int possiblities = getUniArrs(n, range, end);

    cout << "\nThere are " << possiblities << " possible such arrays." << endl;

    cout << endl;

    return 0;
}

int getUniArrs(int n, int elems, int end) {
    // Since we know that the array will start with 1
    // All the other possiblities will essentially be the same
    // Hence we can convert them to `ending with 1` or not
    vector<pair<int, int>> dp(n + 1);

    // With length = 1 & start 1, there is only possiblity
    // no such possiblity exists to end with other numbers
    dp[1] = make_pair(1, 0);

    for (int i = 2; i <= n; i += 1) {
        int prevEndWithOne = dp[i - 1].first;
        int prevEndNotOne = dp[i - 1].second;

        // For an element ending with 1, we need to add,
        // all endings previously not with 1
        dp[i].first = modMul(prevEndNotOne, elems - 1);
        // For others we need to add the rest of the elems
        // and the one previously ending with 1
        dp[i].second = modAdd(modMul(prevEndNotOne, elems - 2), prevEndWithOne);
    }

    if (end == 1) return dp[n].second;
    else return dp[n].first;
}