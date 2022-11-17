#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<char> c = {'H','e','l','l','o'};
    string s(c.data(), c.size());
    cout << s << endl;

    system("pause");
    return 0;
}