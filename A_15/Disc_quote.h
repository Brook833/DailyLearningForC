#ifndef DISC_QUOTE_H_
#define DISC_QUOTE_H_

#include "Quote.h"

class Disc_quote : public Quote
{
protected:
    size_t quantity = 0;
    double discount = 0.0;
public:
    Disc_quote() = default;
    Disc_quote(const string& book, double price, size_t qty, double disc) : Quote(book,price), quantity(qty), discount(disc) {}
    double net_price(size_t) const = 0;
};

#endif  // DISC_QUOTE_H_