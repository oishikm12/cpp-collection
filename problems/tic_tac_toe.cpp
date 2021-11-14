// Optimal Move in Tic Tac Toe
// Send Feedback
// Given a state of 3*3 Tic Tac Toe Board and two players 'x' and 'o', find the best optimal move possible for player with the next turn, specifying their row and column.
// Consider yourself to be 'x' and computer to be 'o'.
// Note: If there are more than one ways for 'x' to win the game from the given board state, the optimal move is the one where we have to make lesser number of moves to win the game.
// Input Format:
// First line of input contains integer N, representing the number of given states of board.
// Next N lines contain row number, column number and player name('x' or 'o'), space separated.
// Output Format:
// The first line of output contains the ultimate result of the game as follows:
// "Player_name" Wins. If no one wins, print Draw 
// The second line of output contains 
// (Total number of moves left) row: (Row Number) col: (Column Number)
// Sample Input 1:
// 4
// 0 0 x
// 0 1 o
// 0 2 x
// 1 1 o
// Sample Output 1:
// Draw
// 5 row: 2 col: 1
// Sample Input 2:
// 4
// 0 0 o
// 2 0 x
// 2 2 o
// 2 1 x
// Sample Output 2:
// o Wins
// 1 row: 1 col: 1
#include <iostream>
#include <vector>
using namespace std;

void findBestMove(vector<string> &, char);
pair<int, int> minimax(vector<string> &, int, bool);
int evaluate(vector<string> &);
bool hasMovesLeft(vector<string> &);

int main() {
    /**
     * In order to find out which player wins in a game of tic tac toe
     * we will use min-max to find out best possible move and score
     */ 
    cout << "\nThis program finds out the best move to win a game of tic-tac-toe.\n" << endl;

    vector<string> board(3);
    cout << "Enter space seperated line delimited state of the board with _ for unplayed tiles," << endl;
    for (auto &x : board) cin >> x;

    char player = 'x';
    cout << "Enter whose turn is next, `x` or `o`: ";
    cin >> player;

    // Accounitng for any mis-input
    player = player == 'x' ? 'x' : 'o';

    findBestMove(board, player); 

    cout << endl;

    return 0;
}

void findBestMove(vector<string> &board, char player) {
    // We will consider a move by X as maximizing & play by O as minimizing
    bool isMax = player == 'x';
    int bestVal = isMax ? -1000 : 1000;
    pair<int, int> bestMove = {-1, -1};

    // To store the number of moves to win
    int moves;

    // Traversing all the cell, evaluating minimax for all empty cells and
    // returnming the cell with optimal value
    for (int i = 0; i < board.size(); i += 1) {
        for (int j = 0; j < board[i].size(); j += 1) {
            char cell = board[i][j];
            // We only perform minimax if the cell is empty
            if (cell != '_') continue;

            // Make the move
            cell = player;
            // Then compute the evaluation of this move, i.e. computing opponents move
            auto [newVal, newMoves] = minimax(board, 1, !isMax);
            // Then undo the move
            cell = '_';

            // If the curr move is better than the best, then we update 
            if ((isMax && newVal > bestVal) || (!isMax && newVal < bestVal)) {
                bestMove = {i, j};
                bestVal = newVal;
                moves = newMoves;
            }
        }
    }

    if (bestVal > 0) cout << "\nPlayer X wins this game with " << moves << " moves" << endl;
    else if (bestVal < 0) cout << "\nPlayer O wins this game with " << moves << " moves" << endl;
    else cout << "\nAfter " << moves << " moves, the game ends in draw" << endl;

    cout << "\nThe move to make this possible is [" << bestMove.first << ", " << bestMove.second << "]" << endl;
}

pair<int, int> minimax(vector<string> &board, int depth, bool isMax) {
    // Here we recursively calculate the state of board given current move
    // as to who wins. Further to prevent incorrect patterns we use depth, i.e
    // winning with less moves is preferrable to winning with more
    int score = evaluate(board);

    // If the maximizer wins, return their score
    if (score == 10) return {score - depth, depth};
    // if the minimizer wins, return their score
    if (score == -10) return {score + depth, depth};
    // Otherwise if there are no moves left, its a tie
    if (!hasMovesLeft(board)) return {0, depth};

    pair<int, int> best = {isMax ? -1000 : 1000, 0};

    for (auto &row : board) {
        for (auto &cell : row) {
            // We only consider if the cell is not empty
            if (cell != '_') continue;

            // We make the move, and then call minimax recursively
            // & choose the best value
            if (isMax) {
                cell = 'x';
                best = max(best, minimax(board, depth + 1, !isMax));
            } else {
                cell = 'o';
                best = min(best, minimax(board, depth + 1, !isMax));
            }
            // And then undo those moves
            cell = '_';
        }
    }

    return best;
}

int evaluate(vector<string> &board) {
    char maximizer = 'x';
    char minimizer = 'o';

    // Checking rows for victory
    for (int row = 0; row < 3; row += 1) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == maximizer) return 10;
            else if (board[row][0] == minimizer) return -10;
        }
    }

    // Checking columns for victory
    for (int col = 0; col < 3; col += 1) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == maximizer) return 10;
            else if (board[0][col] == minimizer) return -10;
        }
    }

    // Checking diagonals for victory
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        if (board[1][1] == maximizer) return 10;
        else if (board[1][1] == minimizer) return -10;
    }

    // Otherwise there are no possible winning moves yet, or draws only
    return 0;
}

bool hasMovesLeft(vector<string> &board) {
    // If there exists even one empty cell then, there are more possible moves
    for (auto &row : board) for (auto &cell : row) if (cell == '_') return true;
    return false;
}