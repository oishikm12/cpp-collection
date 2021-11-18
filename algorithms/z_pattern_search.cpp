#include <iostream>
#include <vector>
using namespace std;

void searchString(string, string);
void buildZArr(string, vector<int> &);

int main() {
    /**
     * In order to find out how many times a pattern repeats in a string
     * in linear time, we will use Z-Algorithm which uses an auxillary 
     * array to store how much the current substring resembles that of the
     * prefix of the string itself. It does this by maintaining L & R
     * pointers that track how much of a string matches the prefix
     */ 
    cout << "\nThis program calculates occurances of a pattern in a string.\n" << endl;
    string text, pattern;

    cout << "Enter the string in which to search: ";
    cin >> text;
    cout << "Enter the pattern to search for: ";
    cin >> pattern;

    searchString(text, pattern);

    cout << endl;

    return 0;
}

void searchString(string text, string pattern) {
    // Since Z Pattern finding, matches each index with that of the 
    // prefix, we place the pattern to find in front of the string itself
    string zForm = pattern + "$" + text;
    // This array serves as the counter for how many characters match with prefix
    vector<int> zArr(zForm.size());

    buildZArr(zForm, zArr);

    for (int i = 0; i < zArr.size(); i += 1) {
        // At any given point if the number of matching characters is the same as prefix till
        // our delimiter symbol ~ $, this would indicate that a pattern match is found
        if (zArr[i] != pattern.size()) continue;
        cout << "\nA match was found at index " << i - pattern.size() - 1 << endl;
    }
}

void buildZArr(string zForm, vector<int> &zArr) {
    int lPtr = 0;
    int rPtr = 0;

    int len = zForm.size();
    for (int i = 1; i < len; i += 1) {
        if (i > rPtr) {
            // We are currently at an index which has not been
            // traversed before, hence Z does not exist
            lPtr = i;
            rPtr = i;

            // Now we simply check how many characters match with prefix
            // Accordingly, rPtr is incremented
            while (rPtr < len && zForm[rPtr - lPtr] == zForm[rPtr]) rPtr += 1;

            zArr[i] = rPtr - lPtr;
            // Since rPtr is currently at non matching character, we decrement 
            // it to point to last matching char of prefix
            rPtr -= 1;
        } else {
            // We have to calculate if the length of matching string exceeds L - R
            // range, hence we calculate i + previously matching length from this char
            if (i + zArr[i - lPtr] <= rPtr) {
                // This index already falls inside L - R, range hence their Z 
                // value has already been calculated as part of prefix, hence we copy it
                zArr[i] = zArr[i - lPtr];
            } else {
                // This means that matching prefix part is longer than L - R 
                // range, and hence their Z values need to be calculated
                lPtr = i;

                // Setting rPtr to i - 1, will result in re-traversal of pattern string,
                // hence we repeat the steps instead of looping
                while (rPtr < len && zForm[rPtr - lPtr] == zForm[rPtr]) rPtr += 1;

                zArr[i] = rPtr - lPtr;
                rPtr -= 1;
            }
        }
    }
}