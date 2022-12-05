#include <list>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void elimDups(list<string> &words) {
    words.sort();
    words.unique();
}

int main() {
    list<string> l = {"aa", "aa", "aa", "aa", "aasss", "aa"};
    elimDups(l);

    for (const auto& e : l) {
        cout << e << " ";
    }
    std::cout << std::endl;

    system("pause");

    return 0;

}