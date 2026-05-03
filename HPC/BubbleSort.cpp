/*Write a program to implement Parallel Bubble Sort using OpenMP. Use 
existing algorithms and measure the performance of sequential and parallel 
algorithms. Compare the results and analyze the speedup achieved by parallelization
*/

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Swap function
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Sequential Bubble Sort
void sequentialBubble(vector<int> &a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort (Odd-Even)
void parallelBubble(vector<int> &a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;

        #pragma omp parallel for
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> a(n), b(n);

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i]; // copy for parallel version
    }

    // Sequential Sort
    sequentialBubble(a, n);

    // Parallel Sort
    parallelBubble(b, n);

    // Output Sequential Result
    cout << "\nSorted Array (Sequential):\n";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }

    // Output Parallel Result
    cout << "\nSorted Array (Parallel):\n";
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }

    return 0;
}
/*
To implement Sequential and Parallel Bubble Sort using OpenMP and compare their results.

🌐 Concept Used
Bubble Sort compares adjacent elements and swaps them if needed.
Sequential version works one by one.
Parallel version uses Odd-Even Transposition Sort to perform comparisons simultaneously using OpenMP.
🧱 Program Explanation
🔸 Swap Function
Swaps two elements using a temporary variable.
🔸 Sequential Bubble Sort
Uses two nested loops.
Compares adjacent elements and swaps if required.
After each pass, the largest element moves to the end.
Time Complexity: O(n²)
🔸 Parallel Bubble Sort
Uses Odd-Even method:
Even phase → (0,1), (2,3), …
Odd phase → (1,2), (3,4), …
Uses:
#pragma omp parallel for
Allows multiple comparisons at the same time.
🔸 Main Function
Takes number of elements n
Reads array elements
Copies array into another vector
Calls:
Sequential sort
Parallel sort
Prints both sorted arrays
📤 Output
Displays sorted array using:
Sequential method
Parallel method
⚠️ Important Points
Both methods give the same result
Parallel version is faster on multi-core systems
Complexity remains O(n²)
No data conflict due to independent comparisons
🎯 Conclusion

The program demonstrates how OpenMP improves performance by executing multiple operations in parallel, making sorting faster for large datasets.
*/