#include <windows.h>
#include <iostream>
#include <string>

int main () {
    system ("chcp 65001");

    std::string s;
    getline(std::cin, s);

    for (auto &c : s) {
         if(!ispunct(c)) {
            std::cout << c;
         }
    }
    std::cout << std::endl;



    system ("pause");
    return 0;
}