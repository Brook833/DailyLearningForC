#ifndef SCREEN_H
#define SCREEN_H
#include <string>


class Screen
{
private:
    unsigned height = 0, width = 0;
    unsigned cursor = 0;
    std::string contents;

    typedef std::string::size_type pos;
public:
    Screen() = default;
    Screen(unsigned ht, unsigned wd) : height(ht), width(wd), contents(ht*wd, ' ') {}
    Screen(unsigned ht, unsigned wd, char c) : height(ht), width(wd), contents(ht*wd, c) {}
};
#endif