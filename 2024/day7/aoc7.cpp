#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<string> getInput(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) { cout << "Bäzingën (getInput)" << endl; exit(1); }

    string line;
    vector<string> lines;
    while(getline(file, line)) { lines.push_back(line); }

    file.close();

    return lines;
}

void doTheMathBro(unsigned long long* silver, vector<string>& equations) {
    for(auto& considered : equations) {

        int colonpos = static_cast<int>(considered.find(':'));                           // find :
        unsigned long long desired = stoull(considered.substr(0, colonpos));      // get number before the colon. we will add this to *silver.
        string equationelements = considered.substr(colonpos + 2);                    // get the elements of the equation

        int lastspace = -1;
        vector<unsigned long long> numbers;
        for (int i = 0; i <= equationelements.length(); i++) {
            if (equationelements[i] == ' ' || i == equationelements.length()) {
                if(lastspace != i - 1) { numbers.push_back(stoull(equationelements.substr(lastspace+1, i-lastspace-1))); }
                lastspace = i;
            }
        }

        int spacecount = static_cast<int>(numbers.size() - 1);
        int totalcombos = (1<<numbers.size());                       // get combination count

        for (int i = 0; i < totalcombos; i++) {                     // and do the mathing.
            unsigned long long currentresult = numbers[0];
            int temp = i;
            for (int j = 0; j < spacecount; j++) {
                char op = (temp % 2 == 0) ? '+' : '*';
                temp /= 2;
                switch (op) {
                    case '+': currentresult+=numbers[j+1]; break;
                    case '*': currentresult*=numbers[j+1]; break;
                    default:; // this will never happen anyways
                }
                if(currentresult > desired) { break; }
            }
            if(currentresult == desired) { (*silver)+=desired; break; }
        }
    }
}

void doTheMathAgainBro(unsigned long long* gold, vector<string>& equations) {
    char chars[] = {'*', '+', '|'};
    for(auto& considered : equations) {

        int colonpos = static_cast<int>(considered.find(':'));
        unsigned long long desired = stoull(considered.substr(0, colonpos));
        string equationelements = considered.substr(colonpos + 2);

        int lastspace = -1;
        vector<unsigned long long> numbers;
        for (int i = 0; i <= equationelements.length(); i++) {
            if (i == equationelements.length() || equationelements[i] == ' ') {
                if (lastspace != i - 1) { numbers.push_back(stoull(equationelements.substr(lastspace + 1, i - lastspace - 1))); }
                lastspace = i;
            }
        }

        int spacecount = static_cast<int>(numbers.size() - 1);
        int totalcombos = static_cast<int>(pow(3, spacecount));

        vector<int> digits_cache(numbers.size());
        for (int j = 0; j < numbers.size(); j++) { digits_cache[j] = (numbers[j] == 0) ? 1 : static_cast<int>(log10(numbers[j])) + 1; } // compute digits
        for (int i = 0; i < totalcombos; i++) {                             // mathing
            unsigned long long currentresult = numbers[0];
            int temp = i;
            for (int j = 0; j < spacecount; j++) {
                char op = chars[temp % 3];
                temp /= 3;
                switch(op) {
                    case '*': currentresult*=numbers[j+1]; break;
                    case '+': currentresult+=numbers[j+1]; break;
                    case '|': {
                        currentresult *= static_cast<unsigned long long>(pow(10, digits_cache[j+1]));
                        currentresult += numbers[j+1];
                    }
                    default: break;
                }
                if(currentresult > desired) { break; }
            }
            if(currentresult==desired) { (*gold)+=desired; break; }
        }
    }
}

int main() {
    const string filename = "../aoc-test-7.txt";
    vector<string> equations = getInput(filename);
    unsigned long long silver = 0, gold = 0;

    doTheMathBro(&silver, equations);
    doTheMathAgainBro(&gold, equations);

    cout << "silver: " << silver << endl;
    cout << "gold:   " << gold << endl;
    return 0;
}