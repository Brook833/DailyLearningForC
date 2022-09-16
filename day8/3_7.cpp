#include <windows.h>
#include <iostream>
#include <string>


int main () {
    system ("chcp 65001");
    std::string s;
    std::cin >> s;

    for (char &c : s) {//改为char后，程序正常运行，auto编译器也会推断为char。
        c = 'X';
    }

    std::cout << "重写后的字符串为： " << s << std::endl;


    system ("pause");
    return 0;
}