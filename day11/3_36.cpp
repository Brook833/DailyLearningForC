#include <iostream>

int main () {
    system("chcp 65001");

    int arry1[5] = {0 , 1, 2, 3, 4};
    int arry2[5];
    int val;
    int i = 0;

    while (std::cin >> val && i != 5) {

        arry2[i] = val;
        i++;
    }
    
    for (auto c : arry1) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    for (auto c : arry2) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
    int *p = std::begin(arry1);
    int *q = std::begin(arry2);
    
    int *pend = std::end(arry1);
    int *qend = std::end(arry2);

    int len1 = pend - p;
    int len2 = qend - q;

    if (len1 != len2) {
        std::cout << "两个数组长度不相等" << std::endl;
        system("pause");
        return 0;
    }

    for (; p != pend && q != qend; p++, q++) {
        if (*p == *q) {
            continue;
        } else {
            std::cout << "两个数组不相等" << std::endl;
            system("pause");
            return 0;
        }
    }
    std::cout << "两个数组相等" << std::endl;

    system("pause");
    return 0;
}