#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

int A[1000000];
int Q[1000000];

int intro_sort(int* A, int* Q, int n, int ifqu);

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

void max_heapify(int* A, int i, int n) {
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int largest;
    if(L <= n && A[L] > A[i])
        largest = L;
    else 
        largest = i;
    if(R <= n && A[R] > A[largest])
        largest = R;
    if(largest != i) {
        int l = A[i];
        A[i] = A[largest];
        A[largest] = l;
        max_heapify(A, largest, n);
    }
    return;
}

void build_max_heap(int* A, int n) {
    for(int i = n/2; i >= 0; i--) 
        max_heapify(A, i, n);
    return;
}

void heap_sort(int* A, int n) {
    build_max_heap(A, n);
    for(int i = n; i > 0; i--){
        int ai = A[i];
        A[i] = A[0];
        A[0] = ai;
        n--;
        max_heapify(A, 0, n);
    }
    return;
}

int quick_sort(int* A, int n, int ifqu, int p, int r) {
    while(ifqu < 0) {
        if(p < r) {
            int i = p;
            int j = r + 1;
            int pivot = A[p];
            do {
                do i++; while(A[i] < pivot && i < r);
                do j--; while(A[j] > pivot && j > p);
                if(i < j) {
                    int ai = A[i];
                    A[i] = A[j];
                    A[j] = ai;
                }
            } while(i < j);
            int ap = A[p];
            A[p] = A[j];
            A[j] = ap;
            quick_sort(A, n, ifqu--, p, j-1);
            quick_sort(A, n, ifqu--, j+1, r);
        }
        return 1;
    }
    return 0;
}

int intro_sort(int* A, int* Q, int n, int ifqu) {
    if(n < 16) {
        insertion_sort(A, n, 1);
        return 1;
    }

    int q = quick_sort(Q, n, ifqu, 0, n);

    if(q == 0) {
        heap_sort(A, n);
        return 1;
    }

    return 0;
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

    for(int i = 0; i < k; i++)
        Q[i] = A[i];

    int ifqu = 2 * log(k);

    auto start = high_resolution_clock::now();
    int isA = intro_sort(A, Q, k - 1, ifqu);
    if(isA == 0) {
        for(int i = 0; i < k; i++)
            A[i] = Q[i];
    }
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */

    cout << "Intro sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}