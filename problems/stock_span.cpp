#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void printSpan(vector<int> &);

int main() {
    /**
     * Stock span is a problem where the value of previous days is just as
     * important as the current days value. As such a stack is used to keep
     * track of costs of previous days greater than that of current date.
     * At any time days to traverse is the difference between top & current
     */
    cout << "\nThis problem demonstrates the no. of cumulative days of stock price less or equal to current.\n" << endl;
    int days;
    cout << "\nEnter days to consider : ";
    cin >> days;

    vector<int> stocks(days);
    cout << "\nEnter space seperated stock prices for each day." << endl;
    for (int i = 0; i < days; i += 1) cin >> stocks[i];

    printSpan(stocks);

    cout << endl;
    
    return 0;
}

void printSpan(vector<int> &stocks) {
    // We store each cost & day as a pair in the stack
    stack<pair<int, int>> costs;
    vector<int> days(stocks.size());

    for (int i = 0; i < stocks.size(); i += 1) {
        int currPrice = stocks[i];

        // We pop till we reach the last element greater than current price
        while (!costs.empty() && costs.top().first < currPrice) costs.pop();
        
        // We save the days we can go back till
        int betterDays = costs.empty() ? 0 : costs.top().second;
        days[i] = i - betterDays;

        // Push it into the costs stack for next day
        costs.push(make_pair(currPrice, i));
    }

    for (auto &a : days) {
        cout << a << " ";
    }

    cout << endl;
}