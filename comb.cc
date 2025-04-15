#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];

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
    comb_sort(A, k, k);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    

    cout << "Comb sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}