#include <iostream>
using namespace std;

bool check_diff(int x, int y) {
  if(abs(x - y) == 1 || abs(x - y) == 3 || abs(x - y) == 5)
    return true;
  else return false;
}

int abs_diff(int data[], int n) {
  // create DP array which holds # of elements in potential sequences and the last number in each potential sequence
  int history[n][2];

  for(int i = 0; i < n; i ++) {
    history[i][0] = 0;
    history[i][1] = 0;
  }

  // base case: data[0]
  history[0][0] = 1;
  history[0][1] = data[0];

  // fill DP array
  for(int i = 1; i < n; i++) { // loop over data
    for(int j = 0; j < i; j++) { // loop over stored subsequences
      if(check_diff(data[i], history[j][1])) {
        // append to existing subsequence
        history[j][0] += 1; // indicate another value has been added to the subsequence
        history[j][1] = data[i]; // remember that value for future comparisons
      }
    }
    // start new subsequence in next open slot
    history[i][0] = 1;
    history[i][1] = data[i];
  }

  // return solution
  int longest = 1;

  for(int i = 0; i < n; i++) {
    if(history[i][0] > longest)
      longest = history[i][0];
  }

  return longest;
}

int main() {
  int n = 10;
  int data[n] = { 10, 30, 5, 8, 27, 1, 4, 9, 14, 17 };

  cout << abs_diff(data, n) << endl;

  int m = 8;
  int data1[m] = { 10, 30, 6, 9, 27, 22, 20, 19 };

  cout << abs_diff(data1, m) << endl;

  return 0;
}
