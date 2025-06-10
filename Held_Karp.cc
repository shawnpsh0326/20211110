#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

struct city {
    int no;
    double x, y;
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

int distance_of_cities(const city city1, const city city2) {
    int x_diff = city1.x - city2.x;
    int y_diff = city1.y - city2.y;
    return static_cast<int>(round(sqrt(x_diff * x_diff + y_diff * y_diff)));
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

    //map dist
    int** map_dist = new int*[num_city];
    for (int i = 0; i < num_city; i++)
        map_dist[i] = new int[num_city];

    for (int i = 0; i < num_city; i++)
        for (int j = 0; j < num_city; j++)
            map_dist[i][j] = distance_of_cities(cities[i], cities[j]);

    //least dist
    int** least_dist = new int*[1 << num_city];
    for (int i = 0; i < (1 << num_city); i++)
        least_dist[i] = new int[num_city];

    for (int i = 0; i < (1 << num_city); i++)
        for (int j = 0; j < num_city; j++)
            least_dist[i][j] = INT_MAX;

    //tsp
    int ** tsp = new int*[1 << num_city];
    for (int i = 0; i < (1 << num_city); i++)
        tsp[i] = new int[num_city];

    for (int i = 0; i < (1 << num_city); i++)
        for (int j = 0; j < num_city; j++)
            tsp[i][j] = -1;
    
    least_dist[(1 << 0)][0] = 0;

    for (int i = 0; i < (1 << num_city); i++) {
        for (int j = 0; j < num_city; j++) {
            if (i & (1 << j)) {
                for (int k = 0; k < num_city; k++) {
                    if (!(i & (1 << k)) && j != k) {
                        int ni = i | (1 << k);
                        if (least_dist[i][j] != INT_MAX)
                            if (least_dist[ni][k] > least_dist[i][j] + map_dist[j][k]) {
                                least_dist[ni][k] = least_dist[i][j] + map_dist[j][k];
                                tsp[ni][k] = j;
                            }
                    }
                }
            }
        }
    }

    int total_distance = INT_MAX;
    int last = -1;
    for (int i = 0; i < num_city; i++) {
        if (map_dist[i][0] != INT_MAX && least_dist[(1 << num_city) - 1][i] != INT_MAX) {
            if (total_distance > least_dist[(1 << num_city) - 1][i] + map_dist[i][0]) {
                total_distance = least_dist[(1 << num_city) - 1][i] + map_dist[i][0];
                last = i;
            }
        }
    }

    int visited_city = (1 << num_city) - 1;
    int* tsp_path = new int[num_city + 1];
    tsp_path[num_city] = 0;
    int now = num_city - 1;

    while (last != -1) {
        tsp_path[now] = last;
        now -= 1;
        int next = tsp[visited_city][last];
        visited_city ^= (1 << last);
        last = next;
    }
    tsp_path[0] = 0;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "tsp path: ";
    for (int i = 0; i <= num_city; i++)
        cout << tsp_path[i] + 1 << " ";

    cout << endl;


    cout << "Total distance: "<< total_distance << endl;
    cout << "Time: " << duration.count() << " microsecond" << endl;

   
    delete [] cities;
    for (int i = 0; i < num_city; i++)
        delete [] map_dist[i];
    delete [] map_dist;
    for (int i = 0; i < (1 << num_city); i++)
        delete [] least_dist[i];
    delete [] least_dist;
    for (int i = 0; i < (1 << num_city); i++)
        delete [] tsp[i];
    delete [] tsp;
    delete [] tsp_path;

    return 0;
}