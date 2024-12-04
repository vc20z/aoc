#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int arrSize = 10; // 140 for input file, 10 for test file

void fillXmasArr(char arrn[][arrSize], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "you are a goblin. (fillXmasArr)" << endl; exit(1); }
    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize; j++) {
            file >> arrn[i][j];
        }
    }
    file.close();
}

void stringEater(char input, string* target) {
    string temp = *target;
    (*target)[1] = temp[0];
    (*target)[2] = temp[1];
    (*target)[3] = temp[2];
    (*target)[0] = input;
}

void driveMeOverWithAChar(char arr[][arrSize], int* counter) {
    string santaSleight = "    ", PANZERKAMPFWAGEN = "    "; // keep this 4 chars long.
    // checking horizontally and vertically
    for (int i = 0; i < arrSize; i++) {
        santaSleight = PANZERKAMPFWAGEN = "    ";
        for (int j = 0; j < arrSize; j++) {
            stringEater(arr[i][j], &santaSleight);
            stringEater(arr[j][i], &PANZERKAMPFWAGEN);
            if(santaSleight=="XMAS" || santaSleight == "SAMX") { (*counter)++; }
            if(PANZERKAMPFWAGEN=="XMAS" || PANZERKAMPFWAGEN == "SAMX") { (*counter)++; }
        }
    }
    // checking \ diagonal
    for (int i = 0; i < arrSize - 3; i++) {
        for (int j = 0; j < arrSize - 3; j++) {
            if (arr[i][j] == 'X' && arr[i+1][j+1] == 'M' && arr[i+2][j+2] == 'A' && arr[i+3][j+3] == 'S') { (*counter)++; }
            if (arr[i][j] == 'S' && arr[i+1][j+1] == 'A' && arr[i+2][j+2] == 'M' && arr[i+3][j+3] == 'X') { (*counter)++; }
        }
    }

    // checking / diagonal
    for (int i = 3; i < arrSize; i++) {
        for (int j = 0; j < arrSize - 3; j++) {
            if (arr[i][j] == 'X' && arr[i-1][j+1] == 'M' && arr[i-2][j+2] == 'A' && arr[i-3][j+3] == 'S') { (*counter)++; }
            if (arr[i][j] == 'S' && arr[i-1][j+1] == 'A' && arr[i-2][j+2] == 'M' && arr[i-3][j+3] == 'X') { (*counter)++; }
        }
    }
}

void driveMeOverWithACharAgain(char arr[][arrSize], int* counter) {
    for (int i = 1; i < arrSize-1; i++) {
        for (int j = 1; j < arrSize-1; j++) {
            if (arr[i][j] == 'A') {
                if(((arr[i-1][j-1] == 'M' && arr[i+1][j+1] == 'S') || (arr[i-1][j-1] == 'S' && arr[i+1][j+1] == 'M')) && ((arr[i+1][j-1] == 'M' && arr[i-1][j+1] == 'S') || (arr[i+1][j-1] == 'S' && arr[i-1][j+1] == 'M'))) {
                    (*counter)++;
                }
            }
        }
    }
}
// i-1 j-1 | i-1 j | i-1 j+1
// -------------------------
//  i  j-1 | i   j |  i  j+1
// -------------------------
// i+1 j-1 | i+1 j | i+1 j+1

int main() {
    const string filename = "../aoc-test-4.txt";
    char xmasArr[arrSize][arrSize];
    int jollyCounter = 0;

    fillXmasArr(xmasArr, filename);
    // took me 7 hours
    driveMeOverWithAChar(xmasArr, &jollyCounter);

    cout << "silver:\t" << jollyCounter << endl;
    jollyCounter = 0;

    // this f***ing elf...
    // took me like what, 10 minutes at most?
    driveMeOverWithACharAgain(xmasArr, &jollyCounter);

    cout << "gold:\t" << jollyCounter << endl;

    return 0;
}
// We don't talk about Advent of Code Day 4 either.
// We don't talk about Advent of Code Day 4 either.
// We don't talk about Advent of Code Day 4 either.
// We don't talk about Advent of Code Day 4 either.
// We don't talk about Advent of Code Day 4 either.