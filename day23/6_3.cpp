#include <iostream>

int fact (int val) {
    int res = 1;
    while (val > 1) {
        res *= val--;
    }
}

int main() {
    system("chcp 65001");
    int a = 4;
    int result = fact(a);
    std::cout << a << "的阶乘是：" << result << std::endl;
    system("pause");
    return 0;
}