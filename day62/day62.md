2022.11.18



### string搜索操作
string类型提供了6个不同的搜索函数，每个函数都有4个重载版本。表9.14描述了这些搜索成员函数及其参数。每个搜索操作都返回一个string::size_type值，表示匹配发生位置的下标。如果搜索失败，则返回一个名为string::npos的static成员。标准库将npos定义为一个const string：：size_type类型，并初始化为值-1.由于npos是一个unsigned类型，此初始值意味着npos等于任何string最大的可能大小。

**WARNING: 搜索函数返回string::size_type值，该类型是一个unsigned类型。因此,用一个或其他带符号类型来保存这些函数的返回值不是一个好主意**

find函数完成最简单的搜索。它查找参数指定的字符串，若找到，则返回第一个匹配位置的下标，否则返回npos;

```c++
string lowercase("annabellle");
pos1 = lowercase.find("Anna);  // pos1 = npos;
```

这段代码会将pos1置为npos，因为Anna与anna不匹配。

一个更复杂一些的问题是查找与给定字符串中任何一个字符匹配的位置。例如，下面代码定位name中的第一个数字:

```c++
string numbers("0123456789"), name("r2d2");
auto pos = name.find_first_of(numbers);  // 返回1，name中第一个数字的下标
```

如果是要搜索第一个不在参数中的字符，我们应该调用find_first_not_of。例如，为了搜索一个string中第一个非数字字符，可以这样做:

```c++
string dept("03714p3");
auto pos = dept.find_first_not_of(numbers);  // 返回5，字符p的下标
```

| **表9.14: string搜索操作** |  |
|:- |:- |
| 搜索操作返回指定字符出现的下标，如果未找到则返回npos |  |
| s.find(args) | 查找s中第一次出现args的位置 |
| s.rfind(args) | 查找s中最后一次出现args的位置 |
| s.find_first_of(args) | 在s中查找args中任何一个字符第一次出现的位置 |
| s.find_last_of(args) | 在s中查找args中任何一个字符最后一次出现的位置 |
| s.find_first_not_of(args) | 在s中查找第一个不在args中的字符 |
| s.find_last_not_of(args) | 在s中查找最后一个不在args中的字符 |
| **args必须是以下形式之一 |  |
| c,pos | 从s中位置pos开始查找字符c。pos默认为0 |
| s2,pos | 从s中位置pos开始查找字符串s2。pos默认为0 |
| cp,pos | 从s中位置pos开始查找指针cp指向的以空字符结尾的C风格字符串。pos默认为0 |
| cp,pos,n | 从s中位置pos开始查找指针cp指向的数组的前n个字符。pos和n无默认值 |

### 指定在哪里开始搜索
我们可以传递给find操作一个可选的开始位置。这个可选的参数之处从哪个位置开始进行搜索。默认情况下，此位置被置为0。一种常见的程序设计模式使用这个可选参数在字符串中循环的搜索字符串出现的所有位置:

```c++
string::size_type pos = 0;
// 每步循环查找name中下一个数
while ((pos = name.find_first_of(numbers, pos)) != string::npos) {
    cout << "found number at index: " << pos << " element is " << name[pos] << endl;
    ++pos;  // 移动到下一个字符
}
```

while的循环条件将pos重置为从Pos开始遇到的第一个数字的下标。只要find_first_of返回一个合法下标，我们就打印当前结果并递增pos。

### 逆向搜索
到现在为止，我们使用过的find操作都是由左至右搜索。标准库还提供了类似的，但由右向左搜索的操作，rfind成员函数搜索最后一个匹配，即字符串最靠右的出现位置:

```c++
string river("Mississippi");
auto first_pos = river.find("is");  // 返回1
auto last_pos = river.rfind("is");  // 返回4
```

类似的，find_last函数的功能与find_first函数相似，只是它们返回最后一个而不是第一个匹配:
> + find_last_of搜索与给定string中任何一个字符匹配的最后一个字符。
> + find_last_not_of搜索最后一个不出现在给定string中的字符

每个操作都接受一个可选的第二参数，用来之处从什么位置开始搜索。