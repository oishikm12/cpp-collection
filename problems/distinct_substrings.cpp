#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int getSubCount(string &);

int main() {
    /**
     * Possible substrings of a string including empty substrings 
     * equals 2^n, inorder to find out distinct count, we have to 
     * simply subtract whenever a substring ends with a repeated
     * character, since whenever ending character is repeated, so 
     * are the possible substrings before it
     */ 
    cout << "\nThis program finds out the possible distinct substrings of a string.\n" << endl;
    string s;
    cout << "Enter the string whose distinct substring count to find: ";
    cin >> s;

    int count = getSubCount(s);

    cout << "\nThere are, " << count << " distinct possible substrings of " << s << "." << endl;

    cout << endl;

    return 0;
}

int getSubCount(string &s) {
    int n = s.size();

    // By maintaining a map we can tell wether we are reading repetations
    unordered_map<char, int> charMap;
    vector<int> count(n + 1);

    // Empty substring is a possiblity
    count[0] = 1; 

    // Each index of string represents the count
    // of substring ending with it
    for (int i = 1; i <= n; i += 1) {
        count[i] = 2 * count[i - 1];

        if (charMap.find(s[i - 1]) != charMap.end()) {
            // This represents a repetation, hence we subtract
            // the count of substrings being repeated
            count[i] -= count[charMap[s[i - 1]]];
        }

        charMap[s[i - 1]] = i - 1;
    }

    return count[n];
}