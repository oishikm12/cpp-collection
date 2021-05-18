#include <iostream>
#include <vector>
using namespace std;

int winningStrat(vector<int> &);

int main() {
    /**
     * Given the fact that an element can be swapped at most
     * two times to reach its sorted position, all we have to 
     * check is wether the current element is two swaps away
     * from its sorted position according to index
     */ 
    cout << "\nThis program decides wether a winning strategy is possible by swapping any element at most twice to build a sorted sequence.\n" << endl;
    int n;
    cout << "Enter the number of players to consider: ";
    cin >> n;

    vector<int> players(n);
    cout << "Enter space seperated current position of players," << endl;
    for (int i = 0; i < n; i += 1) cin >> players[i];

    int isPossible = winningStrat(players);

    if (isPossible != -1) cout << "\nYes, the players can be sorted into a winning strategy with " << isPossible << " swaps." << endl;
    else cout << "\nNo, a winning strategy is not possible." << endl;

    cout << endl;

    return 0;
}

int winningStrat(vector<int> &players) {
    int n = players.size();

    // There is only 1 player, no swaps needed
    if (n <= 1) return 0;

    int cnt = 0;

    for (int i = 0; i < n; i += 1) {
        // Since we can only swap twice, if players are
        // more than 2 away from sorted position, we cannot swap
        if (abs(players[i] - (i + 1)) > 2) return -1;

        if (players[i] == i + 1) {
            // Players are already at their correct position
            continue;
        } else if (i < n - 1 && players[i + 1] == i + 1) {
            // Player is 1 swap away
            swap(players[i], players[i + 1]);
            cnt += 1;
        } else if (i < n - 2 && players[i + 2] == i + 1) {
            // Player is 2 swap away
            swap(players[i + 1], players[i + 2]);
            swap(players[i], players[i + 1]);
            cnt += 2;
        } else {
            // Player is too far away, strategy unsuccessfull
            return -1;
        } 
    }

    return cnt;
}