#include "TextQuery.h"

void runQuery(ifstream& infile) {
    TextQuery tq(infile);
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") {
            break;
        }
        print_result(cout, tq.query(s)) << endl;
    }   
}

int main() {
    ifstream file("1.txt");
    runQuery(file);

    return 0;
}