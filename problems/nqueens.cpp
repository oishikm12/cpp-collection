#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

bool place(vector<int>&, int, int);
void nqueen(vector<int>&, int, int);
void prettyPrint(vector<int>&);
void queenCount(int, int, int&);

// Unlike array counterpart, bitsets are considerably faster,
// they are 1 bit for each element ~ 0 or 1
bitset<64> cols, diag1, diag2;

int main() {
    /**
     * In order to get a plausible configuration of placing n queens on the
     * board we place a queen on a row then move on to place a queen in the
     * next row. We continue this, till we encounter a error, in which case
     * we backtrack and change positions of previous queens till an optimal
     * placemnt grid is achieved
     */ 
    cout << "\nThis program finds out positions of N - Queens.\n" << endl;
    int size, queens;
    cout << "Enter the size of chess board : ";
    cin >> size;
    cout << "Enter the number of queens to consider : ";
    cin >> queens;

    vector<int> board(size + 1, 0);

    nqueen(board, 1, queens);

    int num = 0;

    queenCount(0, size, num);

    cout << "\nThere are " << num << " possible board configurations." << endl;

    cout << endl;

    return 0;
}

void nqueen(vector<int> &board, int current, int queens) {
    // Here we traverse through all rows of the board
    for (int col = 1; col < board.size(); col += 1) {
        if (place(board, current, col)) {
            // If this column can accept a queen
            // NOTE - The number of the queen represents its row,
            // valuea at that index represents the col it is placed in
            board[current] = col;

            if (current == queens) {
                prettyPrint(board);
                cout << endl;
            } else nqueen(board, current + 1, queens);
        }
    }
}

bool place(vector<int> &board, int current, int col) {
    // Here we traverse through all columns of the given row
    for (int j = 1; j < current; j += 1) {
        // This ensures that not only are there no queens below or above
        // But also queens are absent from diagonals
        if (board[j] == col || abs(board[j] - col) == abs(j - current)) return false;
    }
    return true;
}

void prettyPrint(vector<int> &board) {
    for (int i = 1; i < board.size(); i += 1) {
        for (int j = 1; j < board.size(); j += 1) {
            if (board[i] == j) cout << i << " ";
            else cout <<  "* ";
        }
        cout << endl;
    }
}

void queenCount(int row, int size, int& ans) {
    // This is the base case where we have already placed all the queens
    if (row == size) {
        ans += 1;
        return;
    }

    for (int col = 0; col < size; col += 1) {
        // For each of the columns
        // cols bitset array represent all cols where a queen has been placed
        // diag1 bitset array represents all those diagonals where queen has been placed
        // while diag1 consideres left diagonal, diag2 considers right
        // NOTE: row + col or row - col, in a diagonal remains constant
        if (!cols[col] && !diag1[row - col + size - 1] && !diag2[row + col]) {
            cols[col] = diag1[row - col + size - 1] = diag2[row + col] = 1;
            queenCount(row + 1, size, ans);
            // Backtracking Undo
            cols[col] = diag1[row - col + size - 1] = diag2[row + col] = 0;
        }
    }
}