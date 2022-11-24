#include <vector>
#include <algorithm>
#include <iostream>
#include <string>


using namespace std;
void elimDups(vector<string> &words) {
    for (auto c : words) {
        cout << c << " ";
    }
    cout << words.size() << endl;

    sort(words.begin(), words.end());

    for (auto c : words) {
        cout << c << " ";
    }
    cout << words.size() << endl;

    auto end_unique = unique(words.begin(), words.end());

    for (auto c : words) {
        cout << c << " ";
    }
    cout << words.size() << endl;

    words.erase(end_unique, words.end());

    for (auto c : words) {
        cout << c << " ";
    }
    cout << words.size() << endl;
}

int main () {
    vector<string> s {"cc", "bbbb", "zz", "aa", "aa", "ccc"};
    elimDups(s);
    system("pause");

    return 0;
}