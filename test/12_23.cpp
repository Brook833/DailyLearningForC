#include <iostream>
#include <string>
#include <memory>
#include <cstring>

using namespace std;

int main() {
/*    const char *h = "Hello ";
    const char *w = "world";

    char *p = new char [11];

    strcpy(p, h);
    strcpy(p, w);
    cout << p << endl;
*/

    string s1 = "Hello ";
    string s2 = "World";
    char *r = new char[11];
    strcpy(r, (s1 + s2).c_str());

    cout << r << endl;

    delete [] r;
    system("pause");
    return 0;

}