//Selection sort

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];

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
    selection_sort(A, k);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */

    cout << "Selection sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}