#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Quote.h"

class Bulk_quote : public Quote {
private:
    size_t min_qty = 0;
    double discount = 0.0;
public:
    Bulk_quote() = default;
    Bulk_quote(const string& a, double b, size_t c, double d) : Quote(a, b), min_qty(c), discount(d) {
        cout << "Bulk_quote(const string& a, double b, size_t c, double d)" << endl;
    }

    Bulk_quote(const Bulk_quote &rhs) : Quote(rhs), min_qty(rhs.min_qty), discount(rhs.discount) {
        cout << "Bulk_quote(Bulk_quote &rhs)" << endl;
    }
    Bulk_quote& operator=(const Bulk_quote &rhs) {
        cout << "Bulk_quote& operator=(const Bulk_quote &rhs)" << endl;
        Quote::operator=(rhs);
        min_qty = rhs.min_qty;
        discount = rhs.discount;
        return *this;
    }

    Bulk_quote(Bulk_quote &&rhs) noexcept : Quote(std::move(rhs)) {
        cout << "Bulk_quote(Bulk_quote &&rhs) noexcept" << endl;
    }
    Bulk_quote& operator=(Bulk_quote &&rhs) noexcept {
        cout << "Bulk_quote& operator=(Bulk_quote &&rhs) noexcept" << endl;
        Quote::operator=(rhs);
        min_qty = std::move(rhs.min_qty);
        discount = std::move(rhs.discount);
        return *this;
    }

    void debug() {
        Quote::debug();
        cout << "Bulk_quote: " << min_qty << " " << discount << endl; 
    }

    Bulk_quote *clone() const & { return new Bulk_quote(*this); }
    Bulk_quote *clone() && { return new Bulk_quote(std::move(*this)); }

    double net_price(size_t a) const override {
        if (a >= min_qty) {
            return a * (1 - discount) * price;
        } else {
            return a * price;
        }
    }
};

#endif  // BULK_QUOTE_H_
