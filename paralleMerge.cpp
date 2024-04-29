#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>
#include <cstdlib> 
using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m; 

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);
            #pragma omp section
            mergeSort(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}
void printVector(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n = 100; 
    vector<int> arr(n), arr_copy(n);

    srand(42);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
        arr_copy[i] = arr[i];
    }

    cout << "Original vector:" << endl;
    printVector(arr);
    double start = omp_get_wtime();
    mergeSort(arr_copy, 0, n - 1);
    double end = omp_get_wtime();
    cout << "\nParallel Merge Sort: " << end - start << " seconds" << endl;
    printVector(arr_copy);

    return 0;
}
