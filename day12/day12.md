202.9.20
复习C++primer 3.5.4C风格字符串 3.5.5与旧代码的接口 3.6多维数组

### C风格字符串
字符串字面值是一种通用结构的实例，这种结构即是C++由C继承而来的C风格字符串。

C风格字符串不是一种类型，而是为了表达和使用字符串而形成的一种约定俗成的写法。按照此习惯书写的字符串放在字符数组中并以空字符结束。

空字符结束的意思是在字符串最后一个字符后面跟着一个空字符（'\0')。

一般用指针来操作这些字符串。

### C标准库String函数
strlen(p);  //返回p的长度,空字符不计算在内。

strcmp(p1, p2);  //比较p1和p2，如果p1==p2,返回0；如果p1<p2，返回一个正值。

strcat(p1, p2);  //p2附加到给p1之后，返回p1。

strcpy(p1, p2);  //将p2拷贝给p1，返回p1。

传入此类函数的指针必须指向以空字符作为结束的数组。

### 比较字符串
比较标准库string对象时，用的是普通的关系运算符和相等性运算符。

如果把这些运算符用在两个C风格字符串上，实际上比较的是指针而非字符串本身。

如果想比较C风格字符串应该使用上述库函数。

### 目标字符串的大小由调用者指定
连接或拷贝C风格字符串也与标准库string对象的同类操作差别很大。

对于大多数应用来说，使用标准库string要比使用C风格字符串更安全，更高效。

## 多维数组
严格来说，C++中没有多维数组，其实是数组的数组。

### 多维数组的初始化
允许使用花括号括起来的一组值初始化多维数组。

int ia[3][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11}
};

### 使用范围for循环处理多维数组
for (const auto &row : ia)
    for (auto col : row)
        cout << col << endl;

这个循环中并没有任何写操作，可我们还是将外层循环的控制变量声明成引用类型，这是为了避免数组被自动转成指针。

要使用范围for语句处理多维数组，除了最内层的循环外，其他所有的循环控制变量都应该是引用类型。

### 指针和多维数组
当程序使用多维数组的名字时，也会自动将其转换成指向数组首元素的指针。

