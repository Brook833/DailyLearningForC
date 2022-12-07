#include <iostream>
#include <string>
#include <map>


using namespace std;

int main() {
    map<string, size_t> counts;
    string word;
    
    while (cin >> word) {
        ++counts[word];
    }

    for (auto a : counts) {
        cout << a.first << "出现" << a.second << " 次" << endl;
    }

    return 0;
}