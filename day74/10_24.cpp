#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

bool check_size(const string &s, string::size_type sz) {
    return s.size() < sz;
}

int main () {
    vector<int> ival = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    string s = {"hello"};

    auto it = find_if(ival.begin(), ival.end(), bind(check_size, s, placeholders::_1));

    cout << *it << endl;
    system("pause");
    return 0;
}