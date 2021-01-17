#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * We use Pigeon Hole Priniciple to determine how many subarrays are possible
     * In order to do this we consider an extra sequence such that for n elements
     * there are n + 1 sequences to consider
     */ 
    cout << "\nThis program finds all possibe subarrays whose sum is divisible by array length.\n" << endl;
    int len;
    cout << "Enter length of array : ";
    cin >> len;

    vector<int> arr(len);
    vector<int> freq(len, 0);

    freq[0] = 1; // By doing this we are creating n + 1 pigeons for n holes
    // eg  -    1  3  5  7
    // %4 =>    1  3  1  3
    // +1 => 1  1  3  1  3
    // freq => 1*3  3*2
    // ans  => 3c2 + 2c2

    cout << "Enter space seperated elements of array," << endl;
    for (int i = 0; i < len; i += 1) cin >> arr[i];

    // Now we populate the frequency of each element after modulo by length
    int cumSum = 0;
    for (int i = 0; i < len; i += 1) {
        cumSum += arr[i];
        int modSum = cumSum % len;
        modSum = (modSum + len) % len; // this will remove -ve if any
        freq[modSum] += 1;
    }

    // Then we simply find its 2 combinations
    int ans = 0;
    for (int i = 0; i < len; i += 1) {
        // n C 2 => n * n - 1 / 2
        if (freq[i] != 0) ans += (freq[i] * (freq[i] - 1) / 2);
    }

    cout << "\nThere are " << ans << " such possible subarrays." << endl;

    cout << endl;

    return 0;
}