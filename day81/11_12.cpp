#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<pair<string, int>> data;  // pair的vector
    string s;
    int v;
    while (cin >> s && cin >> v) {
        data.push_back(pair<string, int> (s, v));
    }

    for (auto c : data) {
        cout << c.first << " " << c.second << endl;
    }

    system("pause");
    return 0;
}