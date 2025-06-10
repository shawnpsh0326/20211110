#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

int map_tsp[10000][10000];

struct city {
    int no;
    double x, y;
};

struct cd {
    int distance;
    city city1;
    city city2;
};

int number_of_city(const string& filename) {
    ifstream file(filename);
    string line;
    int num_city = 0;
    while (getline(file, line)) {
        if (line.find("DIMENSION:") != string::npos) {
            istringstream iss(line);
            string s;
            iss >> s >> num_city;
            return num_city;
        }
        if (line.find("DIMENSION :") != string::npos) {
            istringstream iss(line);
            string s1, s2;
            iss >> s1 >> s2 >> num_city;
            return num_city;
        }
    }
    return -1;
}

void read_tsp(const string& filename, city* cities) {
    ifstream file(filename);
    string line;
    bool now_read = false;
    int i = 0;
    while (getline(file, line)) {
        if (line == "EOF") 
            break;
        if (line.find("NODE_COORD_SECTION") != string::npos) {
            now_read = true;
            continue;
        }
        if (now_read == true) {
            istringstream iss(line);
            iss >> cities[i].no >> cities[i].x >> cities[i].y;
            i++;
        }
    }
}

void distance_of_cities(const city* cities, cd* cds, const int num_city) {
    int di = 0;
    for (int i = 0; i < num_city; i++)
        for (int j = i + 1; j < num_city; j++){
            int x_diff = cities[i].x - cities[j].x;
            int y_diff = cities[i].y - cities[j].y;
            cds[di].distance = static_cast<int>(round(sqrt(x_diff * x_diff + y_diff * y_diff)));
            cds[di].city1 = cities[i];
            cds[di].city2 = cities[j];
            di++;
        }
}

void merge(cd* cds, cd* Lcds, cd* Rcds, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    for(int i = 0; i < n1; i++)
        Lcds[i] = cds[p + i];
    for(int j = 0; j < n2; j++)
        Rcds[j] = cds[q + j + 1];

    Lcds[n1].distance = INT_MAX;
    Rcds[n2].distance = INT_MAX;

    int i = 0;
    int j = 0;

    for(int k = p; k <= r; k++) {
        if(Lcds[i].distance <= Rcds[j].distance) {
            cds[k] = Lcds[i];
            i++;
        }
        else {
            cds[k] = Rcds[j];
            j++;
        }
    }

    return;
}

void merge_sort(cd* cds, cd* Lcds, cd* Rcds, int p, int r) {
    if(p < r) {
        int q = (p + r) / 2;
        merge_sort(cds, Lcds, Rcds, p, q);
        merge_sort(cds, Lcds, Rcds, q + 1, r);
        merge(cds, Lcds, Rcds, p, q, r);
    }
    return;
}

int find(int* for_mst, int no) {
    if (for_mst[no] == no)
        return no;
    for_mst[no] = find(for_mst, for_mst[no]);
    return for_mst[no];
}

void sum(int* for_mst, int no1, int no2) {
    for_mst[find(for_mst, no1)] = find(for_mst, no2);
}

void find_mst(cd* cds, cd* Lcds, cd* Rcds, cd* mst, int num_city) {
    merge_sort(cds, Lcds, Rcds, 0, num_city * (num_city - 1) / 2 - 1);

    int for_mst[num_city];
    int j = 0;
    for (int i = 0; i < num_city; i++)
        for_mst[i] = i;
    for (int i = 0; i < num_city * (num_city - 1) / 2; i++) {
        if (find(for_mst, cds[i].city1.no - 1) != find(for_mst, cds[i].city2.no - 1)) {
            mst[j] = cds[i];
            sum(for_mst, cds[i].city1.no - 1, cds[i].city2.no - 1);
            j++;
        }
        if (j >= num_city - 1)
            break;
    }
}

void dfs(int n, int* tsp, int& num, int num_city) {
    for (int i = 0; i < num_city; i++) {
        if (map_tsp[n][i] == 1) {
            tsp[num++] = i;
            map_tsp[n][i] = 0;
            map_tsp[i][n] = 0;
            dfs(i, tsp, num, num_city);
        }
    }
}

void find_tsp(cd* mst, int* tsp, int num_city) {
    tsp[0] = 0;
    tsp[num_city] = 0;
    int num = 1;
    for (int i = 0; i < num_city - 1; i++) {
        map_tsp[mst[i].city1.no - 1][mst[i].city2.no - 1] = 1;
        map_tsp[mst[i].city2.no - 1][mst[i].city1.no - 1] = 1;
    }
    dfs(0, tsp, num, num_city);
}

int main() {
    string filename;
    cin >> filename;
    int num_city = number_of_city(filename);

    if (num_city == -1) {
        cout << "Error" << endl;
        return 0;
    }
    
    city* cities = new city[num_city];
    read_tsp(filename, cities);

    auto start = high_resolution_clock::now();

    cd* cds = new cd[num_city * (num_city - 1) / 2];
    distance_of_cities(cities, cds, num_city);
    
    cd* Lcds = new cd[num_city * (num_city - 1) / 2];
    cd* Rcds = new cd[num_city * (num_city - 1) / 2];
    cd* mst = new cd[num_city - 1];
    find_mst(cds, Lcds, Rcds, mst, num_city);

    int* tsp = new int[num_city + 1];
    for (int i = 0; i < num_city; i++)
        for (int j = 0; j < num_city; j++)
            map_tsp[i][j] = 0;
    find_tsp(mst, tsp, num_city);

    int total_distance = 0;
    for (int i = 0; i < num_city; i++) {
        int x_diff = cities[tsp[i]].x - cities[tsp[i + 1]].x;
        int y_diff = cities[tsp[i]].y - cities[tsp[i + 1]].y;
        total_distance += static_cast<int>(round(sqrt(x_diff * x_diff + y_diff * y_diff)));
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "tsp: ";
    for (int i = 0; i < num_city; i++)
        cout << tsp[i] + 1 << " ";

    cout << endl;

    cout << "Total distance: "<< total_distance << endl;
    cout << "Time: " << duration.count() << " microsecond" << endl;
    

    delete [] cities;
    delete [] cds;
    delete [] Lcds;
    delete [] Rcds;
    delete [] mst;
    delete [] tsp;
    return 0;
}