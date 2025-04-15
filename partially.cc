//generate partially sorted input

#include <iostream>
#include <climits>
#include <stdlib.h>
#include <time.h>
#include <fstream>

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
    using namespace std;
    srand(time(NULL));
    int n;
    int p;
    cin >> n >> p;
    for(int i = 0; i < n; i++)
        A[i] = rand();

    int ps = rand()%(n-p);

    merge_sort(A, L, R, ps-1, ps + p - 1);
    
    ofstream file("partially.txt");
    if(file.is_open()) {
        for(int i = 0; i < n; i++)
            file << A[i] << " ";
        file.close();
    }
    else {
        cout << "error" << endl;
        return 1;
    }
    return 0;
}