#include <iostream>
#include <vector>

int main() {

    int arry[5] = {0, 1, 2, 3, 4};
    std::vector<int> ival(std::begin(arry), std::end(arry));

    for (auto c : ival) {
        std::cout << c << std::endl;
    }

    system("pause");
    return 0;

}