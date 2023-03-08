#include <iostream>
#include <string>

template <typename T, unsigned S>
void print_arry(T (&v)[S]) {
    for (auto c : v) {
        std::cout << c << std::endl;
    }
}

int main () {
    int arry[5] = {0, 1, 2, 3, 4};
    std::string s[3] = {"hello", "world", "!"};
    print_arry(arry);
    print_arry(s);

    system("pause");
    return 0;
}

