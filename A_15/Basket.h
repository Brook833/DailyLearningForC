#ifndef BASKET_H_
#define BASKET_H_

#include <memory>
#include <set>
#include "Bulk_quote.h"

class Basket {
private:
    static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs) { return lhs->isbn() < rhs->isbn(); }
    multiset<shared_ptr<Quote>, decltype(compare)*> items {compare};
public:
    Basket() = default;

    void add_item(const Quote &sale) { items.insert(shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote &&sale) { items.insert(shared_ptr<Quote>(std::move(sale).clone())); }

    double total_receipt(ostream &os) const {
        auto sum = 0.0;
        for (auto iter = items.begin(); iter != items.end(); iter = items.upper_bound(*iter)) {
            sum += print_total(os, **iter, items.count(*iter));
        }
        os << "Total Sale: " << sum << endl;
        return sum;
    }

    void print_multiset() {
        for (auto c : items) {
            cout << c->isbn() << endl;
        }
    }
};

#endif  // BASKET_H_