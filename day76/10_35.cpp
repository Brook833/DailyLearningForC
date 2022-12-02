#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> s = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it = s.end() - 1;
    while (it != s.begin() - 1) {
        cout << *it-- << endl;
    }

    system("pause");
    return 0;
}