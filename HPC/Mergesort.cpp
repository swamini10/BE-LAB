/*Write a program to implement Parallel Merge sort using OpenMP. Use 
existing algorithms and measure the performance of sequential and parallel 
algorithms. 
*/
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Merge function
void merge(vector<int> &a, int l, int mid, int r) {
    vector<int> temp;
    int i = l, j = mid + 1;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j])
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);
    }

    while (i <= mid)
        temp.push_back(a[i++]);

    while (j <= r)
        temp.push_back(a[j++]);

    for (int k = 0; k < temp.size(); k++)
        a[l + k] = temp[k];
}

// Sequential Merge Sort (used internally)
void sequentialMergeSort(vector<int> &a, int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;

        sequentialMergeSort(a, l, mid);
        sequentialMergeSort(a, mid + 1, r);

        merge(a, l, mid, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(vector<int> &a, int l, int r, int depth = 0) {
    if (l < r) {
        int mid = (l + r) / 2;

        if (depth < 4) {
            #pragma omp parallel sections
            {
                #pragma omp section
                parallelMergeSort(a, l, mid, depth + 1);

                #pragma omp section
                parallelMergeSort(a, mid + 1, r, depth + 1);
            }
        } else {
            sequentialMergeSort(a, l, mid);
            sequentialMergeSort(a, mid + 1, r);
        }

        merge(a, l, mid, r);
    }
}

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> b(n);

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    double start, end;

    // -------- Parallel Merge Sort --------
    start = omp_get_wtime();
    parallelMergeSort(b, 0, n - 1);
    end = omp_get_wtime();

    cout << "\nParallel Sorted Array:\n";
    for (int x : b)
        cout << x << " ";

    cout << "\nTime (Parallel): " << end - start << " sec\n";

    return 0;
}

/*
Algorithm: Parallel Merge Sort
Start
Input the number of elements n
Read n elements into array A
Call mergeSort(A, 0, n-1)
Function: mergeSort(A, start, end)
If start < end, then:
Find middle index:
mid = (start + end) / 2
Divide the array into two halves
Parallel Execution using OpenMP sections:
Sort left half → mergeSort(A, start, mid)
Sort right half → mergeSort(A, mid+1, end)
Merge the two sorted halves using merge() function
Function: merge(A, leftStart, leftEnd, rightStart, rightEnd)
Create a temporary array
Compare elements from both halves:
Copy smaller element into temporary array
Copy remaining elements (if any)
Copy sorted data back into original array
Repeat until entire array is sorted
Display the sorted array
Stop
🧠 Key Points (for viva)
Uses Divide and Conquer technique
Parallelism achieved using OpenMP sections
Time Complexity: O(n log n)
Faster than Bubble Sort for large inputs
*/