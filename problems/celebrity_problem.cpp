#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int celebrity(vector<vector<int>> &, int);

int main() {
    /**
     * In order to find out a potential candidate who is not known 
     * to anybody, we can use a stack to push every person in a stak
     * and then compare the top 2 to check if they know each other.
     * The person who does not know the other is pushed back into the
     * stack. In the end the person remaining should not know anyone else
     */ 
    cout << "\nThis program finds out a celebrity amidst a given number of guests at a party.\n" << endl;
    int n;
    cout << "Enter the number of people in the party: ";
    cin >> n;

    vector<vector<int>> guests(n, vector<int>(n, 0));
    for (int i = 0; i < n; i += 1) {
        cout << "Enter space seperated guests known by Guest #" << i << ", ending with -1:" << endl;
        int temp;
        cin >> temp;
        while (temp > -1 && temp < n) {
            guests[i][temp] = 1;
            cin >> temp;
        }
    }

    int celebIndex = celebrity(guests, n);

    if (celebIndex == -1) cout << "\nThere is no celebrity in this party." << endl;
    else cout << "\nGuest #" << celebIndex << " is the celebrity." << endl;

    cout << endl;

    return 0;
}

int celebrity(vector<vector<int>> &guests, int n)  {
    // We will use a stack to compare people with each other
    // to select the candidate most likely to be a celebrity
    stack<int> people;
    for (int i = 0; i < n; i += 1) people.push(i);
    
    while (people.size() > 1) {
        // Till we have only 1 guest left, we will pop the topmost
        // and the next guest and check if they dont know each other,
        // the one not knowing the other is the likely candidate
        int first = people.top();
        people.pop();
        int second = people.top();
        people.pop();
        
        // The first guest does not know, the second, hence a possible
        // celibrity, otherwise if the second guest does not know the
        // first, a possible celebrity, else none of them are
        if (guests[first][second] == 0) people.push(first);
        else if (guests[second][first] == 0) people.push(second);
    }
    
    if (people.empty()) return -1;
    
    int candidate = people.top();
    
    for (int i = 0; i < n; i += 1) {
        // In order to ensure that the selected candidate is the celebrity
        // we check wether every person knows the candidate & the candidate
        // knows no one else
        if (i == candidate) continue;       
        if (guests[candidate][i] == 1 || guests[i][candidate] == 0) return -1;
    }
    
    return candidate;
}