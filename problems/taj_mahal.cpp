#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getStall(vector<int> &);

int main() {
    /**
     * In order to find out which stall it is that we will be
     * we need to first ensure that the length of queue in at
     * least one stall is less than the no. of counters, otherwise
     * we will just keep switching in circles. After this we can
     * find out the stall via simple iteration
     */ 
    cout << "\nThis program finds out which stall we can get tickets from in a slding window.\n" << endl;
    int n;
    cout << "Enter the number of counters present: ";
    cin >> n;

    vector<int> counters(n);
    cout << "Enter space delimited length of queue at each counter" << endl;
    for (int i = 0; i < n; i += 1) cin >> counters[i];

    int pos = getStall(counters);

    cout << "\nWe will buy the ticket from stall no." << pos << "." << endl;

    cout << endl;

    return 0;
}

int getStall(vector<int> &counters) {
    // We first need to find outh the counter with least
    // people standing in the queue
    int n = counters.size();
    int leastQueue = *min_element(counters.begin(), counters.end());

    // After that we need to check if it exceeds the no. of
    // counters, and if so we subtract the amount rounded to
    // nearest last counter. This allows us to skip over rounds
    // during which we would simply traverse all the queues
    if (leastQueue > n) {
        int amt = leastQueue - (leastQueue % n);
        for (int i = 0; i < n; i += 1) counters[i] -= amt;
    }

    int pos = 0;
    bool found = false;

    // We will loop till we arrive at an empty counter
    while (!found) {
        // When a user leaves the queue, it becomes empty
        // if no other user is present
        int queueLen = max(counters[pos] - pos, 0);
        if (max(counters[pos] - pos, 0) == 0) {
            // The reason we subtract the position is because
            // each minute 1 person leaves the queue, the same
            // as the current stall no. we are at
            found = true;
            break;
        }
        // At the end of one round, every stall has finished
        // booking `n` person
        counters[pos] = max(counters[pos] - n, 0);
        pos = (pos + 1) % n;
    }

    return pos + 1;
}