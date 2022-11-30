#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

bool j(const string &s, vector<string>::size_type sz) {
    if (s.size() > sz) {
        return true;
    }
    return false;
}

int main () {
    vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};
    cout << count_if(vs.begin(), vs.end(), bind(j, placeholders::_1, 6)) << endl;
    
    system("pause");
    return 0;
}