#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<int> s = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    reverse_iterator it = s.rbegin();
    while (it != s.rend()) {
        cout << *it++ << endl;
    }

    system("pause");
    return 0;
}