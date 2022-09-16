#include <windows.h>
#include <iostream>
#include <string>


int main () {
    system ("chcp 65001");
    std::string s {"hello"};
    int n = 0;
    /* #1
    while (n != 5) {
        s[n] = 'X';
        n++;
    }*/

    /* #2
    for (; n != 5; n++) {
        s[n] = 'X';
    }*/
    std::cout << "重写后的字符串为： " << s << std::endl;


    system ("pause");
    return 0;
}