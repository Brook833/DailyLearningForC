#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>


//编号，价格，作者，名字
class Book {
private:
    std::string isbn_;
    double price_ = 0;
    std::string author_;
    std::string name_;
public:
Book() = default;
Book(const std::string &I, double p, const std::string &a, const std::string &n) : isbn_(I), price_(p), author_(a), name_(n) {}
Book(istream &is) { is >> isbn_; }
};

#endif