#include "String.h"
#include <iostream>

std::pair<char*, char*> String::alloc_n_copy(const char* b, const char* e) { 
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

void String::free() {
    if (elements) {
        for (auto p = end; p != elements;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, end - elements);
    }
}

String::String() : String("") {
    std::cout << "默认构造函数" << std::endl;
}

String::String(const char *s) {
    char *e = const_cast<char *>(s);
    while (*e) {
        e++;
    }
    auto pair_ = alloc_n_copy(s, e + 1);
    elements = pair_.first;
    end = pair_.second;
    std::cout << "接受C风格字符串指针参数的构造函数" << std::endl;
}

String::String(const String& s) {
    auto pair_ = alloc_n_copy(s.elements, s.end);
    elements = pair_.first;
    end = pair_.second;
    std::cout << "拷贝构造函数" << std::endl;
}

String::String(String &&s) noexcept {
    elements = std::move(s.elements);
    end = std::move(s.end);
    s.elements = nullptr;
    s.elements = end;
}

String& String::operator= (const String &s) {
    free();
    auto pair_ = alloc_n_copy(s.elements, s.end);
    elements = pair_.first;
    end = pair_.second;
    std::cout << "拷贝赋值运算符" << std::endl;
    return *this;
}

String& String::operator= (String &&s) {
    if (this != &s) {
        free();
        elements = s.elements;
        end = s.end;
        s.elements = nullptr;
        s.end = nullptr;
    }
    return *this;
}

String::~String() {
    free();
    std::cout << "析构函数" << std::endl;
}