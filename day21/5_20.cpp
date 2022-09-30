#include <iostream>
#include <string>

using namespace std;
int main() {
    system("chcp 65001");
    string now_str;
    string pre_str;
    string s;
    while (cin >> s ) {
        now_str = s;
        if (now_str == pre_str) {
            cout << "连续两次出现相同的字符，退出循环" << endl;
            break;
        }
        pre_str = s;
    }
    cout << " 结束 " << endl;
    system("pause");
    return 0;
}