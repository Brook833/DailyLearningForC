#include <iostream>
#include <vector>
#include <windows.h>


int main() {
    system("chcp 65001");
    std::vector<std::string> sval;
    std::string s;
    char cont;
    std::cout << "请输入一个字后按回车" << std::endl;
    while (std::cin >> s) {
        sval.push_back(s);
        std::cout<< "是否继续？ 是 y/Y 否 n/N" << std::endl;
        std::cin >> cont;
        if (cont != 'y' && cont != 'Y') {
            break;
        }
    }
    for (auto c : sval) {
        std::cout << c << " ";
    }

    system("pause");
    return 0;
}