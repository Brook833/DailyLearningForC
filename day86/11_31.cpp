
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

void remove_author(multimap<string, string> &books, const string &author) {
    auto number = books.count(author);
    auto it = books.find(author);
    while (number) {
        books.erase(it->first);
        number--;
    }
}

void print_books(multimap<string, string> &books) {
    cout << "当前书目包括: " << endl;
    for (auto book : books) {
        cout << "  " << book.first << ": 《" << book.second << "》" << endl;
    }
}

int main () {
    system("chcp 65001");
    multimap<string,  string> books;

    books.insert({"Barth, John", "Sot-Weed Factor"});
    books.insert({"Barth, John", "Lost in the Funhouse"});
    books.insert({"金庸", "笑傲江湖"});
    books.insert({"金庸", "天龙八部"});
    books.insert({"金庸", "射雕英雄传"});

    cout << "删除之前:" << endl;
    print_books(books);
    
    remove_author(books, "Barth, John");

    cout << "删除之后:" << endl;
    print_books(books);

    system("pause");
    return 0;
}
