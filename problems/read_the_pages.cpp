#include <iostream>
#include <vector>
using namespace std;

bool isValid(vector<int>&, int, int, int);
void binarySearchPages(vector<int>&, int, int);

int main() {
    /**
     * In order to find out the best possible distribution we use binary search
     * to find the most probable mid point such that the maximum sum of pages
     * is the minimal accross all readers. The task is to print this maximum
     * possible pages a student can read
     */
    cout << "\nThis program finds out pages to be read by each user.\n" << endl;
    int books, readers;
    cout << "Enter no. of books to consider : ";
    cin >> books;
    cout << "Enter no. of readers to consider : ";
    cin >> readers;

    vector<int> arr(books);

    cout << "Enter space seperated, pages in each book," << endl;
    for (int i = 0; i < books; i += 1) cin >> arr[i];

    binarySearchPages(arr, books, readers);

    cout << endl;

    return 0;
}

void binarySearchPages(vector<int> &arr, int books, int readers) {
    // In this searching pattern we will consider the book with max pages
    // to be our starting element, whereas the cumulitive sum of all pages
    // will be our ending point, there after its just binary + linear
    int mid, ans;
    int start = 0, end = 0;

    for (int i = 0; i < books; i += 1) {
        end += arr[i];
        if (arr[i] > start) start = arr[i];
    } 

    while (start <= end) {
        mid = (start + end) / 2;

        if (isValid(arr, books, readers, mid)) {
            // We need a more accurate answer if it exists so we continue
            // This is the same as finding a lower bound in binary search
            ans = mid;
            end = mid - 1;
        } else {
            // The above function only returns false, if the given mid value
            // results in more no. of students than the value of readers
            // hence we increase the start value
            start = mid + 1;
        }
    }

    cout << "\nThe maximum pages a student can read is : " << ans << endl;
}

bool isValid(vector<int> &arr, int books, int readers, int mid) {
    // We essentially add all the value less than mid, into one bucket
    // Once its filled, we increment students and continue filling
    // At the end of [arr] if the no. of students is more than readers
    // the condition fails
    int students = 1;
    int currentPages = 0;

    for (int i = 0; i < books; i += 1) {
        if (currentPages + arr[i] > mid) {
            currentPages = arr[i];
            students += 1;

            if (students > readers) return false;
        } else {
            currentPages += arr[i];
        }
    }

    return true;
}