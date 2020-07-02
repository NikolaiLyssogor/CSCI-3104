#include <iostream>
using namespace std;

/*
  This program uses merge sort to sort the given array and then does a constant-time
  index to find the kth lowest element. This version of merge sort was adapted from
  the one on Geeksforgeeks.org. We know that merge sort (and other divide-and-conquer
  algorithms like it) take O(nlog(n)) time, and that the space complexity is constant.

  Note: I wanted to make a function which only took the array and k as the inputs, and
  then use mergeSort() and merge() as helper functions to that in order to keep within
  the confines of the question. However, I ran in to some issues that prevented this method
  from working, and I didn't see the difference between that method and the one I ended
  up using as relevant enough to the learning goals to figure out a solution. The program
  as a whole accomplishes the desired outcome.
*/

void merge(int arr[], int low, int high, int mid) { // pass original array
  int i, j, k;
  // size of temp arrays
  int n1 = mid - low + 1;
  int n2 = high - mid;
  // temp arrays
  int arrLow[n1];
  int arrHigh[n2];

  // populate temp arrays
  for(i = 0; i < n1; i++) {
    arrLow[i] = arr[low + i];
  }
  for(j = 0; j < n2; j++) {
    arrHigh[j] = arr[mid + 1 + j];
  }

  i = 0;
  j = 0;
  k = low;

  // pick smallest value from each subarray at indices from which we are observing and add that to next index of original array
  while(i < n1 && j < n2) {
    if(arrLow[i] <= arrHigh[j]) {
      arr[k] = arrLow[i];
      i++;
    }
    else {
      arr[k] = arrHigh[j];
      j++;
    }
    k++;
  }

  // add remaining values to original array
  while(i < n1) {
    arr[k] = arrLow[i];
    i++;
    k++;
  }
  while(j < n2) {
    arr[k] = arrHigh[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int low, int high) { // parameters array to be sorted and indices corresponding to original array and kth smallest number
  if(low < high) {
    int mid = (low + high) / 2; // find midpoint of array
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, high, mid);
  }
}

int main() {
  int arr[8] = { 12, 11, 13, 5, 6, 7, 17, 2 };
  int k = 3;
  int len = *(&arr + 1) - arr;

  mergeSort(arr, 0, len - 1);

  cout << arr[k - 1] << endl;

  return 0;
}
