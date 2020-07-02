#include <iostream>
using namespace std;

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
/*
  The algorithm here always pairs the left-most rabbit without a carrot
  with the left-most carrot remaining. This means we must sort the array
  of rabbits and carrots before pairing rabbits and carrots. Merge sort is
  used here which takes O(nlog(n)) time. We then iterate through the arrays
  again once to find which pairing takes the longest. This takes O(n) time. 
*/
int greedy(int rabbits[], int carrots[], int arrSize) {
  int longest = 0;

  for(int i = 0; i < arrSize; i++) {
    if(abs(rabbits[i] - carrots[i]) > longest) {
      longest = abs(rabbits[i] - carrots[i]);
    }
  }
  return longest;
}

int main() {
  int rabbits[8] = { 84, 15, 15, 161, 187, 9, 66, 1 };
  int carrots[8] = { 92, 103, 163, 119, 63, 117, 144, 172 };

  int arrSize = *(&rabbits + 1) - rabbits;

  mergeSort(rabbits, 0, arrSize - 1);
  mergeSort(carrots, 0, arrSize - 1);

  cout << greedy(rabbits, carrots, arrSize) << endl;

}
