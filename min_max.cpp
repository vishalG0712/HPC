#include <iostream>
#include <omp.h>

using namespace std;

void simpleComputation(int a[], int n) {
    int min_val = a[0], max_val = a[0];
    int sum = 0;

    double start_time = omp_get_wtime(); // Start timing

    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (a[i] < min_val){
            min_val = a[i];
        }
        if (a[i] > max_val){
            max_val = a[i];
        }

        // Increase computational workload
        for (int j = 0; j < 100000; j++) {
            sum *= 1.001;
        }
    }

    double end_time = omp_get_wtime(); // End timing

    float avg = (sum) / n;

    cout << "\nSimple Computation Results:\n";
    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Time taken: " << (end_time - start_time) * 1000<< " milliseconds" << endl;
}

void parallelComputation(int a[], int n) {
    int min_val = a[0], max_val = a[0];
    int sum = 0;

    double start_time = omp_get_wtime(); // Start timing

    #pragma omp parallel for reduction(min: min_val) reduction(max: max_val) reduction(+: sum) schedule(static)
    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (a[i] < min_val){
            min_val = a[i];
        }
        if (a[i] > max_val){
            max_val = a[i];
        }

        // Increase computational workload
        for (int j = 0; j < 100000; j++) {
            sum *= 1.001;
        }
    }

    double end_time = omp_get_wtime(); // End timing

    float avg = (sum) / n;

    cout << "\nParallel Computation Results:\n";
    cout << "Minimum: " << min_val << endl;
    cout << "Maximum: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Time taken: " << (end_time - start_time) * 1000 << " milliseconds" << endl;
}

int main() {
    int a[1000], n;
    cout << "Enter the number of elements in array: ";
    cin >> n;

    cout << "\nEnter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    simpleComputation(a, n);
    parallelComputation(a, n);

    return 0;
}