#include <iostream>
#include <cstring>
#include <string>

int main() {
    system("chcp 65001");

    /* #1
    std::string s1 = "hello";
    std::string s2 = "world";
    
    if( s1 > s2 ) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }*/
    const char s1[6] = "hello";
    const char s2[6] = "world";

    if (strcmp(s1, s2)) {
        std::cout << 1 << std::endl;
    } else {
        std::cout << 0 << std::endl;
    }
    

    system("pause");
    return 0;
}