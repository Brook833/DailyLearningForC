#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Disc_quote.h"

class Bulk_quote : public Disc_quote {
private:
    size_t min_qty = 0;
    double discount = 0.0;
public:
    Bulk_quote() = default;
    Bulk_quote(const string& a, double b, size_t c, double d) : Disc_quote(a, b, c, d) {}

    void debug() {
        Quote::debug();
        cout << "Bulk_quote: " << min_qty << " " << discount << endl; 
    }


    double net_price(size_t a) const override {
        if (a >= min_qty) {
            return a * (1 - discount) * price;
        } else {
            return a * price;
        }
    }
};

#endif  // BULK_QUOTE_H_
