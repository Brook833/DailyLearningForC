#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main() {
    map<string, vector<int>> ival;
    string word;
    vector<int> a;

    ival.insert({word, a}).first->second;

    return 0;
}

// map<stirng, vector<int>>

// pair<map<string, vector<int>>::iterator, bool>