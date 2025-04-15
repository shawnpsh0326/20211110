//to compare sorting time

#include <iostream>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

int M[1000000];
int H[1000000];
int B[1000000];
int I[1000000];
int S[1000000];
int Q[1000000];

int L[1000000];
int R[1000000];

void quick_sort(int* A, int p, int r) {
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
        quick_sort(A, p, j-1);
        quick_sort(A, j+1, r);
    }
}

void selection_sort(int* A, int n) {
    if(n <= 1) return;
    int smallest = A[0];
    int si = 0;
    for(int i = 1; i < n; i++) {
        if(smallest > A[i]) {
            smallest = A[i];
            si = i;
        }
    }
    if(si != 0) {
        int a0 = A[0];
        A[0] = A[si];
        A[si] = a0;
    }
    selection_sort(A+1, n-1);
}

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

void bubble_sort(int* A, int n) {
    for(int i = 0; i < n; i++) {
        if(A[i] > A[i+1]) {
            int ai = A[i];
            A[i] = A[i+1];
            A[i+1] = ai;
        }
    }
    n--;
    if(n > 0)
        bubble_sort(A, n);
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

void merge_sort(int* A, int* L, int* R, int p, int r) {
    if(p < r) {
        int q = (p+r)/2;
        merge_sort(A, L, R, p, q);
        merge_sort(A, L, R, q+1, r);
        merge(A, L, R, p, q, r);
    }
    return;
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
        M[k] = a;
        k++;
    }

    for(int i = 0; i < k; i++){
        H[i] = M[i];
        B[i] = M[i];
        I[i] = M[i];
        S[i] = M[i];
        Q[i] = M[i];
    }
/*
    auto start3 = high_resolution_clock::now();
    bubble_sort(B, k-1);
    auto end3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(end3 - start3);
    cout << duration3.count() << " ";

    auto start4 = high_resolution_clock::now();
    insertion_sort(I, k-1, 1);
    auto end4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(end4 - start4);
    cout << duration4.count() << " ";

    auto start5 = high_resolution_clock::now();
    selection_sort(S, k);
    auto end5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(end5 - start5);
    cout << duration5.count() << " ";
*/
    auto start1 = high_resolution_clock::now();
    merge_sort(M, L, R, 0, k-1);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(end1 - start1);
    cout << duration1.count() << " ";

    auto start2 = high_resolution_clock::now();
    heap_sort(H, k-1);
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(end2 - start2);
    cout << duration2.count() << " ";

    auto start6 = high_resolution_clock::now();
    quick_sort(Q, 0, k-1);
    auto end6 = high_resolution_clock::now();
    auto duration6 = duration_cast<microseconds>(end6 - start6);
    cout << duration6.count() << " ";

    cout << endl;

    return 0;
}