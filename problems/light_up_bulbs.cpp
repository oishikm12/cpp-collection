#include <iostream>
#include <vector>
using namespace std;

int main() {
    /**
     * Since we can toggle a series of bulbs in one go, with
     * minimal cost, our aim is to shift all off bulbs to one
     * end. In order to find out number of reversals / toggles
     * it will take to shift all to one end, we will check the
     * number of times 0 appears after 1
     */ 
    cout << "\nThis program finds out minimum cost to switch all lights to on position in a given sequence at minimum cost.\n" << endl;
    int n, revCost, togCost;
    cout << "Enter the number of bulbs to consider: ";
    cin >> n;
    cout << "Enter the cost to  the state of a subsequence of bulbs: ";
    cin >> revCost;
    cout << "Enter the cost to toggle the state of a subsequence of bulbs: ";
    cin >> togCost;

    vector<int> bulbs(n);
    cout << "Enter space delimited states of the bulbs," << endl;
    for (int i = 0; i < n; i += 1) cin >> bulbs[i];

    // If the bulbs start in off state, we need an op to toggle it
    int operations = bulbs[0] == 0 ? 1 : 0;
    // For each off state bulb that appears after on state, we need
    // an operation to either swap or toggle the sequence
    for (int i = 0; i < n - 1; i += 1) if (bulbs[i] == 1 && bulbs[i + 1] == 0) operations += 1;

    // Depending on whichever costs less, we will use that operation
    // In the end we will toggle all the bulbs on one side to on 
    int cost = operations == 0 ? 0 : operations - 1 * min(revCost, togCost) + togCost;

    cout << "\nThe minimum cost for this operation would be " << cost << "." << endl;

    cout << endl;

    return 0;
}