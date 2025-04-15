//Library sort

#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

int A[1000000];
int L[2000000];
int L0[2000000];

int reblance(int n, int s, int reb) {
    reb = 2 * s;
    for(int i = 0; i < reb + 1; i++)
        L0[i] = NULL;
    int o = 0;
    for(int i = 0; i < reb + 1; i++) {
        if(L[i] != NULL) {
            L0[2 * o + 1] = L[i];
            o++;
        }
    }
    for(int i = 0; i < reb + 1; i++) {
        L[i] = L0[i];
    }
    return reb;
}

int binary_s(int l, int r, int e) {
    int mid;
    while(l <= r) {
        mid = l + (r - l) / 2;
        if(l == r)
            return mid;
        if(mid%2 == 0 && L[mid] == NULL) {
            mid--;
        }
        if(e == L[mid])
            return mid;
        else if(e > A[mid])
            l = mid + 1;
        else
            r = mid - 1;
    }
    return mid;
}


void insert(int e, int n, int s, int reb) {
    if(s == 1) {
        L[1] = e;
        reb = 2;
        return;
    }

    int index = binary_s(0, reb, e);

    if(L[index] == NULL)
        L[index] = e;
    else if(index + 1 > reb) {
        reb = reblance(n, s, reb);
        insert(e, n, s, reb);
        return;
    }
    else if(L[index + 1] == NULL)
        L[index + 1] = e;
    else {
        for(int i = 1; (index + i) < reb; i++) {
            if(L[index + i] == L[index]);
            else if(L[index + i] == NULL)
                L[index + i] = e;
            else {
                reb = reblance(n, s, reb);
                insert(e, n, s, reb);
                return;
            }
        }
        reb = reblance(n, s, reb);
        insert(e, n, s, reb);
        return;
    }
    return;
}

void library_sort(int n, int s, int reb) {
    for(int i = 0; i < n; i++) {
        s++;
        insert(A[i], n, s, reb);
    }
    return;
}

int main() {

    int a;
    cin >> a;
    int k = 0;
    int b;
    for(int i = 0; i < a; i++) {
        cin >> b;
        A[i] = b;
        k++;
    }
    int reb = 0;
    int s = 0;

    for(int i = 0; i < 2 * k; i++) 
        L[i] = NULL;

    auto start = high_resolution_clock::now();
    library_sort(k, s, reb);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    
    int j = 0;
    for(int i = 0; i < 2 * k; i++) {
        if(L[i] != NULL) {
            A[j] = L[i];
            j++;
        }
    }

    for(int i = 0; i < 2 * k; i++)
        cout << L[i] << " ";
    cout << endl;
    
    for(int i = 0; i < k; i++)
        cout << A[i] << " ";
    cout << endl;
    

    cout << "Library sort time: " << duration.count() << " microsecond" << endl;

    return 0;
}