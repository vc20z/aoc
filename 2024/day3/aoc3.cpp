#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

typedef unsigned long long ridiculous;
typedef bool balls;

ridiculous mul(ridiculous a, ridiculous b) {
    return a * b;
}

int main() {

    ridiculous sum = 0;
    balls enabled = true;

    regex findmul(R"(do\(\)|don't\(\)|mul\(([0-9]{1,3}),([0-9]{1,3})\))");
    string line;

    ifstream file("../aoc-input-3.txt");
    if (!file.is_open()) { cout << "Collect my files. (main)" << endl; return 1; }

    while (getline(file, line)) {
        smatch m;
        auto searchStart(line.cbegin());
        while(regex_search(searchStart, line.cend(), m, findmul)) {
            if (m[0]=="do()") { enabled = true; }
            else if (m[0]=="don't()") { enabled = false; }
            else if (enabled) {
                if(m[1].matched && m[2].matched) {
                    ridiculous a = stoull(m[1].str());
                    ridiculous b = stoull(m[2].str());
                    sum += mul(a, b);
                }
            }
            searchStart = m.suffix().first;
        }
    }

    file.close();

    cout << sum << endl;

    return 0;
}
// who would win?
// 20 or regex? (i never did this before)