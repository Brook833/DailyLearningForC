#include <iostream>
#include <list>
#include <vector>

using namespace std;
int main() {
    list<int> a {1, 2, 3};
    vector<int> c {4, 5, 6};
    vector<double> b(c.begin(), c.end());

    for (auto &c : b) {
        cout << c << endl;
    }

    system("pause");
    return 0;
}

