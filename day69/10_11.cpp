#include <iostream>
#include <algorithm>
#include <vector>
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

bool isShorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

int main () {
   std::vector<std::string> s = {"the", "quick", "red", "fox", "jumps",
                                     "over", "the", "slow", "red", "turtle"};
    elimDups(s);

    stable_sort(s.begin(), s.end(), isShorter);

    for (auto c : s) {
        cout << c << " ";
    }

    system("pause");

    return 0;
}