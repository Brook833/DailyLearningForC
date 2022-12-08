#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    map<int, int> m;
    m[2] = 8;
    map<int, int>::iterator m_it = m.begin();
    cout << m_it->first << " " << m_it->second << endl;

    (*m_it).second = 66;

    cout << m_it->first << " " << m_it->second << endl;

    system("pause");
    return 0;
}