#include <windows.h>
#include <iostream>
#include <vector>

int main () {
    std::vector<int> ival;
    int a;
    while (std::cin >> a) {
        ival.push_back(a);
    }
    for (auto c : ival) {
        std::cout << c << " ";
    }

    system("pause");
    return 0;
}