#include <string>
#include <iostream>

using namespace std;

int main() {
    string s;
    s.reserve(100);
    char w;
    while (cin >> w) {
        s.push_back(w);
    }

    return 0;
}