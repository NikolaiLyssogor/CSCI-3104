#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iomanip>

using namespace std;


int numberGame(vector<int> board) {
  // declare DP array
  int n = board.size();
  int moves[n][n];
  memset(moves, 0, sizeof(moves[0][0]) * n * n);

  // base case where there's only one choice
  for(int i = 0; i < n; i++) {
    moves[i][i] = board[i];
  }

  // base case where there's two choices (take greedy option)
  for(int i = 0; i < n - 1; i++) {
    moves[i][i + 1] = max(board[i], board[i + 1]);
  }

  // third base case where there's three choices (also take greedy option)
  for(int i = 0; i < n - 2; i++) {
    moves[i][i + 2] = max(board[i], board[i + 2]);
  }

  // fill rest of DP array using recursive relationship
  // keep filling it in diagonally
  for(int j = 3; j < n; j++) {
    for(int i = 0; i < n - 3; i++) {
      // reference one to the left and one down
      if(moves[i + 1][i + j] < moves[i][i + j - 1])
        moves[i][i + j] = board[i];
      else
        moves[i][i + j] = board[j + i];
    }
  }

/*
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cout << setw(2) << moves[i][j] << " ";
    }
    cout << endl;
  }
*/

  // find solution by tracing back through the DP array
  int start = 0; // keep track of what the board looks like when tracing back
  int end = n - 1;
  int turns = 6;

  int maxVal = 0;
  pair<int,int> currIdx; // keeps track of where we are when tracing back
  currIdx.first = start;
  currIdx.second = end;
  bool my_turn = true; // keeps track of whose turn it is, assumes first player

  while(turns > 0) {
    if(my_turn) maxVal += moves[currIdx.first][currIdx.second];
    // if curr_choice is on left end then optimal choice for opponent is index below currIdx
    if(moves[currIdx.first][currIdx.second] == board[start]) {
      currIdx.first += 1;
      start++;
    }
    else {
      currIdx.second -= 1;
      end--;
    }
    my_turn = !my_turn;
    turns--;
  }


  return maxVal;
}

int main() {
  vector<int> b = { 11, 13, 8, 5, 15, 6 };

  cout << numberGame(b) << endl;

  return 0;
}
