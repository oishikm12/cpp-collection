#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> longestConsecutiveIncreasingSequence(vector<int>&);

int main() {
    /**
     * In order to find the longest consequitive subsequence
     * we maintain an unordered set to find if the next consequitive
     * element is present in the array
     */ 
    cout << "\nThis program finds out longest Consecutive Increasing Sequence from a list\n" << endl;
    int n;
    cout << "Enter size of the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array." << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    vector<int> ans = longestConsecutiveIncreasingSequence(arr);

    for (auto &x: ans) cout << x << ' ';

    cout << endl;

    return 0;
}

vector<int> longestConsecutiveIncreasingSequence(vector<int> &arr) {
    // First we insert all the elements into the hash set
    unordered_set<int> hash;
    for (int i = 0; i < arr.size(); i += 1) hash.insert(arr[i]);
    
    vector<int> result(2);
    int bestSeq = 1;
    result[0] = arr[0];
    result[1] = arr[0];
    
    for (int i = 0; i < arr.size(); i += 1) {
        // We maintain longest sequence for each element
        int currSeq = 1;
        int currElem = arr[i];
        pair<int, int> currPair = make_pair(arr[i], arr[i]);
        
        while (hash.count(currElem + 1) == 1) {
            // By checking if the next element is present in the hash
            // set, we find out max increasing sequence from current
            currElem += 1;
            currSeq += 1;
            currPair.second = currElem;
        }
        
        // If the current sequence is longer, we change result
        if (currSeq > bestSeq) {
            bestSeq = currSeq;
            result[0] = currPair.first;
            result[1] = currPair.second;
        }
    }
    
    // This represnts the sitution where the substring consists of only 1 element
    if (result[0] == result[1]) result.pop_back();
    
    return result;
}