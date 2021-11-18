#include <iostream>
#include <vector>
using namespace std;

vector<int> getLPSArray(string, int);
bool KMPSearch(string, string);

int main() {
    /**
     * KMP search uses the property of repeating subsequences in
     * the pattern being searched for to find the Longes Prefix Sum
     * This way when characters are not similar, we only need to 
     * travel back to last matching position of the searching pattern
     */ 
    cout << "\nThis program uses KMP Search to find out if a given string is a substring of another.\n" << endl;
    string input, pattern;
    cout << "Enter the string to search in: ";
    cin >> input;
    cout << "Enter the pattern to search for: ";
    cin >> pattern;

    bool isPresent = KMPSearch(input, pattern);

    if (isPresent) cout << "\nThe pattern `" << pattern << "` is present in `" << input << "`." << endl;
    else cout << "\nThe pattern `" << pattern << "` is not present in `" << input << "`." << endl;

    cout << endl;

    return 0;
}

bool KMPSearch(string text, string pattern) {
    int txtPtr = 0;
    int patPtr = 0;

    // By finding out the LPS of pattern, we know the repeating
    // subsequence in its prefix, and hence revert to last matching
    // position of the pattern, and not the beggining
    vector<int> lps = getLPSArray(pattern, pattern.size());

    while (txtPtr < text.size() && patPtr < pattern.size()) {
        if (text[txtPtr] == pattern[patPtr]) {
            // The characters match hence we move both forward
            txtPtr += 1;
            patPtr += 1;
        } else {
            // The characters dont match, hence we move the pattern pointer back
            if (patPtr != 0) patPtr = lps[patPtr - 1];
            else txtPtr += 1;
        }
    }

    // The entire pattern if traversed, the pattern is found
    if (patPtr == pattern.size()) return true;
    else return false;
}

vector<int> getLPSArray(string inp, int sz) {
    // We use a vector to keep track of the resembling character count in prefix
    // from each point in the string
    vector<int> store(sz, 0);

    // This pointer represents last resembling prefix subsection
    int backPtr = 0;
    // This pointer represents currently parsing character
    int frontPtr = 1;

    while (frontPtr < sz) {
        if (inp[backPtr] == inp[frontPtr]) {
            // These characters are the same, hence we store the value of backPtr + 1
            // at the location of frontPtr, to indicate how many characters match till that point
            store[frontPtr] = backPtr + 1;
            frontPtr += 1;
            backPtr += 1;
        } else {
            // These characters do not match, so we have to revert the backPtr, to a point
            // where it will, to do this, we move to backPtr - 1, and see the store value there
            // to find out till which character the subsequence was still matching, and move there
            if (backPtr == 0) {
                // The backPtr is at the start, i.e. no matching subsequence yet
                store[frontPtr] = 0;
                frontPtr += 1;
            } else {
                backPtr = store[backPtr - 1];
            }
        }
    }

    return store;
}