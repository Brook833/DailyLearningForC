#ifndef SCREEN_H
#define SCREEN_H
#include <string>


class Screen
{
private:
    unsigned height = 0, width = 0;
    unsigned cursor = 0;
    string contents;

    typedef std::string::size_type pos;
public:
    Screen() = default;
    Screen(unsigned height, unsigned width) : height(ht), width(wd), contents(ht*wd, ' ') {}
    Screen(unsigned height, unsigned width, char c) : height(ht), width(wd), c(ht*wd, c) {}
};
#endif