#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    system("chcp 65001");

    unordered_map<string, size_t> word_count;
    string word;
    while (cin >> word) {
        ++word_count[word];
    }

    for (auto c : word_count) {
        cout << c.first << " 出现" << c.second << " 次" << endl;
    }

    system("pause");
    return 0;
}
