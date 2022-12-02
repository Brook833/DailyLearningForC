2022.12.2



## 10.4.3 反向迭代器
反向迭代器就是在容器中从微元素向首元素反向移动的迭代器。对于反向迭代器，递增(以及递减)操作的含义回颠倒过来。搭赠一个反向迭代器(++it)会移动到前一个元素:递减i哥迭代器(--it)会移动到下一个元素。

出了forward_list之外，其他容器都支持反向迭代器。我们可以通过调用rebgin()、rend()、crbegin()、crend()成员函数来获得反向迭代器。这些成员函数返回指向容器尾元素和首元素之前一个位置的迭代器。与普通迭代器一样，反向迭代器也有const和非const版本。

下面的循环是一个使用反向迭代器的例子,它按逆序打印vec中的元素:

```c++
vector<int> vec = {0, 1, ,2, 3, 4, 5, 6, 7, 8, 9};
// 从尾元素到首元素的反向迭代IQ
for (auto r_iter = vec.crbegin(); r_iter != vec.crend(); ++r_iter) {
    cout << *r_iter << endl;  // 打印9,8,7,6,5,4,3,2,1,0
}
```

虽然颠倒递增和递减运算符的含义可可能看起来令人混淆，但这样做使我们可以用算法透明的向前或向后处理容器。例如，可以通过向sort传递一对反向迭代器来将vector整理为递减序:

```c++
sort(vec.begin(), vec.end());  // 按"正常序"排序vec
sort(vec.rbegin(), vec.end());  // 按逆序排序，将最小元素放在vec的末尾
```

### 反向迭代器需要递减运算符
不必惊讶，我们只能从既支持++也支持--的迭代器来定义反向迭代器。毕竟反向迭代器的目的是在序列中反向移动。除了forword_list之外，标准容器上的其他迭代器都既支持递增运算也支持递减运算。但是，流迭代器不支持递减运算，因为不可能在一个流中反向移动。因此，不可能从一个forward_list或一个流迭代器创建反向迭代器。

### 反向迭代器和其他迭代器间的关系
假定有一个名为line的string，保存着一个逗号分隔的单词列表，我们希望打印line中的第一个单词。使用find可以很容易地完成这一任务:

```c++
// 在一个逗号分隔的列表中查找第一个元素
auto comma = find(line.cbegin(), line.cend(), ',');
cout << string(line.cbegin(), comma) << endl;
```

如果line中有逗号，那么comma将指向这个逗号；否则，它将等于line.cend()。否则当我们打印从line.cbegin()到comma之间的内容时，将打印到逗号为止的字母，或者打印整个string(如果其中不包含逗号的话)。

如果希望打印最后一个单词，可以改用反向迭代器:

```c++
// 在一个逗号分隔的列表中查找最后一个元素
auto rcomma = find(line.crbegin(), line.crend(), ',');
```

由于我们将crbegin()和crend()传递给find，find将从line的最后一个字符开始向前搜索。当find完成后，如果line中有逗号，则rcomma指向最后一个逗号--即，它指向反向搜索中找到的第一个逗号。如果line中没有逗号，则rcomma指向line.crend()。

当我们试图打印找到的单词时，最有意思的部分就来了。看起来下面的代码是显然的方法:

```c++
// 错误:将逆序输出单词的字符
cout << string(line.crbegin(), rcomma) << endl;
```

但它会生成错误的输出结果。例如，如果我们的输入是:

```c++
FIRST,MIDDLE,LAST
```

则这条语句会打印TSLA！

我们使用的是反向迭代器，回反向处理string。因此，上述输出语句从crbegin开始反向打印line中内容。而我们希望按正常顺序打印从rcomma开始到line末尾间的字符。但是，我们不能直接使用rcomma。因为它是一个反向迭代器，意味着它会反向朝着string的开始位置移动。需要做的是，将rcomma转换回一个普通迭代器，能在line中正向移动。我们需要调用recerse_iterator的base成员函数来完成这一转换，此成员函数会返回其对应的普通迭代器:

```c++
// 正确:得到一个正向迭代器，从逗号开始读取字符指导line末尾
cout << string(rcomma.base(), line.cend()) << endl;
```

给定和之前一样的输入，这条语句会如我们预期打印出LAST。

rcomma和rcomma.base()指向不同的元素，line.crbegin()和line.cend()也是如此。这些不同保证了元素范围无论是正向处理还是反向处理都是相同的。

```c++
F I R S T , M I D D L E, L A S T
cbegin() 指向 F
comma 指向 第一个,

rcomma 指向 第二个,
crbegin() 指向 T

rcomma.base() 指向 L
cend() 指向 T后的尾后迭代器
```

从技术上将，普通迭代器与反向迭代器的关系反映了左闭合区间的特性。关键点在于[line.crbegin(), rcomma)和[rcomma.base(), line.cend())指向line中相同的元素范围。为了实现这一点，rcomma和rcomma.base()必须生成相邻位置而不是相同位置，crbegin()和cend()也是如此。

**Note: 反向迭代器的目的是表示元素范围，而这些范围是不对称的，这导致一个重要的结果:当我们从一个普通迭代器初始化一个反向迭代器，或是一个反向迭代器赋值时，结果迭代器与原迭代器指向的并不是相同的元素。**