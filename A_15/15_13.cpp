/*
派生类中的print很明显是输出基类的成员后，在输出派生类的成员。

应修改为
void print(ostream &os) { base::print(os); os << " " << i; }
*/