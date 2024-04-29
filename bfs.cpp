#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

int main() {
    int n, i, j, k, v, m, visited[10] = {0}, cost[10][10] = {0}, rare = 0, front = 0, qu[10] = {0};
    double start_time, end_time;

    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;
    cout << "\nEDGES\n";
    for (int k = 1; k <= m; k++) {
        cin >> i >> j;
        cost[i][j] = 1;
    }
    cout << "Enter the start vertex: ";
    cin >> v;
    cout << "Visited vertices: ";
    cout << v << " ";
    visited[v] = 1;
    k = 1;

    start_time = omp_get_wtime();

    // Sequential BFS
    while (k < n) {
        for (int j = 1; j <= n; j++) {
            if (cost[v][j] != 0 && visited[j] != 1) {
                qu[rare++] = j;
                visited[j] = 1;
            }
        }
        if (front < rare) {
            v = qu[front++];
            cout << v << " ";
            k++;
        }
    }

    end_time = omp_get_wtime();
    cout << "\nTime taken for sequential computation: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    start_time = omp_get_wtime();

    // Parallel BFS
    #pragma omp parallel
    {

        while (k < n) {
            #pragma omp for
            for (int j = 1; j <= n; j++) {
                if (cost[v][j] != 0 && visited[j] != 1) {
                    #pragma omp critical 
                    {
                        if (!visited[j]) {
                            qu[rare++] = j;
                            visited[j] = 1;
                        }
                    }
                }
            }
            #pragma omp single
            {
                if (front < rare) {
                    v = qu[front++];
                    cout << v << " ";
                    k++;
                }
            }
        }
    }

    end_time = omp_get_wtime();
    cout << "\nTime taken for parallel computation: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

    return 0;
}