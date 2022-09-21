2022.9.18
复习C++primer 3.4迭代器

## 迭代器
我们可以使用下表运算符来访问string对象或vector对象的元素，还有一种更通用的机制也可以实现同样的目的，就是迭代器。

所有标准库容器都可以使用迭代器，但只有少数支持下标运算符。

严格来说，string对象不属于容器，但是string支持很多与容器类型类似的操作，比如下标运算符和迭代器。

类似于指针类型，迭代器也提供了对对象的间接访问。

有效的迭代器指向某个元素，或指向容器中为尾元素的下一位置；其他情况都属于无效。

### 使用迭代器
和指针不一样的是，获取迭代器不是使用取地址符，有迭代器的类型同时拥有返回迭代器的成员。

这些类型都拥有名为begin和end的成员，其中begin成员负责返回指向第一个元素的迭代器。end成员负责返回指向容器尾元素的下一位置的迭代器。

end成员返回的迭代器通常被称作尾后迭代器。

特殊情况下，如果容器为空，则begin和end返回的是同一个迭代器。（都是尾后迭代器）

### 迭代器运算符
*iter  //返回迭代器iter所指元素的引用

iter->mem  //解引用iter并获取该元素的名为mem的成员，等价于(*iter).mem

++iter  //令iter指示容器中的下一个元素

--iter  //令iter指示容器中的上一个元素

iter1 == iter2  //判断两个迭代器是否相等，如果两个迭代器指示的是同一个元素或者他们是同一个容器的尾后迭代器，则相等。

解引用一个非法迭代器或者尾后迭代器都是未被定义的行为。

### 将迭代器从一个元素移动到另外一个元素
因为end返回的迭代器并不实际指向某个元素，所以不能对其进行递增或解引用操作。

所有标准库容器的迭代器都定义了==和！=，但他们中的大多数都没有定义<运算符。

### 迭代器类型
一般来说我们无需知道迭代器的精确类型，实际上，那些拥有迭代器的标准库类型使用iterator和const_iterator来表示迭代器的类型。

vector<int>::iterator it; //it能读写vector<int>的元素

string::iterator it2; //it2能读写string对象中的字符

vector<int>::const_iterator it3; //i3只能读，不能写

string::const_iterator it4; //i4只能读，不能写

const_iterator和常量指针差不多，能读取但不能修改它所指的元素值。

### begin和end运算符
如果对象只需要读操作而无需写操作，我们最好使用常量类型。

C++11标准引入了两个新函数，分别是cbegin和cend，返回值都是const_iterator。

### 结合解引用和成员访问操作
解引用迭代器可获得迭代器所指的对象，如果该对象正好是类，就可以进一步访问它的对象。

（*it).empty(); //(*it)的圆括号必不可少。

为了简化上述表达式，C++语言定义了箭头运算符->。箭头运算符把解引用和成员访问两个操作结合在一起，即(*it).mem和it->mem表达的意思相同。

### 某些对vector对象的操作会使迭代器失效
vector对象虽然可以动态的增长，但是也会有一些副作用。已知的一个限制是不能通过范围for向vector对象中添加元素。另外一个限制是任何一种可能改变vector对象容量的操作，比如push_back，都会是该vector对象的迭代器失效。

但凡是使用了迭代器的循环体，都不要向迭代器所属的容器添加元素。

## 迭代器运算
string和vector的迭代器提供了更多额外的运算符，一方面可使得迭代器的每次移动跨过多个元素，另外也支持迭代器进行关系运算。

iter + n  //迭代器加上一个整数值仍得到一个迭代器，迭代器指示的新位置与原来相比向前移动了n个元素。

iter1 - iter2  //两个迭代器相减的结果是它们之间的距离，参与运算的两个迭代器必须指向的是同一个容器中的元素或是尾元素的下一位置。

### 迭代器的算术运算
迭代器类型是名为difference_type的带符号整数。