//Bubble sort

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];

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
    bubble_sort(A, k-1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */

    cout << "Bubble sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}