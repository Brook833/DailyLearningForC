#ifndef X_QUOTE_H_
#define X_QUOTE_H_

#include "Quote.h"

class X_quote : public Quote {
private:
    size_t max_qty = 0;
    double discount = 0.0;
public:
    X_quote() = default;
    X_quote(const string& a, double b, size_t c, double d) : Quote(a, b), max_qty(c), discount(d) {}

    double net_price(size_t a) const override {
        if (a <= max_qty) {
            return a * (1 - discount) * price;
        } else {
            return max_qty * (1 - discount) * price + (a - max_qty) * price;
        }
    }
};

#endif  // X_QUOTE_H_
