#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

/*
  Final Exam: Question 4

  There are n rooms numbered from {1,2, ..n} in Williams Village. Each of the rooms
   has a teleportation device with a value v_i ∀i∈ {1,2, ....n}. The teleportation device
    placed in the room i with value v_i teleports to a room numbered (v_i%n) + 1. A room
    in Williams Village is said to be beautiful if you can get back to the room
    you started using the teleportation devices.  The task is to count the number
    of beautiful rooms in Williams Village.The input to your algorithm is the list
    of values associated with the teleportation device placed in the rooms.
    The output should be a number indicating the number of beautiful rooms.
*/

int beautifulRooms(vector<int> rooms) {
  int beauts = 0; // keeps track of beautiful rooms
  int n = rooms.size();
  int visited[n] = { 0 }; // all values initially zero
  bool flag = true; // sentinel variable
  int curr_room; // index of current room we're in

  // check if each room is beautiful
  for(int i = 0; i < n; i++) {
    // enter loop after first teleportation
    curr_room = (rooms[i] % n) + 1;

    // self-loop edge case
    if(curr_room == i + 1) {
      beauts++;
      flag = false;
    }

    while(flag == true) {
      // we've come back around to where we started
      if(curr_room == i + 1) {
        flag = false;
        beauts++;
      }
      // we're stuck in a loop i.e. room is not beautiful
      else if (visited[curr_room - 1] == 1) {
        flag = false;
      }
      // continue teleporting
      else {
        visited[curr_room - 1] = 1;
        curr_room = (rooms[curr_room - 1] % n) + 1;
      }
    }
    // reset visited array for next room
    memset(visited, 0, sizeof(visited));
    flag = true;
  }
  return beauts;
}

int main() {
  // test case 1
  vector<int> r1 = {2, 3, 4, 5};
  cout << beautifulRooms(r1) << endl;

  // test case 2
  vector<int> r2 = {1, 2, 3, 6};
  cout << beautifulRooms(r2) << endl;

  return 0;
}
