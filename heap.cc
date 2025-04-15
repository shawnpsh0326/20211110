//Heap-sort

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];

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
    heap_sort(A, k-1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */

    cout << "Heap sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}