#include <iostream>
#include <string>

using namespace std;

int main () {
    system("chcp 65001");

    string s {"ab2c3d7R4E6"};
    string numbers {"0123456789"};
    string alphabet{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    cout << "仅数字版本:  ";
    for (string::size_type pos = 0; (pos = s.find_first_not_of(alphabet, pos)) != string::npos; pos++) {
        cout << s[pos];
    }
    cout << endl;
    cout << "仅字母版本:  ";
        for (string::size_type pos = 0; (pos = s.find_first_not_of(numbers, pos)) != string::npos; pos++) {
        cout << s[pos];
    }

    system("pause");
    return 0;
}