#include <iostream>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];
int T[2000000];
int V[2000000];

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
    tournament_sort(A, k);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    

    cout << "Tournamrnt sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}