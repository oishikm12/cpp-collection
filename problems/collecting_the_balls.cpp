#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isBalanced(int, int);
int getArbValue(int);

int main() {
    /**
     * In order to find the optimal value for which player 1
     * will have more than half the number of balls by the end
     * we will use binary search and then confirm the result in
     * linear time. Since the optimal strategy skews towards mean,
     * this strategy will work
     */ 
    cout << "\nThis demonstrates how many balls player 1 needs to have more than half by the end in `collecting the balls` game.\n" << endl;
    int balls;
    cout << "Enter the number of balls present: ";
    cin >> balls;

    int arb = getArbValue(balls);

    cout << "\nThe first player will start taking " << arb << " balls each turn." << endl;

    cout << endl;

    return 0;
}

bool isBalanced(int balls, int k) {
    // We just need to ensure that left is half of total
    int left = 0;
    int total = balls;

    while (balls >= k && balls > 0) {
        left += k;
        balls -= k;
        // We do not need to store what the 2nd player has
        balls -= balls / 10;
    }
    // When the amount left is less than k, all goes
    // to the first player
    left += balls;

    return left * 2 >= total;
}

int getArbValue(int balls) {
    // In order to find the optimal value to start with
    // we will use binary search between 1 and all balls
    int min = 1;
    int max = balls;
    int ans;

    while (max >= min) {
        int mid = (max - min) / 2 + min;
        
        if (isBalanced(balls, mid)) {
            // Since we need least value, we will continue after
            // finding a suitable ans, to get the best
            ans = mid;
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }

    return ans;
}