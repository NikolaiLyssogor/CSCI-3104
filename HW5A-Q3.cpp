#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int ROWS = 4;
const int COLS = 4;

// returns 1 if an index is 1, 0 otherwise
int DFS(int map[][COLS], bool visited[][COLS], int i, int j) {
  // return if given index has been visited already or is outside the map
  if(visited[i][j] == true || i < 0 || i > ROWS - 1 || j < 0 || j > COLS - 1)
    return 0;

  // return but mark as visited if the cell is valid but not part of an island
  if(map[i][j] == 0) {
    visited[i][j] = true;
    return 0;
  }

  // index passed is land, call DFS again for all cells adjacent to it
  if(map[i][j] == 1) {
    visited[i][j] = true;
    return 1 + DFS(map, visited, i, j + 1)
             + DFS(map, visited, i + 1, j + 1)
             + DFS(map, visited, i + 1, j)
             + DFS(map, visited, i + 1, j - 1)
             + DFS(map, visited, i, j - 1)
             + DFS(map, visited, i - 1, j - 1)
             + DFS(map, visited, i - 1, j)
             + DFS(map, visited, i - 1, j + 1);
  }
}


vector<int> findIslands(int map[][COLS]) {
  // have separate array which keeps track of visited cells
  bool visited[ROWS][COLS];
  memset(visited, false, sizeof(visited));

  // vector to keep track of discovered islands and their sizes
  vector<int> islands;

  for(int i = 0; i < ROWS; i++) {
    for(int j = 0; j < COLS; j++) {
      if(map[i][j] == 1 && visited[i][j] == false) { // found an island that hasn't been visited
        islands.push_back(DFS(map, visited, i, j));
      }
    }
  }

  return islands;
}

int main() {
  int map[ROWS][COLS] = {{ 1, 0, 0, 1 },
                         { 0, 1, 0, 1 },
                         { 0, 1, 0, 0 },
                         { 0, 1, 0, 1 }};

  vector<int> solution = findIslands(map);

  for(int i = 0; i < solution.size(); i ++) {
    cout << solution[i] << " ";
  }

  return 0;
}
