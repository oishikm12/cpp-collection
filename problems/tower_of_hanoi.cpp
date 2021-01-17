#include <iostream>
using namespace std;

void towerForm(int, int&, char, char, char);

int main() {
    /**
     * In order to find the logical sequencing we simply call the same 
     * function recursively, swapping the destination of a ring such that
     * it always lands over a larger value
     */ 
    cout << "\nThis program builds a Tower of Hanoi.\n" << endl;
    int num;
    cout << "Enter the no. of rings to consider : ";
    cin >> num;

    int count = 0;
    cout << endl;
    towerForm(num, count, 'A', 'C', 'B');

    cout << "\nIt took " << count << " moves." << endl;

    cout << endl;

    return 0;
}

void towerForm(int num, int &count, char src, char dest, char mid) {
    // In each recursive call we swap the values of src dest & mid to
    // ensure that a smaller ring is always placed above a larger
    if (num == 0) return;

    // We move one from src to mid
    towerForm(num - 1, count, src, mid, dest);

    cout << "Move Disk #" << num << " from " << src << " to " << dest << "." << endl;
    count += 1;

    // We then move it from mid to dest
    towerForm(num - 1, count, mid, dest, src);
}