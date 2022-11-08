#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


struct PersonInfo {
    string name;
    vector<string> phones;
};

string format(const string &s) {
    return s;
}

bool valid(const string &s) {
    // 如何验证电话号码将在第 17 章介绍
    // 现在简单返回 true
    return true;
}

using namespace std;
int main (int argc, char *argv[]) {
    ifstream in(argv[1]);  // 打开第一个文件
    if (!in) {
        cerr << "无法打开输入文件" << endl;
    }

    string line, word;
    vector<PersonInfo> people;

    while (getline(in, line)) {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;  // record保存的是名字，电话号码。
        while (record >> word) {
            info.phones.push_back(word);
        }
        people.push_back(info);
    }

    ostringstream os;
    for (const auto &entry : people) {
        ostringstream formatted, badNums;
        for (const auto &nums : entry.phones) {
            if (!valid(nums)) {
                badNums << " " << nums;
            } else {
                formatted << " " << format(nums);
            }
        }

        if (badNums.str().empty()) {
            os << entry.name << " " << formatted.str() << endl;
        } else {
            cerr << "input error: " << entry.name << " invalid numbers(s) " << badNums.str() << endl;
        }
    }

    cout << os.str() << endl;
    
    return 0;
}