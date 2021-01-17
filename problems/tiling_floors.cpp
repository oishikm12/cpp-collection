#include <iostream>
using namespace std;

int getTileConfigs(int);

int main() {
    /**
     * In order to get all possible configurations of tiles, we simply call
     * the function again after placing a tile in current slot
     */ 
    cout << "\nThis program finds out possible tile configs in a floor.\n" << endl;
    int width;
    cout << "Enter width of floor : ";
    cin >> width;

    int possiblities = getTileConfigs(width);

    cout << "\nThere are " << possiblities << " possible configurations." << endl;

    cout << endl;

    return 0;
}

int getTileConfigs(int pos) {
    // We simply recurse till we are at position 0 of floor
    if (pos == 0) return 1;

    // After placing current tile horizontally, we place next
    int nextPos = getTileConfigs(pos - 1);
    // We consider placing vertically if possible
    if (pos >= 4) nextPos += getTileConfigs(pos - 4);

    return nextPos;
}