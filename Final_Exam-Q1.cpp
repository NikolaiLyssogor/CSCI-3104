#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

/*
  Final Exam: Question 1

  You are given a list of jobs with start and end times. Assume that only one job can
  be executed at a time on a processor. Your task is to find out the minimum number of
  processors required so that the jobs are executed as soon as they arrive (no waiting
  time for a process). The input to your algorithm will be a list of tuples indicating the
  start and end times of the respective jobs. The output should be a number indicating the
  minimum number of processors required. Your algorithm should have a runtime of O(nlog(n)),
  where n is the number of jobs. Assume you do not have access to any auxiliary functions.
*/

int scheduleProcessors(vector<pair<int,int>> jobs) {
  // sort jobs by start time using iterative merge sort from GeeksforGeeks

  int curr_size; // size of current subarrays
  int left_idx; // starting index of subarray
  int right_idx; // ending index of subarray
  int mid; // midpoint of subarray
  int n = jobs.size();

  // subarrays start with size of 1 then grow as merged
  for(curr_size = 1; curr_size <= n - 1; curr_size = curr_size * 2) {
    // iterate over each of the subarrays
    for(left_idx = 0; left_idx < n - 1; left_idx += curr_size * 2) {

      // calculate midpoint of subarray
      if(left_idx + curr_size - 1 < n - 1)
        mid = left_idx + curr_size - 1;
      else mid = n - 1;

      // calculate ending index of subarray
      if(left_idx + (curr_size * 2) - 1 < n - 1)
        right_idx = left_idx + (curr_size * 2) - 1;
      else right_idx = n - 1;

      // merge subarrays (sorry for the mess)
      int i, j, k;
      int sizeLeft = mid - left_idx + 1;
      int sizeRight = right_idx - mid;

      // create subarrays
      pair<int,int> left[sizeLeft], right[sizeRight];

      // copy values into subarrays from array passed to function
      for(i = 0; i < sizeLeft; i++)
        left[i] = jobs[left_idx + i];
      for(j = 0; j < sizeRight; j++)
        right[j] = jobs[mid + j + 1];

        i = 0;
        j = 0;
        k = left_idx;

        // merge values back into the jobs array, sorting based on starting time
        while(i < sizeLeft && j < sizeRight) {
          if(left[i].first <= right[j].first) {
            jobs[k] = left[i];
            i++;
          }
          else {
            jobs[k] = right[j];
            j++;
          }
          k++;
        }

        // copy remaining values of left[] and right[], respectively, into jobs[]
        while(i < sizeLeft) {
          jobs[k] = left[i];
          i++;
          k++;
        }
        while(j < sizeRight) {
          jobs[k] = right[j];
          j++;
          k++;
        }
    }
  }


  // "assign" a processor to each job
  int processorAssignment[n];
  processorAssignment[0] = 1;
  int max = 1;

  // iterate over each job
  for(int i = 0; i < n; i++) {
    processorAssignment[i] = 1;
    // see if current job overlaps with previous jobs
    for(int j = 0; j < i - 1; j++) {
      // if jobs[i] overlaps jobs[j], another processor is needed for jobs[i]
      if(jobs[j].first < jobs[i].second) {
        processorAssignment[i] = processorAssignment[j] + 1;
        // update max processors needed
        if(processorAssignment[i] > max)
          max = processorAssignment[i];
      }
    }
  }
  return max;
}

int main() {
  // test case
  vector<pair<int,int>> jobs;

  jobs.push_back(make_pair(2, 10));
  jobs.push_back(make_pair(9, 11));
  jobs.push_back(make_pair(15, 18));
  jobs.push_back(make_pair(3, 4));
  jobs.push_back(make_pair(17, 19));
  jobs.push_back(make_pair(5, 13));

  cout << scheduleProcessors(jobs);

  return 0;
}
