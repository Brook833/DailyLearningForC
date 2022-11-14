#include <iostream>
#include <string>
#include <deque>

using namespace std;
int main() {
    string s;
    deque<string> l;

    while (cin >> s) {
        l.push_back(s);
    }

    for (auto &c : l) {
        cout << c << endl;
    }

    system("pause");
    return 0;
}