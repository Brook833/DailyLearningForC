2022.11.10



## 9.2.1 迭代器
与容器一样，迭代器有着公共的接口：如果一个迭代器提供某个操作，那么所有提供相同操作的迭代器对这个操作的实现方式都是相同的。例如，标准容器类型上的所有迭代器都允许我们访问容器中的元素，而所有迭代器都是通过解引用运算符来实现这个操作的。类似的，标准库容器的所有迭代器都定义了自增运算符，从当前元素移动到下一个元素。

表3.6列出了迭代器支持的所有操作，其中有一个例外不符合公共接口特点--forward_list迭代器不支持递减运算符(--)。表3.7列出了迭代器支持的算数运算，这些运算只能应用于string、vector、deque、和array的迭代器。我们不能将他们用于其他任何类型容器的迭代器。

### 迭代器范围
**Note:迭代器范围的概念是标注库的基础**

一个迭代器范围(iterator range)由一对迭代器表示，两个迭代器分别指向同一个容器中的元素或者是尾元素之后的位置。这两个迭代器通常被称为begin和end，或者是first和last，他们标记了容器中元素的一个范围。

虽然第二个迭代器常常被称为last，但这种叫法有些误导，因为第二个迭代器从来都不会指向范围中的最后一个元素，而是指向尾元素之后的位置。迭代器范围中的元素包含first所表示的元素以及从first开始直至last(但不包含last)之间的元素。

这种元素范围被称为左闭合区间，其标准数学描述为[begin,end),表示范围自begin开始，于end之前结束，迭代器begin和end必须指向相同的容器。end可以与begin指向相同的位置，但不能指向begin之前的位置。

**对构成范围的迭代器的要求**
如果满足如下条件，两个迭代器begin和end构成一个迭代器范：
> + 他们指向同一个容器中的元素，或者是容器最后一个元素之后的位置，且我们可以通过反复递增begin来到达end。换句话说，end不在begin之前。

**warning: 编译器不会强制这些要求，确保程序符合这些约定是程序员的责任**

### 使用左闭合范围蕴含的编程假定
标准库使用左闭合范围是因为这种范围有三种方便的性质。假定begin和end构成一个合法的迭代器范围，则:
> + 如果begin与end相等,则范围为空。
> + 如果begin与end不等,则范围至少包含一个元素,且begin指向该范围中的第一个元素。
> + 我们可以对begin递增若干次,使得begin==end

这些性质意味着我们可以向下面的代码一样用一个循环来处理一个元素范围，而这是安全的:

```c++
while (begin != end) {
    *begin = val;  // 正确，范围非空，因此begin只想一个元素
    ++begin;  // 移动迭代器，获取下一个元素
}
```
给定构成一个合法范围的迭代器begin和end,若begin==end,则范围为空。在此情况下，我们应该退出循环。如果范围不为空，begin指向此非空范围的一个元素。因此，在while循环体中，可以安全地解引用begin，因为begin必然指向一个元素。最后，由于每次循环对begin递增一次，我们确定循环最终会结束。

## 9.2.2 容器类型成员
每个容器都定义了多个类型，如表9.2所示。我们已经使用过其中三种：size_type、iterator和const_iterator。

除了已经使用过的迭代器类型，大多数容器还提供反向迭代器。简单地说，反向迭代器就是一种反向遍历容器的迭代器。与正向迭代器相比，各种操作的含义也都发生了颠倒。例如，对一个反向迭代器执行++操作，会得到上一个元素。

剩下的就是类型别名了，通过类型别名，我们可以在不了解容器中元素类型的情况下使用它。如果需要元素类型，可以使用容器的value_type。如果需要元素类型的一个引用，可以使用reference或const_reference。这些元素相关的类型别名在泛型编程中非常有用。

为了使用这些类型，我们必须显式使用其类名：
```c++
//iter是通过list<string>定义的一个迭代器类型
list<string>::iterator iter;
//count是通过vector<int>定义的一个difference_type类型
vector<int>::difference_type count;
```

这些声明语句使用了作用域运算符来说明我们希望使用list<string>类的iterator成员及vector<int>类定义的difference_type。

## 9.2.3 begin和end成员
begin和end操作生成指向容器中第一个元素和尾元素之后位置的迭代器。这两个迭代器最常见的用途是形成一个包含容器中所有元素的迭代器范围。

如表9.2所示，begin和end有多个版本:带r的版本返回反向迭代器;以c开头的版本则返回const迭代器:

```c++
list<string> a = {"Milton", "Shakespare", "Austen"};
auto it1 = a.begin();  // list<string>::iterator
auto it2 = a.rbegin();  // list<string>::reverse_iterator
auto it3 = a.cbegin();  // list<string>::const_iterator
auto it4 = a.crbegin();  // list<string>::const_reversse_iterator
```
不以c开头的函数都是被重载过的。也就是说，实际上有两个名为begin的成员。一个是const成员，返回容器const_iterator类型。另一个是非常量成员，返回容器的iterator类型。rbgegin、end和rend的情况类似。当我们对一个非常量对象调用这些函数时，才会得到一个const版本。与const指针和引用类似，可以将一个普通的iterator转换为对应的const_iterator，但反之不行。

以c开头的版本是C++新标准引入的，用以支持auto与begin和end函数结合使用。过去，没有其他选择，只能显示生命希望使用哪种类型的迭代器:

```c++
//显式指定类型
list<string>::iterator it5 = a.begin();
list<string>::const_iterator it6 = a.begin();
//是iterator还是const_iterator依赖于a的类型。
auto it7 = a.begin();  // 仅当a是const时，it7是const_iterator
auto it8 = a.cbegin();  // it8是const_iterator
```

当auto与begin或end结合使用时，获得的迭代器类型依赖于容器类型，与我们想要如何使用迭代器毫不相干。但以c开头的版本还是可以获得const_iterator的，而不管容器的类型是什么。

**Best Practices:当不需要写访问时，应使用cbegin和cend**

## 9.2.4 容器定义和初始化
每个容器都定义了一个默认构造函数。除array之外，其他容器的默认构造函数都会创建一个指定类型的空容器，且都可以接受指定容器大小和元素初始值的参数。

| 表9.3: 容器定义和初始化|  |
| :- | :- |
| C c; | 默认构造函数。如果c是一个array，则c中的元素按默认方式初始化;否则c为空 |
| C c1(c2) 或 C c1 = c2 | c1初始化为c2的拷贝。c1和c2必须是相同类型(即,他们必须时相同的容器类型，且保存的时相同的元素类型:对于array类型,两者还必须具有相同大小) |
| C c{a, b, c} 或 C c = {a, b, c} | c初始化为初始化列表中元素的拷贝。列表中元素的类型必须与C的元素类型相容对于array类型，列表中元素数目必须等于或小于array的大小，任何遗漏的元素都进行值初始化 |
| C c(b,e) | c初始化为迭代器b和e指定范围中的元素的拷贝。范围中元素的类型必须与C的元素类型相容(array不适用) |
| **只有顺序容器(不包括array)的构造函数才能接受大小参数** |  |
| C seq(n) | seq包含n个元素，这些元素进行了值初始化;此构造函数是explicit的(string不适用) |
| C seq(n,t) | seq包含n个初始化为值t的元素 |
