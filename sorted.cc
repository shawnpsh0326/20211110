//generate sorted input

#include <iostream>
#include <fstream>

int main() {
    using namespace std;
    int n;
    cin >> n;
    int A[1000000];
    for(int i = 0; i < n; i++)
        A[i] = i + 1;
    ofstream file("sorted.txt");
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