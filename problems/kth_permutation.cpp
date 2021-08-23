#include <iostream>
#include <set>
using namespace std;

string findKthPermutation(int, int);
int findFirstNumIndex(int &, int);

int main() {
    /**
     * The first position of an n length sequence is occupied 
     * by each of the numbers from 1 to n exactly n! / n that 
     * is (n-1)! number of times and in ascending order. So the 
     * first position of the kth sequence will be occupied by 
     * the number present at index = k / (n-1)!
     */
    cout << "\nThis program finds a certain permutation of a given number.\n" << endl;
    int n, k;
    cout << "Enter the number of natural numbers to consider: "; 
    cin >> n;
    cout << "Enter the permutation index to find: ";
    cin >> k;

    string res = findKthPermutation(n, k);

    cout << "\nThe " << k << "th permutation of " << n << " is " << res << "." << endl;

    cout << endl;

    return 0;
}

string findKthPermutation(int n, int k) {
    // Store final answer
    string ans = "";
 
    set<int> s;
 
    // Insert all natural number upto n in set
    for (int i = 1; i <= n; i += 1) s.insert(i);
 
    // Mark the first position
    auto itr = s.begin();
 
    // Subtracting 1 to get 0 based indexing
    k -= 1;
 
    for (int i = 0; i < n; i += 1) {
        int index = findFirstNumIndex(k, n - i);
 
        advance(itr, index);
        // `itr` now points to the number at index in set s
        ans += (to_string(*itr));
        // Remove current number from the set
        s.erase(itr);
 
        // We reset the itertor to beginning 
        itr = s.begin();
    }

    return ans;
}

int findFirstNumIndex(int &k, int n) {
    // First we need to find the index of the number
    // at first position of kth sequence of set of size n
    if (n == 1) return 0;

    n -= 1;
 
    int firstNumIdx;
    int partialFact = n;
 
    while (k >= partialFact && n > 1) {
        partialFact = partialFact * (n - 1);
        n -= 1;
    }
 
    // First position of the kth sequence will be
    // occupied by the number present at index = k / (n-1)!
    firstNumIdx = k / partialFact;
 
    k = k % partialFact;
 
    return firstNumIdx;
}
