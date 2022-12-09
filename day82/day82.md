2022.12.08



## 11.3 关联容器操作
关联容器定义了表11.3中列出的类型。这些类型表示容器关键字和值的类型。

| **表11.3: 关联容器额外的类型别名** |  |
|:- |:- |
| key_type | 此容器类型的关键字类型 |
| mapped_type | 每个关键字关联的类型；只适用于map |
| value_type | 对于set，与key_type相同, 对于map，为pair<const key_type, mapped_type> |
对于set类型，key_type和value_type是一样的; set中保存的值就是关键字。在一个map中，元素是关键字——值对。即每个元素是一个pair对象，包含一个关键字和一个关联的值。由于我们不能改变一个元素的关键字，因此这些pair的关键字部分是const的:

```c++
set<string>::value_type v1;  // v1是一个string
set<string>::key_type v2;  // v2是一个string
map<string, int>::value_type v3;  // v3是一个pair<string, int>
map<string, int>::key_type v4;  // v4是一个string
map<string, int>::mapped_type v5;  // v5是一个int
```

与顺序容器一样，我们用作用域运算符来提取一个类型的成员————例如，map<string, int>::key_type。

只有map类型(unordered_map、unordered_multimap、multimap、和map)才定义了mapped_type。

## 11.3.1 关联容器迭代器
当解引用一个关联容器迭代器时，我们会得到一个容器的value_type的值的引用。对map而言，value_type是一个pair类型，其first成员保存const的关键字，second成员保存值:

```c++
// 获得只想word_count中一个元素的迭代器
auto map_it = word_count.begin();
// *map_it是指向一个pair<const string, size_t>对象的引用
cout << map_it->first;  // 打印此元素的关键字
cout << map_it->second;  // 打印此元素的值
map_it->first = "new key";  // 错误，关键字是const的。
++map_it->second;  // 正确，我们可以通过迭代器改变元素。
```

**Note: 必须记住，一个map的value_type是一个pair，我们可以改变pair的值，但不能改变关键字成员的值。**

### set的迭代器是const的
虽然set类型类型同时定义了iterator和const_iterator类型，但两种类型都只允许只读访问set中的元素。与不能改变一个map元素的关键字一样，一个set中的关键字也是const的。可以用一个set迭代器来读取元素的值，但不能修改:

```c++
set<int> iset = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
set<int>::iterator set_it = iset.begin();
if (set_it != iset.end()) {
    *set_it = 42;  // 错误，set中的关键字是只读的。
    cout << *set_it << endl;  // 正确，可以读关键字
}
```

### 遍历关联容器
map和set类型都支持表9.2中的begin和end操作。与往常一样，我们可以用这些函数获取迭代器，然后用迭代器来遍历容器。例如，我们可以编写一个循环来打印单词计数程序的结果:

```c++
// 获得一个指向首元素的迭代器
auto map_it = word_count.cbegin();
// 比较当前迭代器和尾后迭代器
while (map_it != word_count.cend()) {
    // 解引用迭代器，打印关键字-值对
    cout << map_it->first << " occurs " << map_it->second << " times" << endl;
    ++map_it;  // 递增迭代器，移动到下一个元素
}
```

while的循环条件和循环中的迭代器递增操作看起来很像我们之前编写的打印一个vector或一个string的程序。我们首先初始化迭代器map_it，让它指向word_count中的首元素。只要迭代器不等于end，就打印当前元素并递增迭代器。输出语句解引用map_it来获得pair的成员，否则与我们之前的程序一样。

**Note:本程序的输出是按字典序排列的。当使用一个迭代器遍历一个map、multimap、set或multiset时，迭代器按关键字升序遍历元素。

### 关联容器和算法
我们通常不对关联容器适用泛型算法。关键字是const这一特性意味着不能讲关联容器传递给修改或重排元素的算法，因为这类算法需要想元素写入值。

关联容器可用于只读取元素的算法。但是，很多这类算法都要搜索序列。由于关联容器中的元素不能通过他们的关键字进行(快速)查找，因此对其使用泛型搜索算法几乎总是个坏主意。例如关联容器定义了一个find的成员，他通过一个给定的关键字直接获取元素。我们可以用泛型find算法来查找一个元素，但此算法会进行顺序搜索。使用关联容器定义的专用的find成员会比调用泛型find快得多。

在实际编程中，如果我们真要对一个关联容器使用算法，要么是将它当作一个源序列，要么当作一个目的位置。例如，可以用泛型copy算法将元素从一个关联容器拷贝到另一个序列。类似的，可以调用inserter将一个插入器绑定到一个关联容器。通过使用inserter，我们可以将关联容器当作一个目的位置来调用另一算法。