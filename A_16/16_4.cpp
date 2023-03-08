#include <iostream>
#include <vector>
#include <list>
#include <string>

template <typename T1, typename T2>
T1 find_zxc(const T1 &begin, const T1 &end, const T2 &v) {
    for(auto it = begin; it != end; it++) {
        if(*it == v) {
            return it;
        }
    }
    //auto it = find(it1, it2, v);
    return end;
}

int main () {
    std::vector<int> v;
    std::list<std::string> l {"a", "b", "c", "d", "e"};
    for (auto i = 0; i != 5; i++) {
        v.push_back(i);
    }

    auto it_v = find_zxc(v.begin(), v.end(), 2);
    std::cout << it_v - v.begin() + 1 << std::endl;

    auto it_l = find_zxc(l.begin(), l.end(), "e");
    std::cout << *it_l << std::endl;

    system("pause");
    return 0;
}