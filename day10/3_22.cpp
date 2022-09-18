#include <iostream>
#include <vector>

int main () {
    system("chcp 65001");

    std::vector<std::string> s;
    std::string v;
    while (getline(std::cin, v)) {
        s.push_back(v);
    }
    
    for (auto i = s.begin(); i != s.end() && !i->empty(); i++) {
        for (auto it = i->begin(); it != i->end(); it++) {
            *it = toupper(*it);
        }
        std::cout << *i << std::endl;
    }


    system("pause");
    return 0;
}