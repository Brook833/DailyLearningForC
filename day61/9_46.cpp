#include <string>
#include <iostream>

using namespace std;

string name_string (string &name, const string &a, const string &b) {
    name.insert(0, " ");
    name.insert(0, a);
    name.insert(name.size(), " ");
    name.insert(name.size(), b);

    return name;
}

int main() {
    string s = "James Bond";
    name_string(s, "Mr", "II");
    cout << s << endl;

    system("pause");
    return 0;
}