#ifndef SCREEN_H_
#define SCREEN_H_

#include <string>


template <unsigned N, unsigned W>
class Screen {
private:
    unsigned pos = 0;
    std::string contents;
public:
    Screen() = default;
    Screen(char c) : contents(H * W, c) {}

    
};

#endif  // SCREEN_H_
