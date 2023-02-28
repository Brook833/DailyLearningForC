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
    Quote(const string &book, double sales_price) : bookNo(book), price(sales_price) {
        cout << "Quote(const string &book, double sales_price)" << endl;
    }

    Quote(const Quote &rhs) : bookNo(rhs.bookNo), price(rhs.price) {
        cout << "Quote(const Quote &rhs)" << endl;
    }
    Quote& operator= (const Quote &rhs) {
        cout << "Quote& operator= (const Quote &rhs)" << endl;
        bookNo = rhs.bookNo;
        price = rhs.price;
        return *this;
    }

    Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)) {
        cout << "Quote(Quote &&q)" << endl;
    }
    Quote& operator= (Quote &&rhs) noexcept {
        cout << "Quote& operator= (Quote &&rhs)" << endl;
        bookNo = std::move(rhs.bookNo);
        price = std::move(rhs.price);
        return *this;
    }

    virtual ~Quote() = default;

    virtual Quote* clone() const & { return new Quote(*this); }
    virtual Quote* clone() && { return new Quote(std::move(*this)); }

    string isbn() const { return bookNo; }
    virtual double net_price(size_t n) const { return n * price; }
    virtual void debug() {
        cout << "Quote: " << bookNo << " " << price << endl; 
    }
};

double print_total(ostream &os, Quote &item, size_t n) {
        double ret = item.net_price(n);
        os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << endl;
        return ret;
}


#endif  // QUOTE_H_
