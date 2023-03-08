#include <iostream>

template <typename T, size_t N>
const T *begin_zxc(const T (&v)[N]) {
    return v;
}

template <typename T, size_t N>
const T *end_zxc(const T (&v)[N]) {
    return v + N;
}

int main() {
    int arry[5] = {0, 1, 2, 3, 4};
    auto it = begin_zxc(arry);
    auto it_end = end_zxc(arry);

    std::cout << *it << std::endl;
    std::cout << *(it_end - 1)<< std::endl;

    system("pause");
    return 0;
}