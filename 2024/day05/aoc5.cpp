#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct {
    string before;
    string after;
} RULE;

void getCount(int* p1, int* p2, const string& filename) {
    ifstream file(filename);
    string line;
    int part1lines=0, part2lines=0;
    bool part1 = true;
    while(getline(file, line)) {
        if(part1==true) { part1lines++; }
        if(line.empty()) { part1 = false; part1lines--; }
        if(part1==false) { part2lines++; }
    }
    *p1 = part1lines;
    *p2 = part2lines-1;
    file.close();
}

void getInsuranceOrInput(RULE* rules, string* updates, const string& filename, const int p1) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "The shareholders said no. (getInsurance)" << endl; exit(1); }
    string line;
    int index=0, index2=0;
    bool part1 = true;
    while(file >> line) {
        if(index<p1 && part1 == true) {
            rules[index].before = line.substr(0,2);
            rules[index].after = line.substr(3, 2);
            index++;
        } else { part1 = false; }
        if(part1 == false) { updates[index2] = line; index2++; }
    }
    file.close();
}

void ruleDestructor50000(RULE* rules, string* updates, const int rulecount, const int updatescount, int* count) {
    for (int i = 0; i < updatescount; i++) {
        bool ruleDestructed50000 = false;
        for (int j = 0; j < rulecount; j++) {
            // praise the .find()
            if(updates[i].find(rules[j].before)!=-1 && updates[i].find(rules[j].after)!=-1) {
                if (updates[i].find(rules[j].before) > updates[i].find(rules[j].after)) { ruleDestructed50000 = true; break; }
            }
        }
        if(ruleDestructed50000==false) {
            int seeklen = (int)updates[i].length();
            string FOUNDYOU = updates[i].substr((seeklen/2)-1,2);
            (*count) += stoi(FOUNDYOU);
        }
    }
}

void ruleConstructor50000(RULE* rules, string* updates, const int rulecount, const int updatescount, int* count) {
    for (int i = 0; i < updatescount; i++) {
        bool ruleConstructed50000 = false;
        for (int j = 0; j < rulecount; j++) {
            // glorious .find() - it returns the position of the first char in the string, or -1 if it found none.
            if(updates[i].find(rules[j].before)!=-1 && updates[i].find(rules[j].after)!=-1) {
                if (updates[i].find(rules[j].before) > updates[i].find(rules[j].after)) {
                    ruleConstructed50000 = true;
                    string elem1 = updates[i].substr(updates[i].find(rules[j].before), 2);
                    string elem2 = updates[i].substr(updates[i].find(rules[j].after), 2);
                    updates[i].replace(updates[i].find(rules[j].before), 2, elem2);
                    updates[i].replace(updates[i].find(rules[j].after), 2, elem1);
                    j=0; // this is a HUGE perf hit but its necessary, i think.
                }
            }
        }
        if(ruleConstructed50000==true) {
            int seeklen = (int)updates[i].length();
            string FOUNDYOU = updates[i].substr((seeklen/2)-1,2);
            (*count) += stoi(FOUNDYOU);
        }
    }
}

int main() {
    const string filename = "../aoc-test-5.txt";
    int p1 = 0, p2 = 0, jolly=0;
    getCount(&p1, &p2, filename);

    auto* rules = new RULE[p1];
    auto* updates = new string[p2];

    getInsuranceOrInput(rules, updates, filename, p1);
    ruleDestructor50000(rules, updates, p1, p2, &jolly);
    cout << "silver:\t" << jolly << endl;
    jolly = 0;
    ruleConstructor50000(rules, updates, p1, p2, &jolly);
    cout << "gold:\t" << jolly << endl;

    delete[] rules;
    delete[] updates;
    return 0;
}
// i have yet to see if it works on bigboy.
// im proud of this otherwise.
