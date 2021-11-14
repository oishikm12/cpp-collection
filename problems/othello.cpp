#include <iostream>
#include <vector>
using namespace std;

int findNextStep(int &, int &, vector<vector<int>> &, bool);
int evaluateBoard(vector<vector<int>> &, bool &);
vector<pair<int, int>> possibleMoves(vector<vector<int>> &, int);
vector<vector<int>> makeAMove(int, int, vector<vector<int>> &, int, bool);
void printBoard(vector<vector<int>> &);

int main() {
    /**
     * In order to find the next best move in the othello board, such
     * that the first player wins, we use MinMax to calculate all possible
     * outcomes, and then select the one leading to maximum score
     */
    cout << "\nThis program solves a Othello board, by finding the next best move for the first player.\n" << endl; 
    int sz;
    cout << "Enter grid size of board to consider: ";
    cin >> sz;

    vector<vector<int>> board(sz, vector<int>(sz, 0));
    cout << "Enter space seperated, line-delimited current state of the board, 0 being empty, 1 & 2 being players," << endl;
    for (auto &x : board) for (auto &y : x) cin >> y;

    int nextX, nextY;
    int score = findNextStep(nextX, nextY, board, true);
    cout << "\nIn order to get a score of " << score << ", the next move should be at index [" << nextX << ", " << nextY << "]" << endl;

    cout << endl;
    
    return 0;
}

int findNextStep(int &x, int &y, vector<vector<int>> &board, bool maximizerTurn) {
    // Checks if the game is completed, if so returns the score
    // of current player, otherwise applies minmax to all moves
    bool completed;
    int score = evaluateBoard(board, completed);

    // We print the state for this turn
    printBoard(board);
    // If the game is completed, we return the resulting score
    if (completed) return score;

    // The maximizer is Player 1, minimizer, Player 2
    int player = maximizerTurn ? 1 : 2;
    // Finding out all moves of current player
    vector<pair<int, int>> possiblities = possibleMoves(board, player);
    
    if (possiblities.size() == 0) {
        // This player has no turns possible hence we move on to 
        // opponent, while setting current move position to -1
        x = -1;
        y = -1;
        int dummyX, dummyY;
        return findNextStep(dummyX, dummyY, board, !maximizerTurn);
    }

    // Represents score possible this round, initially minimal if 
    // maximizers turn, vice versa for minimizer
    int bestScore = maximizerTurn ? INT_MIN : INT_MAX;

    // For each possible moves
    for (auto &[moveX, moveY] : possiblities) {
        // State of board after performing the given move
        // [isCheck] -> is false here because we are making the move, not just cheking
        vector<vector<int>> newBoard = makeAMove(moveX, moveY, board, player, false);

        int dummyX, dummyY;
        int currScore = findNextStep(dummyX, dummyY, newBoard, !maximizerTurn);
   
        if (maximizerTurn) bestScore = max(bestScore, currScore);
        else bestScore = min(bestScore, currScore);

        if (bestScore == currScore) {
            // This means that this is a valid move for the current player
            // since it is increasing the score for player
            x = moveX;
            y = moveY;
        }
    }

    return bestScore;
}

int evaluateBoard(vector<vector<int>> &board, bool &completed) {
    // Evaluates the board to find out wether minimizer or
    // maximizer is currently winning
    if (possibleMoves(board, 1).size() != 0 || possibleMoves(board, 2).size() != 0) {
        // There are possible moves yet, hence we cannot evaluate
        completed = false;
        return 0;
    }

    // Otherwise, the board is in terminal stage
    completed = true;
    // We use a counter to find out scores for each player
    // Empty = 0, PLayer 1 = 1, Player 2 = 2
    vector<int> cnt(3, 0);
    for (auto &x : board) for (auto &y : x) cnt[y] += 1;

    // The resulting value is score of Player 1 - Player 2
    return cnt[1] - cnt[2];
}

vector<pair<int, int>> possibleMoves(vector<vector<int>> &board, int player) {
    // Finds out all possible valid moves that the given player can make
    vector<pair<int, int>> moves;

    // Here we iterate over all possible moves in the board
    for (int i = 0; i < board.size(); i += 1) {
        for (int j = 0; j < board[i].size(); j += 1) {
            // There is already a player move here, so we
            // cannot make our move here
            if (board[i][j] != 0) continue;

            // If we cannot make a move at this place. then
            // we move onto next empty tile
            if (makeAMove(i, j, board, player, true).size() == 0) continue;

            // This is a valid move this player can make
            moves.push_back(make_pair(i , j));
        }
    }

    return moves;
}

vector<vector<int>> makeAMove(int x, int y, vector<vector<int>> &board, int player, bool isCheck) {
    // Here we determine if it is possible to actually make a move
    // By setting `isCheck` to true, we only evaluate the possiblity, not perform operations
    vector<vector<int>> newBoard = board;

    // From any given tile, flips can be made in 8 directions
    vector<pair<int, int>> possiblities = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    // Invalid condition
    if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size() || board[x][y] != 0) return {};
    bool movePossible = false;

    for (auto &[xStep, yStep] : possiblities) {
        int currX = x + xStep;
        int currY = y + yStep;
        int count = 0;

        while (currX >= 0 && currX < board.size() && currY >= 0 && currY < board[currX].size()) {
            // This represents a potentially valid config

            if (newBoard[currX][currY] == 0 ) {
                // This slot is currently empty, cannot flip
                break;
            } else if (newBoard[currX][currY] != player) {
                // Opposite player occupies this tile, can be flipped
                currX += xStep;
                currY += yStep;
                count += 1;
            } else {
                // Reached a tile with same color as player
                // If count is 0, no tiles could be flipped
                if (count != 0) {
                    // Otherwise we were able to flipsome tiles
                    movePossible = true;
                    // We simply wanted to check not apply changes
                    if (isCheck) return newBoard;
                    // If not checking, we place the current player at those tiles
                    while (count--) {
                        currX -= xStep;
                        currY -= yStep;
                        newBoard[currX][currY] = player; 
                    }
                    newBoard[x][y] = player;
                }
                break;
            }
        }
    }

    if (movePossible) return newBoard;
    else return {};
}

void printBoard(vector<vector<int>> &board) {
    cout << endl;
    for (auto &x : board) {
        for (auto &y : x) cout << y << ' ';
        cout << endl;
    }
    cout << endl;
}
