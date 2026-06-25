#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

map<string, int> variables;

void executeLine(string line) {
    if (line.empty() || line == "goby_shuru" || line == "goby_shesh") return;

    stringstream ss(line);
    string keyword;
    ss >> keyword;

    if (keyword == "shrimp_rakho") {
        string varName, equalSign;
        int value;
        ss >> varName >> equalSign >> value;
        if (equalSign == "=") {
            variables[varName] = value;
        }
    }
    else if (keyword == "goby_bolo") {
        string target;
        getline(ss, target);
        if(!target.empty() && target[0] == ' ') target = target.substr(1);

        if (target.front() == '"' && target.back() == '"') {
            cout << target.substr(1, target.length() - 2) << endl;
        } else {
            if (variables.find(target) != variables.end()) {
                cout << variables[target] << endl;
            } else {
                cout << "Error: '" << target << "' definition not found!" << endl;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./goby <filename.goby>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: File " << filename << " not found!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        // Trim spaces from beginning
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        executeLine(line);
    }

    file.close();
    return 0;
}
