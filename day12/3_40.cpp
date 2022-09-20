#include <iostream>
#include <cstring>


int main () {
    system("chcp 65001");

    char s1[] = "jd";
    char s2[] = "tm";

    
    char a[4];
    strcpy(a, s1);
    strcat(a, s2);
    std::cout << a << std::endl;

    system("pause");
    return 0;
}