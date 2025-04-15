//Merge-sort

#include <iostream>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];
int L[1000000];
int R[1000000];

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
        A[k] = a;
        k++;
    }

    auto start = high_resolution_clock::now();
    merge_sort(A, L, R, 0, k-1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */
   
    cout << "Merge sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}