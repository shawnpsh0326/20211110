#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];

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

    int k;
    cin >> k;
    for(int i = 0; i < k; i++)
        cin >> A[i];

    auto start = high_resolution_clock::now();
    cocktail_shaker_sort(A, 0, k-1);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    /*
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    */

    cout << "Cocktail shaker sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}