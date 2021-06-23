#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isPalindrome(string &);
vector<vector<string>> partition(string);
void recursivePartition(string, int, vector<string>, vector<vector<string>> &);

int main() {
    /**
     * In order to find all palindromic partitions of a string, we simply
     * use recursion and backtracking to check if given substring is palindromic
     * or not, and if so, remove that portion from the string and recurse
     * for next palindromic substring
     */ 
    cout << "\nThis program finds out all palindromic substrings in a given string.\n" << endl;
    string s;
    cout << "Enter the string to find substrings of: ";
    cin >> s;

    vector<vector<string>> substrings = partition(s);

    cout << "\nThe palindromic substrings of the word " << s << " are," << endl;
    for (auto &subs : substrings) {
        for (auto &sections : subs) cout << sections << ", ";
        cout << endl;
    }

    cout << endl;

    return 0;
}

bool isPalindrome(string &word) {
    // We simply create a copy of the given string and reverse it
    string temp = word;
    reverse(temp.begin(), temp.end());

    // For a palindromic string, its reverse is the same as it
    return temp == word;
}

vector<vector<string>> partition(string word) {
    int len = word.size();

    // We use a vector to store the palindromic subsections of a string
    vector<string> current;
    // A 2D vector is used to store all such different configurations
    // of that string
    vector<vector<string>> result;
    
    recursivePartition(word, len, current, result);
    
    return result;
}
    
void recursivePartition(string word, int len, vector<string> current, vector<vector<string>> &store) {
    for (int i = 1; i <= len; i += 1) {
        // Given a string of certain length, we simply use the index
        // to generate all possible substrings as prefix
        string prefix = word.substr(0, i);
        
        if (isPalindrome(prefix)) {
            // If the current word is indeed a palindrome, we push it
            // to current iteration of finding palindrome
            current.push_back(prefix);
            
            if (i == len) {
                // If we reached the end of string, this represents a successful
                // sequeunce of palindromic strings, and hence we push it into result
                store.push_back(current);
                return;
            }
            
            // We recurse to find the other possible palindromic substrings
            recursivePartition(word.substr(i), len - i, current, store);
            // After we are done, we remove, i.e. backtrack inserted prefix
            current.pop_back();
        }
    }
}
    
    