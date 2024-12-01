#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// i spent 3 hours on this function for no reason in particular
void getinput(int arrlen, int* arr1, int* arr2) {
    ifstream file("../aoc-input-1.txt");
    // ifstream file("../aoc-test-1.txt");
    if(!file.is_open()) { cout << "missing!" << endl; exit(1); }
    string line;
    char a1[6]; char a2[6]; // change to [2] for test file
    for (int i = 0; i < arrlen; i++) {
        getline(file, line);
        // change to j < 2 for test file
        for (int j = 0; j < 6; j++) {
            a1[j] = line[j];
            a2[j] = line[j+8]; // change to [j+4] for test file
        }
        arr1[i] = (int)strtol(a1, NULL, 10);
        arr2[i] = (int)strtol(a2, NULL, 10);
    }
    file.close();
}

void sortlist(int* arr, int arrlen) {
    for (int i = 0; i < arrlen-1; i++) {
        bool swapped=false;
        for (int j = 0; j < arrlen-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            }
        }
        if(swapped==false) { break; }
    }
}

int getdistance(int* arr1, int* arr2, int arrlen) {
    int dist = 0; // this was a long. wtf?

    for (int i = 0; i < arrlen; i++) {
        // could i use abs? yes. do i care? no.
        if (arr1[i] > arr2[i]) {
            dist += arr1[i]-arr2[i];
        } else if (arr1[i] < arr2[i]) {
            dist += arr2[i]-arr1[i];
        } else {
            dist += 0;
        }
    }

    return dist;
}

int similarityscore(int* arr1, int* arr2, int arrlen) {
    int score=0;

    for (int i = 0; i < arrlen; i++) {
        int occurence=0;

        for (int j = 0; j < arrlen; j++) {
            if (arr1[i] == arr2[j]) { occurence++; }
        }

        score += arr1[i]*occurence;
    }

    return score;
}

int main() {
    int arr1[1000]; // change all 1000s to 6 for test file
    int arr2[1000];

    getinput(1000, arr1, arr2);

    sortlist(arr1, 1000); // you dont have to use these if you want just the similarityscore
    sortlist(arr2, 1000);

    cout << getdistance(arr1, arr2, 1000) << endl;
    cout << similarityscore(arr1, arr2, 1000) << endl;

    return 0;
}