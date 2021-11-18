#include <iostream>
#include <vector>
using namespace std;

vector<int> getLPSArray(string, int);

int main() {
    /**
     * In order to find out the longest prefix that resembles a certain
     * suffix, we will use two pointers, and an array to maintain count
     * of resembling characters upto that point, i.e. each time the digits
     * pointed to by both are the same, the counter is increased by one,
     * and the pointer moves to the next place, whereas if they dont, the
     * lagging pointer moves back to the length of the last matched subsequence
     */ 
    cout << "\nThis program finds out the longest prefix that resembles a certain portion of suffix in the string.\n" << endl;
    string s;
    cout << "Enter the string whose LPS to find: ";
    cin >> s;

    vector<int> lpsArr = getLPSArray(s, s.size());

    // We need to find the position in suffix till which the longest prefec is same
    int lpsPoint = s.size() - 1;
    while (lpsPoint != 0 && lpsArr[lpsPoint] == 0) lpsPoint -= 1;

    if (lpsPoint == 0) cout << "\nThere is no prefix which matches any subsequence of the suffix." << endl;
    else cout << "\nThe size of the longest prefix is " << lpsArr[lpsPoint] << ", and the string is: " << s.substr(0, lpsArr[lpsPoint]) << endl;

    cout << endl;

    return 0;
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