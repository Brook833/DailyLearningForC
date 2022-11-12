#include <vector>

using namespace std;


//1:默认初始化
vector<int> a;
//2:初始化为a的拷贝
vector<int> b(a);
//3:初始化列表
vector<int> c{1, 2, 3};
//4:初始化为迭代器范围中元素的拷贝。
vector<int> d(a.begin(), a.end());
//5:默认值初始化
vector<int> e(10);
//6:指定值初始化
vector<int> f(10, 1);
