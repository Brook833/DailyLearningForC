#include <map>
#include <iostream>
#include <string>

using namespace std;

int main() {
    map<string, size_t> words_count;
    string word;

    while (cin >> word) {
        auto ret = words_count.insert({word, 1});
        if (!ret.second) {
            ++ret.first->second;
        }
    }

    system("pause");

    return 0;
}