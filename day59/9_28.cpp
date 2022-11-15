#include <iostream>
#include <forward_list>
#include <string>

using namespace std;

bool test(string &s1, string &s2, forward_list<string> &l) {
    auto prev = l.before_begin();
    auto now = l.begin();
    bool id = false;
    while (now != l.end()) {
        if (*now == s1) {
           now = l.insert_after(now, s2);
           id = true;
           return true;
        } else {
            prev = now;
            ++now;
        }
    }
    if(!id){
        now = l.insert_after(prev, s2);
    }
    return false;
}

int main() {
    system("chcp 65001");
    forward_list<string> l {"Hello", "World"};
    string s1 = "Hello";
    string s2 = "!";

    if (test(s1, s2, l)) {
        cout << "容器中存在s1: ";
    } else {
        cout << "容器中不存在s1: ";
    }

    for (auto &c : l) {
        cout << c << " ";
    }

    system("pause");
    return 0;
}