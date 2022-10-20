#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;
class Person {
 private:
  string strName_;    //姓名
  string strAdress_;  //地址
 public:
  string getName() const { return strName_; }      //返回姓名
  string getAdress() const { return strAdress_; }  //返回地址
};

#endif