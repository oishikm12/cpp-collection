#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * We use a sliding window, while keeping track of which letters have already
     * occured in order to either expand or contract the size and position of
     * our window
     */
    cout << "\nThis problem finds out maximum size unique substring in a word.\n" << endl;
    string inp;
    cout << "\nEnter the string to parse : ";
    cin >> inp;

    // Storing if we have visited a letter, and its latest position
    vector<int> visited(200, -1);

    // First letter has already occured at pos 0
    visited[inp[0]] = 0;
    int currLen = 1, maxLen = 1;

    for (int i = 1; i < inp.size(); i += 1) {
        int lastOccur = visited[inp[i]];

        // If we have not reached this letter before, or 
        // at least it is not part of current substring
        if (lastOccur == -1 || i - currLen > lastOccur) {
            currLen += 1;
            maxLen = max(maxLen, currLen);
        } else {
            // If this letter is recurring in current subsequence
            // then we have to store length of previous &
            // start a new sub sequence from after last occurence
            maxLen = max(maxLen, currLen);
            currLen = i - lastOccur;
        }

        visited[inp[i]] = i;
    }

    cout << "\nThe max possible unique substring is : " << maxLen << endl;

    cout << endl;
    
    return 0;
}
