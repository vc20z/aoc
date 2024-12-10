#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// abandon all hope, ye who enter here...

char** getInput(const string& filename, int* arrlen) {
    ifstream file(filename);
    if(!file.is_open()) { cout << "soldier of Christ, why art thou hidden? (getInput)" << endl; exit(1); }

    string line;
    getline(file, line);
    *arrlen = static_cast<int>(line.length());

    file.clear();
    file.seekg(0, ios::beg);

    char** arr = new char*[*arrlen];

    for (int i = 0; i < static_cast<int>(line.length()); i++) {
        arr[i] = new char[*arrlen];
        for (int j = 0; j < static_cast<int>(line.length()); j++) {
            file >> arr[i][j];
        }
    }

    file.close();

    return arr;
}

void solvePart1(char** arr, const int* arrlen, int* silver) {
    char** results = new char*[*arrlen];
    for (int i = 0; i < *arrlen; i++) {
        results[i] = new char[*arrlen];
    }
    for (int i = 0; i < *arrlen; i++) {
        for (int j = 0; j < *arrlen; j++) {
            results[i][j] = '.';
        }
    }
    for (int i = 0; i < *arrlen; i++) {
        for (int j = 0; j < *arrlen; j++) {
            if(arr[i][j] != '.') {
                for (int k = 0; k < *arrlen; k++) {
                    for (int l = 0; l < *arrlen; l++) {
                        if(arr[i][j] == arr[k][l] && i != k && j != l) {
                            int distanceY = i-k; // no absolute value because this loop will run for everything anyways :skull:
                            int distanceX = j-l;
                            if (k-distanceY < *arrlen && k-distanceY >= 0 && l-distanceX < *arrlen && l-distanceX >= 0) { // checking if within bounds
                                results[k-distanceY][l-distanceX] = '#';
                            }
                            if (i+distanceY < *arrlen && i+distanceY >= 0 && j+distanceX < *arrlen && j+distanceX >= 0) {
                                results[i+distanceY][j+distanceX] = '#';
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < *arrlen; i++) {
        for (int j = 0; j < *arrlen; j++) {
            if(results[i][j] == '#') { (*silver)++; }
        }
    }
    for (int i = 0; i < *arrlen; i++) {
        delete[] results[i];
    }
    delete[] results;
}

void solvePart2(char** arr, const int* arrlen, int* gold) {
    char** results = new char*[*arrlen];
    for (int i = 0; i < *arrlen; i++) {
        results[i] = new char[*arrlen];
    }
    for (int i = 0; i < *arrlen; i++) {
        for (int j = 0; j < *arrlen; j++) {
            results[i][j] = '.';
        }
    }
    for (int i = 0; i < *arrlen; i++) {
        for (int j = 0; j < *arrlen; j++) {
            if(arr[i][j] != '.') {
                for (int k = 0; k < *arrlen; k++) {
                    for (int l = 0; l < *arrlen; l++) {
                        if(arr[i][j] == arr[k][l] && i != k && j != l) {
                            int distanceY = i-k;
                            int distanceX = j-l;
                            results[i][j] = results[k][l] = '#';
                            for (int m = 1; m < *arrlen; m++) {
                                if (k-(distanceY*m) < *arrlen && k-(distanceY*m) >= 0 && l-(distanceX*m) < *arrlen && l-(distanceX*m) >= 0) { // checking if within bounds
                                    results[k-(distanceY*m)][l-(distanceX*m)] = '#';
                                }
                                if (i+(distanceY*m) < *arrlen && i+(distanceY*m) >= 0 && j+(distanceX*m) < *arrlen && j+(distanceX*m) >= 0) {
                                    results[i+distanceY][j+distanceX] = '#';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < *arrlen; i++) {
        for (int j = 0; j < *arrlen; j++) {
            if(results[i][j] == '#') { (*gold)++; }
        }
    }
    for (int i = 0; i < *arrlen; i++) {
        delete[] results[i];
    }
    delete[] results;
}

int main() {
    const string filename = "../aoc-test-8.txt";
    int arrlen, silver = 0, gold = 0;
    char** arr = getInput(filename, &arrlen);

    solvePart1(arr, &arrlen, &silver);
    solvePart2(arr, &arrlen, &gold);

    cout << "silver: " << silver << endl;
    cout << "gold: " << gold << endl;

    for (int i = 0; i < arrlen; i++) { delete[] arr[i]; }
    delete[] arr;
    return 0;
}
