2022.12.03



## 10.5 泛型算法结构
任何算法的最基本的特性是它要求迭代器提供哪些操作。某些算法，如find，只要求通过迭代器访问元素、递增迭代器以及比较两个迭代器是否相等这些能力。其他一些算法，如sort，还要求度、写和随机访问元素的能力。算法所要求的迭代器操作可以分为5个迭代器类别(iterator category),如表10.5所示。每个算法都会对它的每个迭代器参数致命提供哪类迭代器。

| **表10.5:迭代器类别** |  |
|:- |:- |
| 输入迭代器 | 只读，不写；单遍扫描，只能递增 |
| 输出迭代器 | 只写，不读；单遍扫描，只能递增 |
| 前向迭代器 | 可读写；多遍扫描，只能递增 |
| 双向迭代器 | 可读写；多遍扫描，可递增递减 |
| 随机访问迭代器 | 可读写；多遍扫描，支持全部迭代器运算 |
第二种算法分类的方式(如我们在本章开始所做的)是按照是否读、写或是重排序列中的元素来分类。附录A按这种分类方法列出了所有算法。

算法还共享一组参数传递规范和一组命名规范。

## 10.5.1 5类迭代器
类似容器，迭代器也定义了一组公共操作。一些操作所有迭代器都支持，另外一些只有特定类别的迭代器才支持。例如，ostream_iterator只支持递增、解引用和算数运算。vector、string和deque的迭代器除了这些操作外，还支持递减、关系和算数运算。

迭代器是按它们所提供的操作来分类的，而这种分类形成了一种层次。除了输出迭代器之外，一个高层类别的迭代器支持低层类别迭代器的所有操作。

C++标准指明了泛型和数值算法的每个迭代器参数的最小类别。例如，find算法在一个序列上进行一遍扫描，对元素进行只读操作，因此至少输入迭代器。replace函数需要一对迭代器，至少是前向迭代器。其第三个迭代器表示目的位置，必须至少是输出迭代器。其它的例子类似。对每个迭代器参数来说，其能力必须与规定的最小类别至少相当。向算法传递一个能力更差的迭代器会产生错误。

**WARNING: 对于向一个算法传递错误类别的迭代器的问题，很多编译器不会给出任何警告或提示。**

### 迭代器类别
输入迭代器(input iterator): 可以读取序列中的元素。一个输入迭代器必须支持
> + 用于比较两个迭代器相等和不相等运算符(==、!=)
> + 用于推进迭代器的前置和后置递增运算符(++)
> + 用于读取元素的解引用运算符(*);解引用只会出现在赋值运算符的右侧
> + 箭头运算符(->),等价于(*it).member，即，解引用迭代器，并提取对象的成员

输入迭代器只用于顺序访问。对于一个输入迭代器，*it++保证是有效的，但递增它可能导致所有其他指向流的迭代器失效。其结果就是，不能保证输入迭代器的状态可以保存下来并用来访问元素。因此，输入迭代器只能用于单遍扫描算法。算法find和accumulate要求输入迭代器；而istream_iterator是一种输入迭代器。

输出迭代器(output iterator): 可以看作输入迭代器功能上的补集————只写而不读元素。输出迭代器必须支持
> + 用于推进迭代器的前置和后置递增运算(++)
> + 解引用运算符(*),只出现在赋值运算符的左侧(向一个已经姐饮用的输出迭代器赋值，就是将值写入它所指的元素)

我们只能向一个输出迭代器赋值一次。类似输入迭代器，输出迭代器只能用于单遍扫描算法。用作目的位置的迭代器通常都是输出迭代器。例如，copy函数的第三个参数就是输出迭代器。ostream_iterator类型也是输出迭代器。

前向迭代器(forward iterator): 可以读写元素。这类迭代器只能在序列中沿一个方向移动。前向迭代器支持所有输入和输出迭代器的操作，而且可以多次读写同一个元素。因此，我们可以保存前向迭代器的状态，使用前向迭代器的算法可以对序列进行多遍扫描。算法replace要求前向迭代器，forward_list上的迭代器是前向迭代器。

双向迭代器(bidirectional iterator): 可以正向、反向读写序列中的元素。除了支持所有前向迭代器的操作之外，双向迭代器还支持前置和后置递减运算符(--)。算法reverse要求双向迭代器，除了forward_list之外。其它标准库都提供符合双向迭代器要求的迭代器。

随机访问迭代器(random-access iterator):提供在常量时间内访问序列中任意元素的能力。此类迭代器支持双向迭代器的所有功能，此外还支持表3.7中的操作:
> + 用于比较两个迭代器相对位置的关系运算符(<、<=、>和>=)
> + 迭代器和一个整数值的加减运算(+、+=、-和-=),计算结果是迭代器在序列中前进(或后退)给定整数个元素后的位置
> + 用于两个迭代器上的减法运算符(-)，得到两个迭代器的距离
> + 下标运算符(iter[n])，与*(iter[n])等价

算法sort要求随机访问迭代器。array、deque、string和vector的迭代器都是随机访问迭代器，用于访问内置数组元素的指针也是。