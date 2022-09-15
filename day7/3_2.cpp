#include <windows.h>
#include <iostream>
#include <string>


int main() {
    system("chcp 65001"); //解决cout中有中文时，输出乱码的情况。
    std::cout << "请输入" << std::endl;
    std::string line;
    while (std::cin >> line) {
        //if(!line.empty()) {
            std::cout << line << std::endl;
        //}
    }

    std::cout << "测试完成" << std::endl;

    system("pause");
    return 0;
}