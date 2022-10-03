#include <iostream>

int time () {
    static int time = 0;
    return ++time;
}

int main() {
    for (int i = 0; i != 5; i++) {
        std::cout << time() << std::endl; 
    }

    system("pause");
    return 0;

}