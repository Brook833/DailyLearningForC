#include <iostream>
#include <memory>

using namespace std;

struct destination{};  // 表示正在连接什么
struct connection{};   // 表示连接所需的信息
connection connect(destination *pd) {
    cout << "打开连接" << endl;
    return connection();
}

void disconnect(connection c) {
    cout << "关闭连接" << endl;
}

void end_connection(connection *p) { disconnect(*p); }
void f(destination &d) {
    cout << "智能指针管理 connect" << endl;
    connection c = connect(&d);
    shared_ptr<connection> p(&c, end_connection);
    cout << "f 结束" <<endl;
}

int main() {
    system("chcp 65001");

    destination d;
    f(d);

    system("pause");
    return 0;
}