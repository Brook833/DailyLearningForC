2022.9.15
复习C++primer 3.2.2string对象上的操作 3.2.3处理string对象上的字符

## string对象上的操作

一个类除了要初始化其对象的方式外，还要定义对象上所能执行的操作。

类既能够定义通过函数名调用的操作，也能定义<<,+等各种运算符在该类对象上的新含义。

string的大多数操作：

os << s  将s写入到输出流os中，返回os

is << s  从is中读取字符串赋给s，字符串以空白分割，返回is

getlint(is, s)  从is中读取一行赋给s，返回is

s.empty()  s为空返回true，否则返回false

s.size()  返回s中字符的个数

s[n]  返回s中第n个字符的引用，位置从0计起

s1 + s2  返回s1和s2连接后的结果

s1 = s2  用s2的副本代替s1中原来的字符

s1 == s2 如果s1和s2中的字符完全一样，则它们相等。string对象的相等性判断对大小写敏感。

<, <=, >, >=  利用字符在字典中的顺序进行比较，对字母的大小写敏感

### string::size_type类型
string::size_type是一个无符号类型的值，而且能够放下任何string对象的大小。

所有用于存放string类函数返回值的变量，都应该是string::size_type。

C++11标准中，允许编译器通过auto或decltype来推断变量的类型。

### 比较string对象
如果两个string对象的长度不同，而且较短string对象的每个字符都与较长string对象对应位置上的字符相同，就说较短string对象小于string对象。

如果两个string对象在某些对应位置上不一致，则其比较结果是第一对相异字符比较的结果。

### 为string对象赋值
string st1(10,'c'); //st1 = cccccccccc;

### 两个对象相加
两个string对象相加得到一个string对象，其内容是把左侧的运算对象与右侧的运算对象串接而成。

### 字面值和string对象相加
因为标准库允许把字符字面值和字符串字面值转换成string对象。

string s4 = s1 + ","; //把一个string对象和一个字面值相加。

string s5 = "hello" + ","//加号两边的两个运算对象都不是string。

因为某些历史原因，也为了与C兼容，所以C++语言中的字符串字面值并不是标准库类型string的对象。

### 处理string对象中的字符
cctype头文件中定义了一组标准库函数：

isalnum(c) // 当c是字母或数字是为真

isalpha(c) // 当c是字母时为真

iscntrl(c) // 当c是控制字符时为真

isdigit(c) // 当c是数字时为真

isgraph(c) // 当c不是空格但可打印时为真

isprint(c) // 当c是可打印字符时为真（即c是空格或c具有可视形式）

ispunct(c) // 当c是标点符号时为真

isspace(c) // 当c是空白时为真

isupper(c) // 当c时大写字母时为真

isxdigit(c) // 当c是十六进制数字时为真

tolower(c) // 如果c是大写字母，输出对应的小写字母，否则原样输出c

toupper(c) // 如果c是小写字母，输出对应的大写字母，否则原样输出c

### 处理每个字符？使用基于范围的for语句
范围for语句，这种语句遍历给定序列中的每个元素，并对序列中的每个值执行某种操作。

string对象的下标必须大于等于0而小于s.size();'

在访问字符之前，首先检查s是否为空。