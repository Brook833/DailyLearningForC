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
    Disc_quote(const string& book, double price, size_t qty, double disc) : Quote(book,price), quantity(qty), discount(disc) {
        cout << "Disc_quote(const string& book, double price, size_t qty, double disc)" << endl;
    }

    Disc_quote(Disc_quote &rhs) : Quote(rhs), quantity(rhs.quantity), discount(rhs.discount) {
        cout << "Disc_quote(Disc_quote &rhs)" << endl;
    }
    Disc_quote& operator= (const Disc_quote &rhs) {
        cout << "Disc_quote& operator= (const Disc_quote &rhs)" << endl;
        Quote:operator=(rhs);
        quantity = rhs.quantity;
        discount = rhs.discount;
        return *this;
    }

    Disc_quote(Disc_quote &&rhs) noexcept : Quote::Quote(std::move(rhs)), quantity(std::move(rhs.quantity)), discount(std::move(rhs.discount)) {
        cout << "Disc_quote(Disc_quote &&rhs) noexcept" << endl;
    }

    Disc_quote *clone() const & { return new Disc_quote(*this); }

    Disc_quote& operator=(Disc_quote &&rhs) noexcept {
        cout << "Disc_quote(Disc_quote &&rhs) noexcept " << endl;
        Quote::operator=(rhs);
        quantity = std::move(rhs.quantity);
        discount = std::move(rhs.discount);
        return *this;
    }
    double net_price(size_t) const = 0;
};

#endif  // DISC_QUOTE_H_