#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

int main() {
    /**
     * If we are to ensure that no successive characters can be the
     * same, we simply have to prepare count of characters and ensure
     * that when one is placed after a unique one, same characters do
     * not reapper, this can be done via Max Heap & pair of {char, frequency}
     */ 
    cout << "\nThis program finds out unique representation of a string in which same characters are not adjacent.\n" << endl;
    string s;
    cout << "Enter the string to reorganize: ";
    cin >> s;

    string ordStr = reorganizeString(s);

    if (ordStr == "") cout << "\nThe string could not be reorganized." << endl;
    cout << "\n" << s << " can be reorganzied into " << ordStr << " to prevent same characters from reappearing adjacent to each other." << endl; 

    cout << endl;

    return 0;
}

string reorganizeString(string s) {
    // We will be using a map to maintain character & frequency
    unordered_map<int, int> cnts;
    // We are also converting characters to their ASCII format
    // and pairing their frequencies
    for (char &c : s) cnts[c] += 1;

    // We will use a priority queue to sort elements which
    // appear most times
    priority_queue<pair<int, int>> pq;
    for (auto &p : cnts) pq.push(make_pair(p.second, p.first));

    string res;
    pair<int, int> top1, top2;

    while (!pq.empty()) {
        top1 = pq.top(); 
        pq.pop();

        // We add the first character to the resultant string
        res += top1.second;

        if (!pq.empty()) {
            top2 = pq.top(); 
            pq.pop();

            res += top2.second;
            // We add the subsequent elements, and similarly
            // readd them decreasing their counts by 1
            if (top2.first > 1) {
                pq.push(make_pair(top2.first - 1, top2.second));
            }
        }

        if (top1.first > 1) {
            pq.push(make_pair(top1.first - 1, top1.second));
        }
    }

    // Since we added each character only once in sequence
    // if there are any repetation, we cannot segregate them
    for (int i = 1; i < res.size(); i++) {
        if (res[i] == res[i - 1]) return "";
    }

    return res;
}