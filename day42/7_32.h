#ifndef WINDOW_MGR
#define WINDOW_MGR

#include <iostream>
#include <vector>
#include <string>


class Window_mgr {
public:
    void clear();
};

class Screen {
public:
    friend void Window_mgr::clear();

private:
  unsigned height = 0, width = 0;
  unsigned cursor = 0;
  std::string contents;

public:
  Screen() = default;
  Screen(unsigned ht, unsigned wd) : height(ht), width(wd) {}
  Screen(unsigned ht, unsigned wd, char c) : height(ht), width(wd), contents(ht*wd, c) {}
};

void Window_mgr::clear() {
    Screen myScreen(10, 20, 'X');
    std::cout << "清理之前 myScreen的内容是: " << std::endl;
    std::cout << myScreen.contents << std::endl;
    myScreen.contents = "";
    std::cout << "清理之后 myScreen的内容是: " << std::endl;
    std::cout << myScreen.contents << std::endl;
}

#endif
