#include <string>
#include <fstream>
#include <iostream>

using namespace std;
void find_longest_word(ifstream &in) {
    string not_have {"bdfhjkltfgjpqy"};
    int max_length = 0;
    string s, longest_word;
    while (in >> s) {
        if (s.find_first_of(not_have) != string::npos) {
            continue;
        }
        if (max_length < s.size()) {
            longest_word = s;
            max_length = s.size();
        }
    }

    cout << "符合要求的最长的字符串: " << longest_word << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "请输入输入文件" << endl;
    }

    ifstream in(argv[1]);

    if(!in) {
        cout << "无法打开输入文件" << endl;
    }

    find_longest_word(in);

    return 0;
}
