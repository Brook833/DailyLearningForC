#include "StrVec.h"

void StrVec::push_back(const string &s) {
    // 如果没有空间存放新元素，创建二倍大小的空间来存放，并将旧string移动到新的内存中
    if(size() == capacity()) {
        auto newcapacity = size() ? size() * 2 : 1;
        auto newdata = alloc.allocate(newcapacity);
        auto dest = newdata;
        auto elem = elements;
        for (auto i = 0; i != size(); ++i) {
            alloc.construct(dest++, std::move(*elem++));
        }
        // 释放旧string内存
        if (elements) {
            for (auto i = first_free; i != elements;) {
                alloc.destroy(--i);
            }
            alloc.deallocate(elements, cap - elements);
        }
        elements = newdata;
        first_free = dest;
        cap = newdata + newcapacity;
    }
    // 如果有空间存放新元素，将新元素存入第一个空闲位置，并将空闲位置递增。
    alloc.construct(first_free++, s);
}

StrVec::StrVec(initializer_list<string> il) {
    auto data = alloc.allocate(il.size());
    elements = data;
    first_free = cap = uninitialized_copy(il.begin(), il.end(), data);
}

StrVec::StrVec(const StrVec& s) {
    // 根据s.size()分配原始内存空间
    auto data = alloc.allocate(s.size());
    elements = data;
    first_free = cap = uninitialized_copy(s.begin(), s.end(), data);
}

StrVec& StrVec::operator= (const StrVec& rhs) {
    auto data = alloc.allocate(rhs.size());
    if (elements) {
        for (auto i = first_free; i != elements;) {
            alloc.destroy(--i);
        }
        alloc.deallocate(elements, cap - elements);
    }
    elements = data;
    first_free = cap = uninitialized_copy(rhs.begin(), rhs.end(), data);
    return *this;
}

StrVec::~StrVec() {
    if (elements) {
        for (auto i = first_free; i != elements;) {
            alloc.destroy(--i);
        }
        alloc.deallocate(elements, cap - elements);
    }
}