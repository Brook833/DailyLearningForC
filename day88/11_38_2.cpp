#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

unordered_map<string, string> buildMap(ifstream &map_file) {
    string key, value;
    unordered_map<string, string> trans_map;
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() > 1) {
            trans_map[key] = value.substr(1);
        }
    }
    return trans_map;
}

string& transform(unordered_map<string, string> &m, string &s) {
    auto it = m.find(s);
    if (it != m.end()) {
        return it->second;
    } else {
        return s;
    }
}

void word_transform(ifstream &map_file, ifstream &input) {
    unordered_map<string, string> trans_map;
    trans_map = buildMap(map_file);
    string text;
    string word;
    while (getline(input, text)) {
        istringstream is(text);
        while (is >> word) {
            cout << transform(trans_map, word);

        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    ifstream map_file(argv[1]);
    ifstream input(argv[2]);

    word_transform(map_file, input);

    return 0;
}
