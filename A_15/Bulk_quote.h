#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Quote.h"

class Bulk_quote : public Quote {
private:
    size_t min_qty = 0;
    double discount = 0.0;
public:
    Bulk_quote() = default;
    Bulk_quote(const string& a, double b, size_t c, double d) : Quote(a, b), min_qty(c), discount(d) {}

    double net_price(size_t a) const override {
        if (a >= min_qty) {
            return a * (1 - discount) * price;
        } else {
            return a * price;
        }
    }
};

#endif  // BULK_QUOTE_H_
