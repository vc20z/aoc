#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int arrSize = 15000;

void fillXmasArr(char** arrn, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "you are a goblin. (fillXmasArr)" << endl; exit(1); }
    for (int i = 0; i < arrSize+1; i++) {
        arrn[i] = (char*)malloc(sizeof(char)*arrSize);
        for (int j = 0; j < arrSize; j++) {
            file >> arrn[i][j];
        }
    }
    file.close();
}

void driveMeOverWithAChar(char** arr, int* counter) {
    for (int i = 0; i < arrSize; i++) {
        for (int j = 0; j < arrSize; j++) {
            // checking horizontally
            if (j < arrSize-3) {
                if((arr[i][j] == 'X' && arr[i][j+1] == 'M' && arr[i][j+2] == 'A' && arr[i][j+3] == 'S') || (arr[i][j] == 'S' && arr[i][j+1] == 'A' && arr[i][j+2] == 'M' && arr[i][j+3] == 'X')) { (*counter)++; }
            }
            if(j < arrSize-3) {
                // checking vertically and diagonally
                if((arr[j][i] == 'X' && arr[j+1][i] == 'M' && arr[j+2][i] == 'A' && arr[j+3][i] == 'S') || (arr[j][i] == 'S' && arr[j+1][i] == 'A' && arr[j+2][i] == 'M' && arr[j+3][i] == 'X')) { (*counter)++; }
                if(i < arrSize-3) {
                    if (arr[i][j] == 'X' && arr[i+1][j+1] == 'M' && arr[i+2][j+2] == 'A' && arr[i+3][j+3] == 'S') { (*counter)++; }
                    if (arr[i][j] == 'S' && arr[i+1][j+1] == 'A' && arr[i+2][j+2] == 'M' && arr[i+3][j+3] == 'X') { (*counter)++; }
                }
                if(i>=3) {
                    if (arr[i][j] == 'X' && arr[i-1][j+1] == 'M' && arr[i-2][j+2] == 'A' && arr[i-3][j+3] == 'S') { (*counter)++; }
                    if (arr[i][j] == 'S' && arr[i-1][j+1] == 'A' && arr[i-2][j+2] == 'M' && arr[i-3][j+3] == 'X') { (*counter)++; }
                }
            }
        }
    }
}

void driveMeOverWithACharAgain(char** arr, int* counter) {
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

int main() {
    clock_t start = clock();
    const string filename = "../bigboy.txt";
    char** xmasArrBigBoy = (char**)malloc((arrSize+1)*sizeof(char*));
    int jollyCounter = 0;

    fillXmasArr(xmasArrBigBoy, filename);
    clock_t p1start = clock();
    driveMeOverWithAChar(xmasArrBigBoy, &jollyCounter);

    cout << "silver:\t" << jollyCounter << endl;
    clock_t p1end = clock();
    jollyCounter = 0;

    driveMeOverWithACharAgain(xmasArrBigBoy, &jollyCounter);
    cout << "gold:\t" << jollyCounter << endl;
    clock_t end = clock();
    cout << "time (part 1): " << (double)(p1end-p1start)/CLOCKS_PER_SEC << endl;
    cout << "time (part 2): " << (double)(end-p1end)/CLOCKS_PER_SEC << endl;
    cout << "time (total): " << (double)(end-start)/CLOCKS_PER_SEC << endl;
    for (int i = 0; i<arrSize; i++) { free(xmasArrBigBoy[i]); }
    free(xmasArrBigBoy);
    clock_t end2 = clock();
    cout << "time (dealloc): " << (double)(end2-start)/CLOCKS_PER_SEC << endl;
    return 0;
}
