//Insertion sort

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];

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
    insertion_sort(A, k-1, 1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */

    cout << "Insertion sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}