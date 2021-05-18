#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
    /**
     * In order to find out the maximum chocolates that we
     * can distribute we will make 2 passes, one from the front,
     * giving more to those who are greater to right, then a 
     * reverse pass giving more to those greater on the left
     */ 
    cout << "\nThis program finds out the maximum chocolates needed to distribute among children, given the one with more score gets more.\n" << endl;
    int n;
    cout << "Enter the number of students to consider: ";
    cin >> n;

    vector<int> students(n);
    cout << "Enter space seperated marks of students," << endl;
    for (int i = 0; i < n; i += 1) cin >> students[i];

    int minChoco = distributeChocolates(students);

    cout << "\nWe will need " << minChoco << " number of chocolates." << endl;

    cout << endl;

    return 0; 
}

int distributeChocolates(vector<int> &students) {
    int n = students.size();
    // Initialize with 1 since all must get 1 chocolates
    vector<int> dp(n, 1);
    dp[0] = 1;

    // First we check if current is greater than previous
    // if so we simply add 1 to whatever previous got
    for (int i = 1; i < n; i += 1) {
        if (students[i - 1] < students[i]) dp[i] = dp[i - 1] + 1;
    }

    // Here we check if current is greater than next
    // if so we compare if we currently have more or
    // we need to add 1 to whatever previous had
    for (int i = n - 2; i >= 0; i -= 1) {
        if (students[i + 1] < students[i]) dp[i] = max(dp[i], dp[i + 1] + 1);
    }
    
    // Sum is the total amount of chocolates needed at the end
    int sum = accumulate(dp.begin(), dp.end(), 0);
    
    return sum;
}