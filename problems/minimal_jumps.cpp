#include <iostream>
#include <vector>
using namespace std;

int minJumps(vector<int> &, int);

int main() {
    /**
     * In order for us to find out the minimal number of jumps required
     * to reach the last index we will simply iterate over the the list
     * updating the maximum reachable distance and the number of steps
     * needed to get there
     */
    cout << "\nThis program finds out the minimal number of jumps needed to reach the last index from first, given the value at each index represents jump distance.\n" << endl; 
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter space seperated elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> arr[i];

    int jumps = minJumps(arr, n);

    cout << "\nIt will take us " << jumps << " jumps to reach " << arr[n - 1] << " from " << arr[0] << "." << endl;

    cout << endl;

    return 0;
}

int minJumps(vector<int> &arr, int n) {
    // The starting point is the end, hence no jumps needed
    if (n <= 1) return 0;
    
    // If the first step allowed is 0, we cannot reach the end
    if (arr[0] == 0) return -1;
    
    // Stores the maximum reachable index at all times, initially
    // this is equal to distance allowed from first step
    // The second value is the minimal number of jumps needed to 
    // reach this position, and for first, its equal to 1
    pair<int, int> destination = make_pair(arr[0], 1);
    
    // Stores the number of steps we can take from any position
    int step = arr[0];
    
    for (int i = 1; i < n; i += 1) {
        // We have reached the destination index
        if (i == n - 1) return destination.second;
        
        // The maximum index we can reach should be current
        // added to how much we can jump from here
        destination.first = max(destination.first, i + arr[i]);
        // We used a step to get here
        step -= 1;
        
        if (step == 0) {
            // If we had no steps remaining, then we jumped 
            destination.second += 1;
            
            // Check if the current index/position or lesser index
            // is the maximum reach point from the previous indexes
            if (i >= destination.first) return -1;

            // Re-initialize the steps to the amount
            // of steps to reach maxReach from position i.
            step = destination.first - i;
        }
    }
    
}