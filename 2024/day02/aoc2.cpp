#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void getcount(int* arr) {
    ifstream file("../aoc-input-2.txt"); // swap to "../aoc-test-2.txt" for example file
    if (!file.is_open()) { cout << "where? (from getcount)" << endl; exit(1);}
    string line;
    int index=0;
    while (getline(file, line)) {
        int spacecount=1;
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ' ') { spacecount++; }
        }
        arr[index]=spacecount;
        index++;
    }
    file.close();
}

void getmynumbers(int** numarr, int* linearr, const int arrlen) {
    ifstream file("../aoc-input-2.txt"); // swap to "../aoc-test-2.txt" for example file
    if (!file.is_open()) { cout << "where? (from getmynumbers)" << endl; exit(1);}
    for (int i = 0; i < arrlen; i++) {
        numarr[i] = (int*)malloc(sizeof(int)*linearr[i]);
        for (int j = 0; j < linearr[i]; j++) {
            file >> numarr[i][j];
        }
    }
    file.close();
}

void releasemynumbers(int** numarr, const int arrlen) {
    for (int i = 0; i < arrlen; i++) {
        free(numarr[i]);
    }
}

void checksafety(int** numarr, int* linearr, const int arrlen) {
    int safecount = 0;
    bool updown;
    for (int i = 0; i < arrlen; i++) {
        int safe = 1, PROBLEM=0;
        if(numarr[i][0] > numarr[i][1]) {
            updown = 0; // DESCEND
        } else {
            updown = 1; // ASCEND
        }
        for (int j = 0; j < linearr[i]-1; j++) {
            int diff=0;
            if(j == PROBLEM) {
                diff = numarr[i][j-1] - numarr[i][j+1];
            } else {
                diff = numarr[i][j] - numarr[i][j+1];
            }
            if (updown==0) {
                if (diff != 1 && diff != 2 && diff != 3) {
                    if (PROBLEM==0) {
                        PROBLEM=j; // THE PROBLEM DAMPENER WILL FIX SOCIETY
                        j = 0;
                    } else {
                        safe=0; // if you need the solution for part 1 remove everything
                        break; // in the if(diff && diff && diff) statements except these
                    }
                }
            } else {
                if (diff != -1 && diff != -2 && diff != -3) {
                    if (PROBLEM==0) {
                        PROBLEM=j; // PRAISE THE PROBLEM DAMPENER
                        j = 0;
                    } else {
                        safe=0;
                        break;
                    }
                }
            }
        }
        safecount+=safe;
    }
    cout << safecount << endl;
}

int main() {
    const int arrlen = 1000; // swap to 6 for test file
    int* numberarr[arrlen];
    int linearr[arrlen]; // im going to hell

    getcount(linearr);
    getmynumbers(numberarr, linearr, arrlen);

    checksafety(numberarr, linearr, arrlen);

    releasemynumbers(numberarr, arrlen);
    return 0;
}

// we dont talk about Advent of Code Day 2.
// we dont talk about Advent of Code Day 2.
// we dont talk about Advent of Code Day 2.
// we dont talk about Advent of Code Day 2.
// we dont talk about Advent of Code Day 2.
// we dont talk about Advent of Code Day 2.