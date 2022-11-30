#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main() {
    vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int> b, c ,d;

    copy(a.begin(), a.end(), back_inserter(b));
    copy(a.begin(), a.end(), front_inserter(c));
    copy(a.begin(), a.end(), inserter(d, d.begin()));

    cout << "b:" << endl;
    for (auto c : b) {
        cout << c << " ";
    }

    cout << "c:" << endl;
    for (auto a : c) {
        cout << a << " ";
    }

    cout << "d:" << endl;
    for (auto c : d) {
        cout << c << " ";
    }

    system("pause");
    return 0;
}