#include <iostream>
#include <map>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

string transform(const string &s, map<string, string> &m) {
    auto it = m.find(s);
    if (it != m.end()) {
        return it->second;
    } else {
        return s;
    }
}

map<string, string> buildMap(ifstream &map_file) {
    string key, value;
    map<string, string> trans_map;
    while (map_file >> key && getline(map_file, value)) {
        if (value.size()) {
            trans_map[key] = value.substr(1);
        } else {
            throw runtime_error("no rule for" + key);
        }
    }
    return trans_map;
}

void word_transform(ifstream &map_file, ifstream &input) {
    map<string, string> trans_map = buildMap(map_file);
    string text;
    while (getline(input, text)) {
        istringstream is(text);
        string word;
        while (is >> word) {
            cout << transform(word, trans_map);
        }
    }
}

int main(int argc, char** argv) {
    ifstream map_file(argv[1]);
    ifstream input(argv[2]);

    word_transform(map_file, input);

    return 0;
}