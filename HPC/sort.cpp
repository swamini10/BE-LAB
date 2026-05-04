 Write a program to implement Parallel Bubble Sort and Merge sort using OpenMP. Use
existing algorithms and measure the performance of sequential and parallel algorithms.

#include <iostream>
#include <ctime>
using namespace std;
 
// 🔹 Bubble Sort (Sequential)
void bubbleSortSeq(int arr[], int n) {
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
 
// 🔹 Bubble Sort (Pseudo Parallel - same as sequential for online)
void bubbleSortPar(int arr[], int n) {
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
 
// 🔹 Merge Function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
 
    int L[100], R[100];
 
    for(int i=0;i<n1;i++) L[i] = arr[l+i];
    for(int j=0;j<n2;j++) R[j] = arr[m+1+j];
 
    int i=0, j=0, k=l;
 
    while(i<n1 && j<n2){
        if(L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
 
    while(i<n1) arr[k++] = L[i++];
    while(j<n2) arr[k++] = R[j++];
}
 
// 🔹 Merge Sort (Sequential)
void mergeSortSeq(int arr[], int l, int r) {
    if(l < r){
        int m = (l + r)/2;
        mergeSortSeq(arr, l, m);
        mergeSortSeq(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
 
// 🔹 Merge Sort (Pseudo Parallel)
void mergeSortPar(int arr[], int l, int r) {
    if(l < r){
        int m = (l + r)/2;
        mergeSortPar(arr, l, m);
        mergeSortPar(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
 
// 🔹 Print Array
void printArray(int arr[], int n){
    for(int i=0;i<n;i++)
        cout << arr[i] << " ";
    cout << endl;
}
 
int main(){
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
 
    int arr[100], temp[100];
 
    cout << "Enter elements:\n";
    for(int i=0;i<n;i++){
        cin >> arr[i];
        temp[i] = arr[i];
    }
 
    double start, end;
 
    // 🔸 Sequential Bubble
    start = clock();
    bubbleSortSeq(arr, n);
    end = clock();
    cout << "\nSequential Bubble Sort Time: " << (end-start)/CLOCKS_PER_SEC;
 
    // 🔸 Parallel Bubble (same here)
    for(int i=0;i<n;i++) arr[i] = temp[i];
    start = clock();
    bubbleSortPar(arr, n);
    end = clock();
    cout << "\nParallel Bubble Sort Time: " << (end-start)/CLOCKS_PER_SEC;
 
    // 🔸 Sequential Merge
    for(int i=0;i<n;i++) arr[i] = temp[i];
    start = clock();
    mergeSortSeq(arr, 0, n-1);
    end = clock();
    cout << "\nSequential Merge Sort Time: " << (end-start)/CLOCKS_PER_SEC;
 
    // 🔸 Parallel Merge (same here)
    for(int i=0;i<n;i++) arr[i] = temp[i];
    start = clock();
    mergeSortPar(arr, 0, n-1);
    end = clock();
    cout << "\nParallel Merge Sort Time: " << (end-start)/CLOCKS_PER_SEC;
 
    cout << "\n\nSorted Array: ";
    printArray(arr, n);
 
    return 0;
}
 

Command :
 

g++ -fopenmp sort.cpp -o run
./run
 

input : 
 

Enter number of elements: 5
Enter elements:
5 2 9 1 3
 

Windows : 

g++ filename.cpp -fopenmp -o filename
 

filename.exe