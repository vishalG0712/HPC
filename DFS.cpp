#include <iostream>
#include <omp.h>

using namespace std;

int cost[10][10], i, j, k, n, m, stk[10], top, v, visited[10], visit[10];

int main() {
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;
    cout << "EDGES\n";
    for (k = 1; k <= m; k++) {
        cin >> i >> j;
        cost[i][j] = 1;
    }
    cout << "Enter starting vertex: ";
    cin >> v;
    cout << "Visited vertices: ";
    cout << v << " ";
    visited[v] = 1;
    k = 1;

    double start_time, end_time;

    // Sequential DFS
    start_time = omp_get_wtime();

    while (k < n) {
        for (j = n; j >= 1; j--) {
            if (cost[v][j] != 0 && visited[j] != 1) {
                if (!visited[j]) {
                stk[top++] = j;
                visited[j] = 1;
                }
            }
        }
        if (top > 0) {
            v = stk[--top];
            cout << v << " ";
            k++;
        }
    }

    end_time = omp_get_wtime();
    cout << "\nTime taken for sequential DFS: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    // Parallel DFS
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        while (k < n) {
            #pragma omp for
            for (j = n; j >= 1; j--) {
                if (cost[v][j] != 0 && visited[j] != 1) {
                    #pragma omp critical
                    {
                        if (!visited[j]) {
                            stk[top++] = j;
                            visited[j] = 1;
                        }
                    }
                }
            }
            #pragma omp single
            {
                if (top > 0) {
                    v = stk[--top];
                    cout << v << " ";
                    k++;
                }
            }
        }
    }

    end_time = omp_get_wtime();
    cout << "\nTime taken for parallel DFS: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    return 0;
}