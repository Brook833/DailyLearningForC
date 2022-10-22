#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;
class Person {
 private:
  string strName_;    //姓名
  string strAdress_;  //地址
 public:
  Person() = default;
  Person(const string &name, const string &addr) {
    strName_ = name;
    strAdress_ = addr;
  }
  Person(std::istream &is) { read(is, *this); }
  string getName() const { return strName_; }      //返回姓名
  string getAdress() const { return strAdress_; }  //返回地址
  istream &read(istream &is, Person &per);
  ostream &print(ostream &os, const Person &per);
};

istream & Person::read(istream &is, Person &per) {
  is >> per.strName_ >> per.strAdress_;
  return is;
}

ostream & Person::print(ostream &os, const Person &per) {
  os << per.getName() << per.getAdress();
}
#endif