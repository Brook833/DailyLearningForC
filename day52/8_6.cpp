#include <iostream>
#include <fstream>
#include <string>

#include "Sales_data.h"
using namespace std;
int main(int argc, char *argv[]) {
    if(argc != 3) {
        cerr << "请给出文件名" << endl;
        return -1;
    }
    ifstream in(argv[1]);
    if(!in) {
        cerr << "无法打开输入文件" << endl;
        return -1;
    }
    ofstream out(argv[2], ofstream::app);
    if(!out) {
        cerr << "无法打开输出文件" << endl;
        return -1;
    }
    Sales_data total;
    if (total.read(in, total)) {
        Sales_data trans;
        while(trans.read(in, trans)) {
            if (total.isbn() == trans.isbn()) {
                total = total.add(total, trans);
            } else {
                total.print(out, total) << endl;
                total = trans;
            }
        }
        //total.print(cout, total) << endl;
        
        total.print(out, total) << endl;
    }
    else {
        cerr << "没有数据" << endl;
        return -1;
    }
    return 0;
}