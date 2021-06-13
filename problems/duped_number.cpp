#include <iostream>
#include <vector>
using namespace std;

int findRepeated(vector<int> &);

int main() {
    /**
     * In order to find the duplicated element inside a certain continious
     * range, we simply need to traverse the list with two pointers, one
     * slow and one fast, treating the value at each position the next index,
     * since there exists a duplicate, the pointers are bound the meet.
     * Further we can use FLoyd's Cycle for LL on this list to find it
     */
    cout << "\nThis program finds a duplicate element in a contigious stream of numbers.\n" << endl;
    int n;
    cout << "Enter the number of elements to consider: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter space seperated continious elements of the array," << endl;
    for (int i = 0; i < n; i += 1) cin >> nums[i];

    int duped = findRepeated(nums);

    cout << "\nIn a stream of continious numbers, " << duped << " appears multiple times." << endl;

    cout << endl;

    return 0;
}

int findRepeated(vector<int> &nums) {
    // Base case, minimum size must be 2
    if (nums.size() <= 1) return -1;

    // Two pointers, slow starts from the first element,
    // fast starts from the element next to it
    int slow = nums[0];
    int fast = nums[nums[0]];

    while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }

    // Once the two iterators meet, we need to find out
    // the element they meet at, which in turn will be
    // the duplicate element
    slow = 0;

    // We do this by resetting the slow pointer to the first
    // element and iterating one step at a time till they meet
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return slow;
}