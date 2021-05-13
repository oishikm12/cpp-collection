#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int tripletSum(vector<int>&, int);

int main() {
    /**
     * In order to find each possible triplets, we select a single number 
     * from the list then iterate over the rest of the sorted list in a two
     * pointer approach such that one iterates from least, one from most
     */
    cout << "\nThis program finds out triplets that add up to a specific number\n" << endl;
    int n;
    cout << "Enter the size of list: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space delimited elements of the list" << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int target;
    cout << "Enter the target to achieve: ";
    cin >> target;

    int possiblities = tripletSum(arr, target);

    cout << "\nThere are " << possiblities << " possible triplets." << endl;

    cout << endl;

    return 0;
}

int tripletSum(vector<int>& input, int target) {
    // We need a sorted input so that we can use 2 pointer approach
    // where l value is <= r value
	sort(input.begin(), input.end());

    int countTriplet = 0;

    for (int i = 0; i < input.size() - 2; i += 1) {
        // l pointer starts after current element
        int l = i + 1;
        // r pointer always starts from last
        int r = input.size() - 1;

        while (l < r) {
            // We need to check wether sum matches required target
            int currSum = input[i] + input[l] + input[r];

            if (currSum < target) l += 1; // if sum is smaller
            else if (currSum > target) r -= 1; // if sum is greater
            else {    
                if (input[l] == input[r]) {
                    int cnt = r - l + 1;
                    // Should both the elements be the same, we need to choose
                    // 2 from a pool of possiblities, more specifically we need
                    // to figure how many ways to choose 2 from all
                    // nCr = n!/r!(n-r)! -> nC2 = n*(n-1)/2
                    countTriplet += (cnt * (cnt - 1) / 2); 
                    break;
                } else {
                    // Should both elements be different, we need to figure out
                    // how many times each element occurs. That way we can select
                    // one of each to find possible configurations
                    int l_cnt = l + 1;
                    int r_cnt = r - 1;
                    while (l_cnt <= r_cnt && input[l_cnt] == input[l]) l_cnt += 1;
                    while (r_cnt >= l_cnt && input[r_cnt] == input[r]) r_cnt -= 1;

                    // nC1 * nC1 = n * n
                    countTriplet += ((l_cnt - l) * (r - r_cnt)); 
                    l = l_cnt;
                    r = r_cnt;
                }
            } 
        }
    }

    return countTriplet;
}