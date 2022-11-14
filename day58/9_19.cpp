#include <iostream>
#include <list>
#include <string>

using namespace std;

int main() {
    string s;
    list<string> l;

    while (cin >> s) {
        l.push_back(s);
    }

    for (auto &c : l) {
        cout << c << endl;
    }

    system("pause");
    return 0;
}