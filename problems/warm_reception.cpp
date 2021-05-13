#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    /**
     * In order keep a track of when the guest keep arriving
     * and leaving, we can use a hash array to store arrival and
     * departure times as well as free times
     */ 
    cout << "\nThis problem determines optimal chairs needed for an event\n" << endl;
    int n;
    cout << "Enter number of guests to expect: ";
    cin >> n;

    // Hash Map tracking 24 hours in minutes
    vector<int> time(2400);
    cout << "Enter space seperated line delimted arrival and departure time of guests." << endl;
    for (int i = 0; i < n; i += 1) {
        int start, end;
        cin >> start >> end;
        
        // In order to track arrival & departure we add 1 to arrival
        // and remove one after departure
        time[start] += 1;
        time[end + 1] -= 1;
    }

    // After all of activity, adding previous to next
    // will give us at any time how many maximum
    // guests were present
    for (int i = 1; i < 2400; i += 1) time[i] += time[i - 1];

    // We just need the max guest count to determine max
    // chairs needed at any time
    int maxChairs = *max_element(time.begin(), time.end());

    cout << "\nWe will need " << maxChairs << " chairs." << endl;

    cout << endl;
    
    return 0;
}
