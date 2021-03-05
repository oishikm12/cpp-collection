#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int largestRectangle(vector<int> &);

int main() {
    /**
     * Largest area under histogram is a problem which can be solved via divide
     * and conquere in nlog n time, however by using a stack we can solve this
     * problem in linear time. In order to do this we keep track of all elements
     * smaller than the current in a stack, the moment current becomes smaller,
     * we calculate area possible by the previous smallest height
     */
    cout << "\nThis problem demonstrates largest possible rectangle under given histogram.\n" << endl;
    int bars;
    cout << "\nEnter elements to consider : ";
    cin >> bars;

    vector<int> histogram(bars);
    cout << "\nEnter space seperated bar heights." << endl;
    for (int i = 0; i < bars; i += 1) cin >> histogram[i];

    int largest = largestRectangle(histogram);

    cout << "\nThe area of the largest rectangle is, " << largest << " units." << endl;

    cout << endl;
    
    return 0;
}

int largestRectangle(vector<int> &histogram) {
    // This will store all bars smaller than current
    stack<int> smaller;
    // Max area acquired
    int max_area = 0;
    // Top represents topmost element index, area being current area
    int top, area_top;

    int i = 0;
    while(i < histogram.size()) {
        if (smaller.empty() || histogram[smaller.top()] <= histogram[i]) {
            // Elements smaller than current
            smaller.push(i);
            i += 1;
        } else {
            // Backing up the current topmost element
            top = smaller.top();
            smaller.pop();

            // Area of top being the topmost element before current
            // multiplied by i if the stack is empty, else distance between
            // current and top twice before the current
            area_top = histogram[top] * (smaller.empty() ? i : i - smaller.top() - 1);

            max_area = max(max_area, area_top);
        }
    } 
    
    while (!smaller.empty()) {
        top = smaller.top();
        smaller.pop();

        area_top = histogram[top] * (smaller.empty() ? i : i - smaller.top() - 1);

        max_area = max(max_area, area_top);
    }

    return max_area;
}