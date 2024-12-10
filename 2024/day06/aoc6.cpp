#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define UP 0            // this order is strictly specific.
#define RIGHT 1         // we will be changing directions via modulo
#define DOWN 2          // and we know that the guard always goes up
#define LEFT 3          // and then turns 90 degrees (to the right)

using namespace std;

int getLength(const string& filename) {
    ifstream file(filename);
    string line;
    if (!file.is_open()) { cout << "im ryan gosling (getLength)" << endl; exit(1); }
    getline(file, line);
    file.close();
    return (int)line.length();
}

void loadJolly(const string& filename, char** arr, const int arrsize, int* guardX, int* guardY) {
    ifstream file(filename);
    if(!file.is_open()) { exit(1); }
    for (int i = 0; i < arrsize; i++) {
        for (int j = 0; j < arrsize; j++) {
            file >> arr[i][j];                                  // this loads into array
            if (arr[i][j] == '^') { (*guardX)=j; (*guardY)=i; } // this finds the guard
        }
    }
    file.close();
}

void findGuardTiles(char** arr, const int arrsize, int* silver, const int* guardX, const int* guardY) {
    int directionswap=0, direction;
    int guardposX = *guardX, guardposY = *guardY; // these must exist otherwise id have to modify the variables in main and i dont want that.
    // so... what is going on here?
    // basically, while the guard is on the map, check direction.
    // once direction is checked, start moving until the guard
    // encounters a block (#) or exits the map.
    // if he encounters a block (#), he changes direction via the modulo
    // if he exits the map, the while loop breaks
    // otherwise if the next "tile" is a '.', add to silver result.
    // any visited tile is marked with 'X'
    // im explaining this here because this... lets just say, doesnt look pretty.
    while(true) {
        direction=directionswap%4;
        if (direction==UP) {
            arr[guardposY][guardposX] = 'X';                // mark as visited by guard
            if(guardposY==0) { break; }
            if (arr[guardposY-1][guardposX] == '.') { (*silver)++; }
            if (arr[guardposY-1][guardposX] != '#') { guardposY--; } else { directionswap++; }
        }
        if (direction==RIGHT) {
            arr[guardposY][guardposX] = 'X';
            if(guardposX==arrsize-1) { break; }
            if (arr[guardposY][guardposX+1] == '.') { (*silver)++; }
            if (arr[guardposY][guardposX+1] != '#') { guardposX++; } else { directionswap++; }
        }
        if (direction==DOWN) {
            arr[guardposY][guardposX] = 'X';
            if(guardposY==arrsize-1) { break; }
            if (arr[guardposY+1][guardposX] == '.') { (*silver)++; }
            if (arr[guardposY+1][guardposX] != '#') { guardposY++; } else { directionswap++; }
        }
        if (direction==LEFT) {
            arr[guardposY][guardposX] = 'X';
            if(guardposX==0) { break; }
            if (arr[guardposY][guardposX-1] == '.') { (*silver)++; }
            if (arr[guardposY][guardposX-1] != '#') { guardposX--; } else { directionswap++; }
        }
    }
}

bool findGuardTilesPart2(char** arr, const int arrsize, const int* guardX, const int* guardY) {
    vector<vector<int>> wasHeHere(arrsize, vector<int>(arrsize, -1));
    int directionswap=0, direction, itercount=0;
    int guardposX = *guardX, guardposY = *guardY;
    bool didloop = false;
    while(true) {
        direction=directionswap%4;
        if (direction==UP) {
            if(guardposY==0) { break; }
            if (arr[guardposY-1][guardposX] == '#') {
                if(wasHeHere[guardposY][guardposX]==UP) { didloop = true; }
                wasHeHere[guardposY][guardposX] = UP;
                directionswap++;
            } else { guardposY--; }
        }
        if (direction==RIGHT) {
            if(guardposX==arrsize-1) { break; }
            if (arr[guardposY][guardposX+1] == '#') {
                if(wasHeHere[guardposY][guardposX]==RIGHT) { didloop = true; }
                wasHeHere[guardposY][guardposX] = RIGHT;
                directionswap++;
            } else { guardposX++; }
        }
        if (direction==DOWN) {
            if(guardposY==arrsize-1) { break; }
            if (arr[guardposY+1][guardposX] == '#') {
                if(wasHeHere[guardposY][guardposX]==DOWN) { didloop = true; }
                wasHeHere[guardposY][guardposX] = DOWN;
                directionswap++;
            } else { guardposY++; }
        }
        if (direction==LEFT) {
            if(guardposX==0) { break; }
            if (arr[guardposY][guardposX-1] == '#') {
                if(wasHeHere[guardposY][guardposX]==LEFT) { didloop = true; }
                wasHeHere[guardposY][guardposX] = LEFT;
                directionswap++;
            } else { guardposX--; }
        }
        itercount++;                                                // this is... ugh.
        if(itercount > (arrsize*arrsize)/2) { didloop = true; }     // i shouldnt be allowed to write code.
        if(didloop) { break; }
    }
    return didloop;
}

void findGuardLoop(char** arr, const int arrsize, int* gold, const int* guardX, const int* guardY) {
    bool didLoop = false;
    for (int i = 0; i < arrsize; i++) {
        for (int j = 0; j < arrsize; j++) {
            if (arr[i][j] == 'X') {
                arr[i][j] = '#';
                didLoop = findGuardTilesPart2(arr, arrsize, guardX, guardY);
                if(didLoop) { (*gold)++; }
                arr[i][j] = 'X';
            }
        }
    }
}

int main() {
    string filename = "../aoc-test-6.txt";
    // im setting silver result to 1 at the start because
    // i will not be counting the guard's spawn point
    int arrsize = getLength(filename), silver = 1, gold = 0;
    int guardX, guardY;

    char** arr = new char*[arrsize];
    for (int i = 0; i < arrsize; i++) { arr[i] = new char[arrsize]; }

    loadJolly(filename, arr, arrsize, &guardX, &guardY);
    findGuardTiles(arr, arrsize, &silver, &guardX, &guardY);
    arr[guardY][guardX] = '^';
    findGuardLoop(arr, arrsize, &gold, &guardX, &guardY);
    cout << "silver: " << silver << endl;
    cout << "gold: " << gold << endl;
    for (int i = 0; i < arrsize; i++) { delete[] arr[i]; }
    delete[] arr;
    return 0;
}
// this isnt a real solution.
// never let me touch a text editor.