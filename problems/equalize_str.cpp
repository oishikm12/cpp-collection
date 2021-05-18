#include <iostream>
using namespace std;

int main() {
    /**
     * The thing to notice here is swapping is only optimal
     * if we are swapping adjacent elements, otherwise the cost
     * is the same is flipping all the elements
     */ 
    cout << "\nThis program tells us the minimum cost to transform one string of 0s & 1s to another.\n" << endl;
    string s1, s2;
    cout << "Enter the string to convert into: ";
    cin >> s1;
    cout << "Enter the string to convert from: ";
    cin >> s2;

    int cost = 0;

    // We will traverse the string and check each of them
    for (int i = 0; i < s1.size(); i += 1) {
        // The letters are same
        if (s1[i] == s2[i]) continue;

        // If we are swapping, we are fixing 2 places at cost of 1
        if (s1[i] != s1[i + 1] && s1[i + 1] != s2[i + 1]) i += 1;

        cost += 1;
    }

    cout << "\nThe cost required to convert one to another is : " << cost << endl;

    cout << endl;

    return 0;

}