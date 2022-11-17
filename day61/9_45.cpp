#include <iostream>
#include <string>

using namespace std;

string name_string (string &s, const string &s1, const string &s2) {
    s.insert(s.begin(), 1, ' ');
    s.insert(s.begin(), s1.begin(), s1.end());
    s.append(" ");
    s.append(s2);

    return s;
}

int main () {
    string s = "James Bond";
    name_string(s, "Mr", "II");
    cout << s << endl;

    system("pause");
    return 0;
}