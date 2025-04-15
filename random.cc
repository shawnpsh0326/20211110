//generate random input

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

int main() {
    using namespace std;
    srand(time(NULL));
    int n;
    cin >> n;
    int A[1000000];
    for(int i = 0; i < n; i++)
        A[i] = rand();
    ofstream file("random.txt");
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