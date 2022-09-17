#include <iostream>
#include <vector>
#include <string>

int main () {

    std::vector<std::string> svec;
    std::string s;
    while (std::cin >> s) {
        svec.push_back(s);
    }
    for (auto &c : svec) {
        for (auto &x : c) {
            if (!isspace(x)) {
               x = toupper(x); 
            }
        }
    }

    for (auto &c : svec ) {
        for (auto &x : c) {
            std::cout << x;
        }
        std::cout << std::endl;
    }
    system("pause");
    return 0;
}