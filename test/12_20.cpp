#include "12_19.h"
#include <fstream>
#include <iostream>

using namespace std;
int main(int argc, char** argv) {
    ifstream i(argv[1]);
    string text;
    StrBlob s;
    while (getline(i, text)) {
        s.push_back(text);
    }

    StrBlobPtr pbeg (s.begin());
    StrBlobPtr pend = s.end();
    for (;neq(pbeg, pend); pbeg.incr()) {
        cout << pbeg.redef() << endl;
    }

    return 0;
}