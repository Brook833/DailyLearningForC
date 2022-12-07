#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void add_family(map<string, vector<string>> &families, const string &first_name) {
    if (families.find(first_name) == families.end()) {
        families[first_name] = vector<string>();
    }
}

void add_child(map<string, vector<string>> &families, const string &first_name, const string &last_name) {
    families[first_name].push_back(last_name);
}


int main() {
    map<string, vector<string>> families;

    vector<pair<string, int>> children_birthday;
    add_family(families, "张");
    add_child(families, "张", "强");
    add_child(families, "张", "三");
    add_child(families, "王", "五");
    add_family(families, "王");

    for (auto f : families) {
        cout << f.first << "家的孩子：";
        for (auto c : f.second)
            cout << f.first << c << " ";
        cout << endl;
    }
    return 0;
}
