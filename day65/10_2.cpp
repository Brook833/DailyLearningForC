#include <iostream>
#include <string>
#include <list>
#include <algorithm>


using namespace std;

int main () {
    list<string> slst = {"aa", "aaa", "aa", "cc"};
    auto n = count(slst.begin(), slst.end(), "aa");

    cout << n << endl;
    system("pause");
    return 0;
}