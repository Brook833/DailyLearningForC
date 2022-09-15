#include "windows.h"
#include "iostream"
#include <string>

int main() {
    system ("chcp 65001");

    std::string s1, s2;
    std::cin >> s1;
    std::cin >> s2;
    /* #1
    if (s1 == s2) {
        std::cout << "两个输入相同：" << s1 << std::endl;
    } else if (s1 > s2) {
        std::cout << "两次输入不同：" << s1 << std::endl;
    } else {
        std::cout << "两次输入不同：" << s2 << std::endl;
    }*/
    
    /* #2
    if (s1.size() == s2.size()) {
        std::cout << "两次输入等长,均为" << s1.size() << "个字符" << std::endl;
    } else if (s1.size() > s2.size()) {
        std::cout << "两次输入不等长,较长的字符个数为" << s1.size() << std::endl;
    } else {
        std::cout << "两次输入不等长,较长的字符个数为" << s2.size() << std::endl;
    }*/
    system ("pause");
    return 0;
}