#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

void add_child(multimap<string, string> &families, const string &family,
               const string &child) {
    families.insert({family, child});
}

int main() {
    system("chcp 65001");
    multimap<string, string> families;

    add_child(families, "张", "强");
    add_child(families, "张", "三");
    add_child(families, "王", "五");

    for (auto f : families)
        cout << f.first << "家的孩子：" << f.second << endl;

    system("pause");
    return 0;
}
