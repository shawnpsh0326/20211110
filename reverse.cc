//generate reverse sorted input

#include <iostream>
#include <fstream>

int main() {
    using namespace std;
    int n;
    cin >> n;
    int A[1000000];
    for(int i = 0; i < n; i++)
        A[i] = n - i;
    ofstream file("reverse.txt");
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