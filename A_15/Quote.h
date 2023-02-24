#ifndef QUOTE_H_
#define QUOTE_H_

#include <iostream>
#include <string>
using namespace std;

class Quote
{
private:
    string bookNo;      // 书籍的ISBN编号

protected:
    double price;       // 书籍原价

public:
    Quote() = default;
    Quote(const string &book, double sales_price) : bookNo(book), price(sales_price) {}
    virtual ~Quote();

    string isbn() const { return bookNo; }
    virtual double net_price(size_t n) const { return n * price; }

double print_total(ostream &os, Quote & item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

};

#endif  // QUOTE_H_
