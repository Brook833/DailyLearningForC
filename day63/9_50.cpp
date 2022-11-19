#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    system("chcp 65001");
    vector<string> isvec = {"123", "+456", "-789"};
    vector<string> fsvec{"12.3", "-4.56", "+7.8e-2"};
    int ri = 0;
    for (auto &c : isvec) {
        ri += stoi(c);
    }
    float rf = 0.0;
    for (auto &c : fsvec) {
        rf += stof(c);
    }
    cout << "整数和为:   " << ri << endl;
    cout << "浮点数和为: " << rf << endl;
    system("pause");
    return 0;
}