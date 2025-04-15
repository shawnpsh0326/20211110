//Quick sort

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];

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
    quick_sort(A, 0, k-1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */

    cout << "Quick sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}