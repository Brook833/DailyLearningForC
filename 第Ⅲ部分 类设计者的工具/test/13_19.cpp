#include <string>
#include <iostream>

using namespace std;

class Employee {
public:
    Employee() : Id(c++) {}
    Employee(const string &str) : name(str), Id(c++) {}
    Employee(const Employee &e) : name(e.name), Id(c++) {}
    Employee& operator=(Employee &e) {
        name = e.name;
        return *this;
    }

    const string &getName() { return name; }
    uint32_t getId() { return Id; }

private:
    string name;  // 雇员姓名
    uint32_t Id;  // 雇员证号
    static uint32_t c;
};

uint32_t Employee::c = 0;

void printNameAndId(Employee &e) {
    cout << e.getName() << ": " << e.getId() << endl;
}

int main() {
    Employee a("马飞"), b = a, c;
    c = b;
    printNameAndId(a);  // 马飞 0
    printNameAndId(b);  // 马飞 1
    printNameAndId(c);  // 马飞 2

    return 0;
}