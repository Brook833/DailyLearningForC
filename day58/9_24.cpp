#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> v;
    int a = v.at(0);
    int b = v[0];
    int c = v.front();
    int d = *(v.begin());

    //cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << d << endl;

    system("pause");
    return 0;
}