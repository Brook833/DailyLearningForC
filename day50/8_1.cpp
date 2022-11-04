#include <iostream>

using namespace std;
istream &  i_out(istream& is) {
    std::string buf;
    while(is >> buf) {
        std::cout << buf << std::endl;
    }
    is.clear();
    return is;
}

int main() {
    i_out(cin);

    system("pause");
    return 0;
}