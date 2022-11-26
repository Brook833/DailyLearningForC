#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool string_length(const string &s) {
    if (s.size() >= 5) {
        return true;
    }
    return false;
}

int main () {
    vector<string> s =  {"cccccc", "iii", "zz", "bbbbb", "c"};
    for (auto c : s) {
        cout << c << " ";
    }
    
    cout << endl;

    auto it = partition(s.begin(), s.end(), string_length);

    for (auto c = s.begin(); c != it; c++) {
        cout << *c << " ";
    }

    system("pause");

    return 0;
}