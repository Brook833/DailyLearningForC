#include <iostream>
#include <string>

template <typename T, size_t N>
constexpr size_t size_zxc(const T(&arr)[N]) {
    return N;
}

int main() {
    int arry[4];
    std::string s[6];

    auto a = size_zxc(arry);
    auto b = size_zxc(s);

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    system("pause");

    return 0;
}