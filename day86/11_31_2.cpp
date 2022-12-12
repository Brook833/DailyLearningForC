#include <algorithm>
#include <map>
#include <iostream>
#include <string>

using namespace std;

void remove_author(multimap<string, string> &books, const string &author) {
    auto pos = books.equal_range(author);
    if (pos.first == pos.second) {
        cout << "不存在" << author << "的作品" << endl;
    } else {
        books.erase(pos.first, pos.second);
    }
}

void print_books(multimap<string, string> &books) {
    cout << "##########"  << endl;
    for (auto book : books) {
        cout << book.first << ": 《" << book.second << "》" << endl;
    }
    cout << "##########"  << endl;
}

int main() {
    system("chcp 65001");
    multimap<string,  string> books;

    books.insert({"Barth, John", "Sot-Weed Factor"});
    books.insert({"Barth, John", "Lost in the Funhouse"});
    books.insert({"金庸", "笑傲江湖"});
    books.insert({"金庸", "天龙八部"});
    books.insert({"金庸", "射雕英雄传"});

    cout << "删除之前:" << endl;
    print_books(books);
    
    remove_author(books, "周小川");
    remove_author(books, "Barth, John");

    cout << "删除之后:" << endl;
    print_books(books);

    system("pause");
    return 0;
}