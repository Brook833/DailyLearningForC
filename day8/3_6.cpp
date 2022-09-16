#include <windows.h>
#include <iostream>
#include <string>


int main () {
    system ("chcp 65001");
    std::string s;
    std::cin >> s;

    for (auto &c : s) {
        c = 'X';
    }

    std::cout << "重写后的字符串为： " << s << std::endl;


    system ("pause");
    return 0;
}