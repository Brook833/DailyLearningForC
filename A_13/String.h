#ifndef STRING_H_
#define STRING_H_

#include <memory>

class String
{
private:
    char* elements;  // 指向字符串起始位置
    char* end;       // 指向字符串尾后位置
    std::allocator<char> alloc;

private:
    std::pair<char*, char*> alloc_n_copy(const char *, const char *);

    void free();

public:
    const char* c_str() const { return elements; }
    size_t size() const { return end - elements; }
    size_t length() const { return end - elements - 1; }

public:
    String();
    String(const char* s);
    String(const String&);
    String& operator= (const String&);
    ~String();
};

#endif  // STRING_H_
