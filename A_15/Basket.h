#ifndef BASKET_H_
#define BASKET_H_

#include <memory>
#include <set>
#include "Quote.h"

class Basket {
public:
    void add_item(const Quote &sale) {}
private:
    static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs) { return lhs->isbn() < rhs->isbn(); }
    multiset<shared_ptr<Quote>, decltype(compare)*> items {compare};
};

#endif  // BASKET_H_