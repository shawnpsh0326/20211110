#include <iostream>
#include <climits>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

int A[1000000];
int L[1000000];
int R[1000000];

void insertion_sort(int* A, int n, int c) {
    if(c <= n) {
        for(int i = c; i > 0; i--) {
            if(A[i] < A[i-1]) {
                int ai = A[i];
                A[i] = A[i-1];
                A[i-1] = ai;
            }
            else {
                insertion_sort(A, n, c+1);
                return;
            }
        }
        insertion_sort(A, n, c+1);
    }
    return;
}

void merge(int* A, int* L, int* R, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q; 

    for(int i = 0; i < n1; i++) 
        L[i] = A[p + i];
    for(int j = 0; j < n2; j++)
        R[j] = A[q + j + 1];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0;
    int j = 0;

    for(int k = p; k <= r; k++) {
        if(L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
    }

    return;
}

void tim_sort(int * A, int* L, int* R, int n) {
    for(int i = 0; i < n; i += 32) {
        insertion_sort(A + i, min(31, n - i), 1);
    }

    for(int i = 32; i < n; i = i * i) {
        for(int p = 0; p < n; p += 2 * i) {
            int q = min(p + i - 1, n - 1);
            int r = min(p + 2 * i - 1, n - 1);
            if(p < r)
                merge(A, L, R, p, q, r);
        }
    }
}

int main() {
    int input;
    cin >> input;
    if(input == 1)
        freopen("random.txt", "r", stdin);
    else if(input == 2)
        freopen("sorted.txt", "r", stdin);
    else if(input == 3)
        freopen("reverse.txt", "r", stdin);
    else if(input == 4)
        freopen("partially.txt", "r", stdin);
    else {
        cout << "error" << endl;
        return 1;
    }

    int a;
    int k = 0;
    while(cin >> a) {
        A[k] = a;
        k++;
    }

    auto start = high_resolution_clock::now();
    tim_sort(A, L, R, k-1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */
   
    cout << "Tim sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}