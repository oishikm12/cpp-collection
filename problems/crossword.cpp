#include <iostream>
#include <vector>
using namespace std;

vector<string> checkVertical(vector<string> board, string word, int x, int y);
vector<string> checkHorizontal(vector<string> board, string word, int x, int y);
void crossWords(vector<string> board, vector<string> &words, int idx);

int main() {
    /**
     * In order to solve a crossword puzzle, we use recursion to try every
     * possiblity of placing words from the very first cell
     */ 
    cout << "\nThis program finds out every possible solution to a crossword puzzle.\n" << endl;
    
    int size, num;

    cout << "Enter the size of the board : ";
    cin >> size;
    vector<string> board(size);
    cout << "Enter newline delimited grid of the board" << endl;
    for (int i = 0; i < size; i += 1) cin >> board[i];

    cout << "Enter the no. of words to place : ";
    cin >> num;
    vector<string> words(num);
    cout << "Enter newline delimited words to enter" << endl;
    for (int i = 0; i < num; i += 1) cin >> words[i];
    
    crossWords(board, words, 0);

    cout << endl;
    
    return 0;
}

vector<string> checkVertical(vector<string> board, string word, int x, int y) {
  // We will try to place the word, so we need to traverse its length
  for (int i = 0; i < word.size(); i += 1) {
    // We will only place the word if the current position is free
    // or has the current letter prefilled
    if (board[x + i][y] == '-' || board[x + i][y] == word[i]) {
      // We are traversing vertically, ie. row wise
      board[x + i][y] = word[i];
    } else {
      // We need the caller function to identify the current
      // configuration to be invalid
      board[0][0] = 'x';
      return board;
    }
  }
  
  return board;
}

vector<string> checkHorizontal(vector<string> board, string word, int x, int y) {
  // Traversing the words to be placed
  for (int i = 0; i < word.size(); i += 1) {
    // We will only place the word if the current position is free
    // or has the current letter prefilled
    if (board[x][y + i] == '-' || board[x][y + i] == word[i]) {
      // We are traversing horizontally, ie. col wise
      board[x][y + i] = word[i];
    } else {
      // Identifying the configuration to be invalid
      board[0][0] = 'x';
      return board;
    }
  }
  
  return board;
}

void crossWords(vector<string> board, vector<string> &words, int idx) {
  // If we have finished with filling all the words
  // We can print the GRID showing word placement
  if (idx == words.size()) {
    for (int i = 0; i < 10; i += 1) cout << board[i] << endl;
    cout << endl;
    return;
  }
  
  string word = words[idx];
  // Maxlen represents the maximum indices we can traverse
  // till the words can fit
  int maxLen = 10 - word.size();
  
  for (int i = 0; i < 10; i++) {
    // We can only go till maxLen trying to place the word
    for (int j = 0; j <= maxLen; j++) {
      vector<string> temp = checkVertical(board, word, j, i);
      // checking invalid configuration before recursing
      if (temp[0][0] != 'x') crossWords(temp, words, idx + 1);
    }
  }

  for (int i = 0; i < 10; i++) {
    // We can only go till maxLen trying to place the word
    for (int j = 0; j <= maxLen; j++) {
      vector<string> temp = checkHorizontal(board, word, i, j);
      // checking invalid configuration before recursing
      if (temp[0][0] != 'x') crossWords(temp, words, idx + 1);
    }
  }
}