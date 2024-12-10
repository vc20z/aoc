#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<char>> getInput(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "I NEED VICODIN (getInput)" << endl; exit(1); }

    vector<vector<char>> input;
    string line;
    while(getline(file, line)) {
        vector<char> temp;
        for (char c : line) {
            temp.push_back(c);
        }
        input.push_back(temp);
    }

    file.close();
    return input;
}

int silversilver(vector<vector<char>>& input, char start, char target, int y, int x, vector<vector<bool>>& visited) {

    int total = 0;

    if (start == target && visited[x][y] == false) {
        visited[x][y] = true; // we mark that this 9 was found by the zero the path started from.
        return 1;
    }

    if (y + 1 < input.size() && input[y + 1][x] == start + 1) {
        total += silversilver(input, static_cast<char>(start + 1), target, y + 1, x, visited);
    }
    if (y - 1 >= 0 && input[y - 1][x] == start + 1) {
        total += silversilver(input, static_cast<char>(start + 1), target, y - 1, x, visited);
    }
    if (x + 1 < input[0].size() && input[y][x + 1] == start + 1) {
        total += silversilver(input, static_cast<char>(start + 1), target, y, x + 1, visited);
    }
    if (x - 1 >= 0 && input[y][x - 1] == start + 1) {
        total += silversilver(input, static_cast<char>(start + 1), target, y, x - 1, visited);
    }

    return total;
}

int silver(vector<vector<char>>& input, char start, char target) {
    if (start == target) { return 1; }

    int total = 0;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == start) {
                vector<vector<bool>> visited (input[i].size(), vector<bool>(input[i].size(), false));   // we create this vector for each zero
                // then we check each direction for a neighbouring 1. when found, call silversilver to continue searching.
                if (i + 1 < input.size() && input[i + 1][j] == start + 1) {
                    total += silversilver(input, static_cast<char>(start + 1), target, i + 1, j, visited); // down
                }
                if (i - 1 >= 0 && input[i - 1][j] == start + 1) {
                    total += silversilver(input, static_cast<char>(start + 1), target, i - 1, j, visited); // up
                }
                if (j + 1 < input[i].size() && input[i][j + 1] == start + 1) {
                    total += silversilver(input, static_cast<char>(start + 1), target, i, j + 1, visited); // right
                }
                if (j-1 >= 0 && input[i][j-1] == start+1) {
                    total += silversilver(input, static_cast<char>(start + 1), target, i, j - 1, visited); // left
                }
            }
        }
    }

    return total;
}

// part 2 is literally part 1 without the bool vector. i figured this out before i solved part 1. regardless of this, very cool puzzle :)
int goldgold(vector<vector<char>>& input, char start, char target, int y, int x) {

    int total = 0;

    if (start == target) { return 1; } // found a 9

    if (y + 1 < input.size() && input[y + 1][x] == start + 1) {
        total += goldgold(input, static_cast<char>(start + 1), target, y + 1, x); // down
    }
    if (y - 1 >= 0 && input[y - 1][x] == start + 1) {
        total += goldgold(input, static_cast<char>(start + 1), target, y - 1, x); // up
    }
    if (x + 1 < input[0].size() && input[y][x + 1] == start + 1) {
        total += goldgold(input, static_cast<char>(start + 1), target, y, x + 1); // right
    }
    if (x - 1 >= 0 && input[y][x - 1] == start + 1) {
        total += goldgold(input, static_cast<char>(start + 1), target, y, x - 1); // left
    }

    return total;
}

int gold(vector<vector<char>>& input, char start, char target) {
    if (start == target) { return 1; }

    int total = 0;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == start) {
                // gold only finds zeros and tries to find neighbouring 1s. when it does, calls goldgold to continue the search towards the 9s
                if (i + 1 < input.size() && input[i + 1][j] == start + 1) {
                    total += goldgold(input, static_cast<char>(start + 1), target, i + 1, j); // down
                }
                if (i - 1 >= 0 && input[i - 1][j] == start + 1) {
                    total += goldgold(input, static_cast<char>(start + 1), target, i - 1, j); // up
                }
                if (j + 1 < input[i].size() && input[i][j + 1] == start + 1) {
                    total += goldgold(input, static_cast<char>(start + 1), target, i, j + 1); // right
                }
                if (j-1 >= 0 && input[i][j-1] == start+1) {
                    total += goldgold(input, static_cast<char>(start + 1), target, i, j - 1); // left
                }
            }
        }
    }

    return total;
}

int main() {
    const string filename = "../aoc-test-10.txt";
    vector<vector<char>> input = getInput(filename);

    cout << "silver: " << silver(input, '0', '9') << endl;
    cout << "gold:   " << gold(input, '0', '9') << endl;

    return 0;
}
