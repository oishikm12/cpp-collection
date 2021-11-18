#include <iostream>
#include <vector>
using namespace std;

vector<string> findPalindromes(string &);

int main() {
    /**
     * In order to find out all the palindromic subsequences we will
     * start from each character and then progressively move to its 
     * left and right to find out if they match. If they do this becomes
     * a palindrome, and the more characters that match, the longer
     * this palinromic subsequence becomes
     */ 
    cout << "\nThis program finds out how many palindromic subsequences are there in a string, and the length of the longest one\n" << endl;
    string s;
    cout << "Enter the string whose palindromic subsequences to find: ";
    cin >> s;

    vector<string> result = findPalindromes(s);

    int mx = 0;
    cout << "\nThe palindromic subsequences are," << endl;
    for (auto &x : result) {
        cout << x << ", ";
        mx = max(mx, (int)x.size());
    }
    cout << endl << "\nThe length of the longest subsequence is, " << mx << "." << endl;

    cout << endl;

    return 0;
}

vector<string> findPalindromes(string &inp) {
    // We use a vector to store all the possible palindromic substrings
    vector<string> result;

    int left, right;
    int len = inp.size();

    for (int i = 0; i < len; i += 1) {
        // First we consider a palindrome of odd length, wherein there is
        // a single element in center, and those on its either side match
        left = i;
        right = i;

        while (left >= 0 && right < len && inp[left] == inp[right]) {
            result.push_back(inp.substr(left, right - left + 1));
            left -= 1;
            right += 1;
        }

        // For a palindrome of even length, we consider two adjacent pointers
        // going in opposite directions, and every character they point match
        left = i;
        right = i + 1;

        while (left >= 0 && right < len && inp[left] == inp[right]) {
            result.push_back(inp.substr(left, right - left + 1));
            left -= 1;
            right += 1;
        }
    }

    return result;
}