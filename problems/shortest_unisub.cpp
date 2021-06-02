#include <iostream>
#include <vector>
using namespace std;

int getUniSubLength(int, int, string &, string &, vector<vector<int>> &);

int main() {
    /**
     * In order to find out wether an unique subsequence is possible
     * or not, all we have to do is consider 2 recursive solutions 
     * at each step, i.e. for each sequence of characters if the last
     * character is present in first and not in second. 
     */ 
    cout << "\nThis program finds out the shorest unique substring length between 2 strings.\n" << endl;
    string a, b;
    cout << "Enter the first string to find substring of: ";
    cin >> a;
    cout << "Enter the second string to compare with: ";
    cin >> b;

    vector<vector<int>> store(a.size(), vector<int>(b.size(), -1));
    int size = getUniSubLength(0, 0, a, b, store);

    cout << "\nThe shortest unique substring would be of size" << size << "." << endl;

    cout << endl;

    return 0;
}

int getUniSubLength(int posA, int posB, string &first, string &second, vector<vector<int>> &store) {
    // If we reached the end of first string, we could not
    // find a unique substring this round
    if (posA == first.size()) return 1e5;
    // If we reach the end of second string, this represents
    // a unique substring in first is found
    if (posB >= second.size()) return 1;

    // We previously found this
    if (store[posA][posB] != -1) return store[posA][posB];
    
    // We ignore the current letter in the first string
    // and then recurse to check if any shorter substring is present
    int excludingCurr = getUniSubLength(posA + 1, posB, first, second, store);
    
    // We are considering the current letter in first string
    // to be part of this substring, so we need to find where
    // this characters occurs in second
    int common;
    for (common = posB; common < second.size(); common += 1) {
        if (first[posA] == second[common]) break;
    }
    
    // This character is not in second, hence an unique substring is found
    if (common == second.size()) return 1;
    
    // We then try to find the next unique substring, and add
    // to it 1, representing the common starting character
    int includingCurr = 1 + getUniSubLength(posA + 1, common + 1, first, second, store);
    
    // The minimal size of both unique substrings is stored
    store[posA][posB] = min(excludingCurr, includingCurr);
    
    return store[posA][posB];
}