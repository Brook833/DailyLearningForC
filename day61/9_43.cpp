#include <string>
#include <iostream>

using namespace std;

void change(string &s, const string &oldVal, const string &newVal) {
    auto begin = s.begin();
    for (begin; distance(begin, s.end()) >= distance(oldVal.begin(), oldVal.end()); ){
        if(string{begin, begin + oldVal.size()} == oldVal) {
            s.replace(begin, begin + oldVal.size(), newVal);
            begin += newVal.size();
        } else {
            begin++;
        }
    }
}

int main () {
    string s = "tho thru tho!";
    change(s, "thru", "through");
    cout << s << endl;

    //system("pause");
    return 0;
}