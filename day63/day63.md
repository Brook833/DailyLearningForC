2022.11.19



## 9.5.4 compare函数
除了关系运算符外，标准库string类型还提供了一组compare函数，这些函数与C标准库的strcmp函数很相似。类似strcmp，根据s是等于、大于还是小于参数指定的字符串，s.compare返回0、整数或复数。

如表9.15所示，compare有6个版本。根据我们是要比较两个string还是一个string与一个字符数组，参数各有不同。在这两种情况下，都可以比较整个或一部分字符串。

| **表9.15: s.compare的几种参数形式** |  |
|:- |:- |
| s2 | 比较s和s2 |
| pos1, n1, s2 | 将s中从pos1开始的n1个字符与s2进行比较 |
| pos1, n1, s2, pos2, n2 | 将s中从pos1开始的n1个字符与s2中从pos2开始的n2个字符进行比较 |
| cp | 比较s与cp指向的以空字符结尾的字符数组 |
| pos1, n1, cp | 将s中从pos1开始的n1个字符与cp指向的以空字符结尾的字符数组进行比较 |
| pos1, n1, cp, n2 | 将s中从pos1开始的n1字符与cp指向的地址开始的n2个字符进行比较 |

## 9.5.5 数值转换
字符串中常常包含表示数值的字符。例如，我们用两个字符的string表示数值15——字符'1'后跟字符'5'。一般情况，一个数的字符表示不同于其数值。数值15如果保存为16位的short类型，则其二进制位模式位0000 0000 0000 1111，而字符串”15“存为两个Latin编码的char，二进制位模式0011 0001 0011 0101。第一个字节表示字符'1',其八进制值为61，第二个字节表示'5'，其Latin-1编码为八进制值065。

新标准引入了多个函数，可以实现数值数据与标准库string之间的转换:

```c++
int i = 42;
string s = to_string(i);  // 将整数i转换为字符表示形式
double d = stod(s);  // 将字符串s转换为浮点数
```

此例中我们调用to_string将42转换为其对应的string表示，然后调用stod将此string转换为浮点值。

要转换为数值的string中第一个非空白符必须是数值中可能出现的字符:

```c++
string s2 = "pi = 3.14";
d = stod(s2.substr(s2.find_first_of("+-.0123456789")));  // 转换s中以数子开始的第一个字串，结果是d = 3.14
```

在这个stod调用中，我们调用了find_first_of来获得s中第一个可能是数值的一部分的字符的位置。我们将s中从此位置开始的字串传递给stod。stod函数读取此参数，处理其中字符，直至遇到不可能是数值的一部分字符。然后他就将找到的这个数值的字符表示形式转换为对应的双精度浮点值。

string参数中的第一个非空白字符必须是符号(+或-)或数字。它可以以0x或0X开头来表示十六进制数。对于那些将字符串转换为浮点值的函数，string参数也可以以小数点(.)开头，并可以包含e或E来表示指数部分。对于那些将字符串转换为整型值的函数，根据基数不同，string参数可以包含字母字符，对应大于数字9的数。

**Note: 如果string不能转换为一个数值，这些函数抛出一个invalid_argument异常。如果转换得到的数值无法用任何类型来表示，则抛出一个out_of_range异常**

| **9.16: string和数值之间的转换** |  |
|:- |:- |
| to_string(val) | 一组重载函数，返回数值val的string表示。val可以是任何算术类型。对每个浮点类型和int或更大的整形，都有相应版本呢的to_string。与往常一样，小整形会被提升。 |
| stoi(s, p, b) | 返回s的起始子串(表示整数内容)的数值，返回值类型分别是int、long、unsigned long、long long、unsigned long long。b表示转换所用的基数，默认值是10。p是size_t指针，用来保存S中第一个非数值字符的下标，p默认为0，即，函数不保存下标。 |
| stol(s, p, b) |  |
| stoul(s, p, b) |  |
| stoll(s, p, b) |  |
| stoull(s, p, b) |  |
| sof(s, p) | 返回s的起始字串(表示浮点数内容)的数值，返回值类型分别是，float、double或long double。参数p的作用与整数转换函数中一样。 |
| stod(s, p) |  |
| stold(s, p) |  |