//to compare sorting time

#include <iostream>
#include <climits>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

int T[1000000];
int C[1000000];
int COM[1000000];
int TO[1000000];
int I[1000000];

int L[1000000];
int R[1000000];
int Q[1000000];

//intro

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

//tournament

void tree(int*A, int n, int a) {
    
    for(int i = a - 2; i >= 0; i--) {
        if(T[2 * i + 1] < T[2 * i + 2])
            T[i] = T[2 * i + 1];
        else
            T[i] = T[2 * i + 2];
    }

    int in = 0;
    while(in < a - 1) {
        if(T[2 * in + 1] == T[0])
            in = 2 * in + 1;
        else
            in = 2 * in + 2;
    }

    T[in] = INT_MAX;

    return;
}

void tournament_sort(int* A, int n) {
    int a = 1;
    for(int i = 0;; i++) {
        a = 1;
        for(int j = 0; j < i; j++)
            a *= 2;
        if(a > n)
            break;
    }

    for(int i = a - 1; i < 2 * a - 1; i++) {
        if(i < a - 1 + n)
            T[i] = A[i - a + 1];
        else
            T[i] = INT_MAX;
    }

    int ai = 0;
    for(int i = 0; i < n; i++) {
        tree(A, n, a);
        A[ai] = T[0];
        ai++;
    }    
    return;
}

//comb

void comb_sort(int* A, int n, int g) {
    for(int i = 0; i + g < n; i++) {
        if(A[i] > A[i+g]) {
            int ai = A[i];
            A[i] = A[i+g];
            A[i+g] = ai;
        }
    }
    g /= 1.3;
    if(g > 0)
        comb_sort(A, n, g);
    return;
}

//cocktail

void cocktail_shaker_sort(int* A, int l, int r) {
    int s = 0;
    for(int i = l; i < r; i++) {
        if(A[i] > A[i+1]) {
            int ai = A[i];
            A[i] = A[i+1];
            A[i+1] = ai;
            s = 1;
        }
    }
    r--;
    for(int i = r; i > l; i--) {
        if(A[i] > A[i+1]) {
            int ai = A[i];
            A[i] = A[i+1];
            A[i+1] = ai;
            s = 1;
        }
    }
    l++;
    if(s)
        cocktail_shaker_sort(A, l , r);
    return;
}

//tim

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
        T[k] = a;
        k++;
    }

    for(int i = 0; i < k; i++){
        C[i] = T[i];
        COM[i] = T[i];
        TO[i] = T[i];
        I[i] = T[i];
    }

    auto start3 = high_resolution_clock::now();
    tim_sort(T, L, R, k-1);
    auto end3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(end3 - start3);
    cout << duration3.count() << " ";
/*
    auto start4 = high_resolution_clock::now();
    cocktail_shaker_sort(C,0, k-1);
    auto end4 = high_resolution_clock::now();
    auto duration4 = duration_cast<microseconds>(end4 - start4);
    cout << duration4.count() << " ";

    auto start5 = high_resolution_clock::now();
    comb_sort(COM, k, k);
    auto end5 = high_resolution_clock::now();
    auto duration5 = duration_cast<microseconds>(end5 - start5);
    cout << duration5.count() << " ";

    auto start1 = high_resolution_clock::now();
    tournament_sort(TO, k);
    auto end1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(end1 - start1);
    cout << duration1.count() << " ";
*/
    int ifqu = 2 * log(k);
    auto start2 = high_resolution_clock::now();
    int isA = intro_sort(I, Q, k - 1, ifqu);
    if(isA == 0) {
        for(int i = 0; i < k; i++)
            I[i] = Q[i];
    }
    auto end2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(end2 - start2);
    cout << duration2.count() << " ";

    cout << endl;

    return 0;
}