#include <windows.h>
#include <iostream>
#include <string>

int main () {
    system ("chcp 65001");
    
    std::string s1, s2, s3, s4;
    std::cin >> s1 >> s2 >> s3;

    /* #1
    s4 = s1 + s2 + s3;
    std::cout << s4 << std::endl;
    */

    /* #2
    s4 = s1 + " " + s2 + " " + s3;
    std::cout << s4 << std::endl;
    */

    system ("pause");
    return 0;
}