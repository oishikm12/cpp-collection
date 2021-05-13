#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isSortable(vector<int> &);

int main() {
    /**
     * In order to find out wether we can sort the skills,
     * we can start traversing from the end, where if the current
     * skill is smaller then we swap with front, else we swap
     * with next. Accordingly we move the index as much as needed
     */ 
    cout << "\nThis problem checks if it is possible to sort a list of skill points\n" << endl;
    int n;
    cout << "Enter the number of skill holders: ";
    cin >> n;

    vector<int> skills(n);
    cout << "\nEnter space seperated skill points to consider." << endl;
    for (int i = 0; i < n; i += 1) cin >> skills[i];

    bool isPossible = isSortable(skills);

    if (isPossible) cout << "\nThis skill-set can be sorted." << endl;
    else cout << "\nThis skill-set cannot be sorted." << endl;

    cout << endl;

    return 0;
}

bool isSortable(vector<int> &skills) {
    // We will start traversing from the last element
    int n = skills.size();
    int idx = n - 1;

    while(idx > 0 && idx < n) {
        // If the current element is smaller than previous
        // and their abs diff is 1, then we can swap them
        if (skills[idx] < skills[idx - 1] && abs(skills[idx] - skills[idx - 1]) == 1) {
            swap(skills[idx], skills[idx - 1]);
        }

        // After swapping we check if the new element currently
        // here is greater than next, if so we move forward else
        // we move to the end
        if (idx < n - 1 && skills[idx] > skills[idx + 1] && abs(skills[idx] - skills[idx + 1]) == 1) {
            idx += 1;
        } else {
            idx -= 1;
        }
    }

    // If after our swaps the list becomes sorted, we return true
    if (is_sorted(skills.begin(), skills.end())) return true;
    return false;
}